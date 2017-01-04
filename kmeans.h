#ifndef __KMEANS_H__
#define __KMEANS_H__

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "point.h"
#include "cluster.h"

class KMeans {
    private:
        int size;
        std::vector<Point*> ps;
        std::vector<float> ds;
        std::vector<Cluster*> p2c;
        std::vector<Cluster*> cs;

    public:
        KMeans(int _size, std::vector<Point*> &_ps): size(_size), ps(_ps) {
            p2c.resize(ps.size());
            ds.resize(ps.size(), -1);
        }
        void initClusters() {
            // TODO choose center from all members.
            srand(time(0));
            cs.push_back(new Cluster(ps[0]));

            std::vector<float> ds_tmp;
            ds_tmp.resize(ps.size(), 0);

            for(int j = 1; j < size; ++j) {
                float all = 0;
                for(int i = 0; i < ps.size(); ++i) {
                    for(auto c : cs) ds_tmp[i] += *c - *ps[i];
                    all += ds_tmp[i];
                }
                float random = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/all));
                std::cout << random << '\t' << all << std::endl;
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
        void start() {
            initClusters();
            bool stop = false;
            while(!stop) {
                for(auto c : cs) c->beforeUpdate();
                // Find the nearest center for every point.
                for(int i = 0; i < ps.size(); ++i) {
                    for(auto c : cs) {
                        float d = *c - *ps[i];
                        if((ds[i] == -1) || (d < ds[i])) {
                            p2c[i] = c;
                            ds[i] = d;
                        }
                    }
                    p2c[i]->update(*ps[i]);
                }
                bool flag = true;
                // Calculate the new center.
                for(auto c : cs) {
                    flag &= (c->finishUpdate() < 0.1);
                }
                // Calculate the new distance.
                for(int i = 0; i < ps.size(); ++i) {
                    ds[i] = *p2c[i] - *ps[i];
                }
                stop = !flag;
            }
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
