#ifndef __KMEANS_H__
#define __KMEANS_H__

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>

#include "point.h"
#include "cluster.h"

class KMeans {
    private:
        int size;
        std::vector<Point*> ps;
        std::vector<float> ds;
        std::vector<Cluster*> p2c;
        std::vector<Cluster*> cs;
        std::default_random_engine generator;

        float randomRange(float range) {
            std::uniform_real_distribution<float> distribution(0.0, range);
            return distribution(generator);
        }

    public:
        KMeans(int _size, std::vector<Point*> &_ps): size(_size), ps(_ps) {
            p2c.resize(ps.size());
            ds.resize(ps.size(), -1);
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            generator = std::default_random_engine(seed);
        }
        void initClusters() {
            // TODO choose center from all members.
            int r = static_cast<int>(randomRange(ps.size()));
            cs.push_back(new Cluster(ps[r]));

            std::vector<float> ds_tmp;
            ds_tmp.resize(ps.size(), 0);

            for(int j = 1; j < size; ++j) {
                float all = 0;
                for(int i = 0; i < ps.size(); ++i) {
                    for(auto c : cs) ds_tmp[i] += *c - *ps[i];
                    all += ds_tmp[i];
                }
                float random = randomRange(all);
                for(int i = 0; i < ds_tmp.size(); ++i) {
                    random -= ds_tmp[i];
                    if(random < 0) {
                        cs.push_back(new Cluster(ps[i]));
                        break;
                    }
                }
            }
            for(auto c : cs) c->center->output();
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
                //p2c[i]->update(*ps[i]);
            }
        }
        void parallel() {
        }
        void start() {
            initClusters();
            std::vector<std::thread*> works;
            int num = 4;
            int r = 10;
            while(--r) {
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
                    flag &= (c->finishUpdate() < 1);
                }
                
                // Calculate the new distance.
                for(int i = 0; i < ps.size(); ++i) {
                    ds[i] = *p2c[i] - *ps[i];
                }
                //stop = flag;
                std::cout << "---one round---" << std::endl;
            }
        }
        void outputCenters() {
            std::cout << "-------------centers" << std::endl;
            for(auto c : cs) c->center->output();
        }
        void output() {
            std::cout << "-------------centers" << std::endl;
            for(auto c : cs) c->center->output();
            //std::cout << "-------------detail" << std::endl;
            //for(int i = 0; i < ps.size(); ++i) {
            //    ps[i]->output();
            //    p2c[i]->center->output();
            //    std::cout << ds[i] << std::endl << std::endl;
            //}
        }

};

#endif
