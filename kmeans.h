#ifndef __KMEANS_H__
#define __KMEANS_H__

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include <cfloat>
#include <fstream>

#include "point.h"
#include "cluster.h"
#include "thread_pool.h"

class KMeans {
    private:
        int size;
        std::vector<Point*> ps;
        std::vector<float> ds;
        std::vector<Cluster*> p2c;
        std::vector<Cluster*> cs;
        std::default_random_engine generator;
        ThreadPool pool;
        int workNum = 8;

        float randomRange(float range) {
            std::uniform_real_distribution<float> distribution(0.0, range);
            return distribution(generator);
        }

    public:
        KMeans(int _size, std::vector<Point*> &_ps, int threadNum): size(_size), ps(_ps), workNum(threadNum), pool(threadNum) {
            p2c.resize(ps.size());
            ds.resize(ps.size(), -1);
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            generator = std::default_random_engine(seed);
        }
        void initClusters() {
            // TODO choose center from all members.
            int r = static_cast<int>(randomRange(ps.size()));
            cs.push_back(new Cluster(ps[r], cs.size() + 1));

            std::vector<float> ds_tmp;
            ds_tmp.resize(ps.size(), FLT_MAX);

            for(int j = 1; j < size; ++j) {
                std::vector<std::future<void>> res;
                int batch = ps.size() / workNum + 1;
                for(int i = 0; i < workNum; ++i) {
                    int s = i * batch;
                    s = s < ps.size() ? s : ps.size();
                    int e = s + batch;
                    e = e < ps.size() ? e : ps.size();
                    res.emplace_back(
                        pool.enqueue([this, s, e, &ds_tmp] {
                            for(int j = s; j < e; ++j) {
                                float t = *cs[cs.size() - 1] - *ps[j];
                                ds_tmp[j] = ds_tmp[j] < t ? ds_tmp[j] : t;
                            }
                        })
                    );
                }
                for(auto && result : res) {
                    result.wait();
                }
                float all = 0;
                for(auto f : ds_tmp) all += f;
                float random = randomRange(all);
                //std::cout << random << ' ' << all << std::endl;
                for(int i = 0; i < ds_tmp.size(); ++i) {
                    random -= ds_tmp[i];
                    if(random < 0) {
                        cs.push_back(new Cluster(ps[i], cs.size() + 1));
                        break;
                    }
                }
                //std::cout << j << std::endl;
            }
            //for(int j = 0; j < size; ++j) {
            //    int r = static_cast<int>(randomRange(ps.size() - j));
            //    cs.push_back(new Cluster(ps[j + r]));
            //}
            //for(auto c : cs) c->center->output();
        } 
        void doRound(int s, int e) {
            for(int i = s; i < e; ++i) {
                //if(randomRange(1.0) < 0.2) continue;
                for(auto c : cs) {
                    float d = *c - *ps[i];
                    if((ds[i] == -1) || (d < ds[i])) {
                        p2c[i] = c;
                        ds[i] = d;
                    }
                }
            }
        }
        void parallel() {
        }
        void start() {
            initClusters();
            std::vector<std::thread*> works;
            int num = workNum;
            int r = 10;
            bool stop = false;
            int round = 0;
            while(!stop && round < 300) {
                for(auto c : cs) c->beforeUpdate();
                int k = ps.size() / num + 1;
                for(int i = 0; i < num; ++i) {
                    int s = k * i;
                    s = s < ps.size() ? s : ps.size() - 1;
                    int e = s + k;
                    e = e <= ps.size() ? e : ps.size();
                    works.push_back(new std::thread(&KMeans::doRound, this, s, e));
                }
                for(auto t : works) t->join();
                works.clear();
                // Calculate the new center.
                for(int i = 0; i < ps.size(); ++i) {
                    p2c[i]->update(*ps[i]);
                }
                bool flag = true;
                for(auto c : cs) {
                    flag &= (c->finishUpdate() < 0.0001);
                }
                
                // Calculate the new distance.
                for(int i = 0; i < ps.size(); ++i) {
                    ds[i] = *p2c[i] - *ps[i];
                }
                stop = flag;
                ++round;
                //std::cout << "---one round---" << std::endl;
            }
            std::cout << round << std::endl;
        }
        void outputCenters() {
            std::cout << "-------------centers" << std::endl;
            for(auto c : cs) c->center->output();
        }
        void output(std::string filename) {
            std::ofstream fo(filename);
            for(auto c : p2c) fo << c->id << std::endl;
            fo.close();
            //for(auto c : cs) c->center->output();
            //std::cout << "-------------detail" << std::endl;
            //for(int i = 0; i < ps.size(); ++i) {
            //    ps[i]->output();
            //    p2c[i]->center->output();
            //    std::cout << ds[i] << std::endl << std::endl;
            //}
        }

};

#endif
