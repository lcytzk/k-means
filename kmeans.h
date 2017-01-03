#ifndef __KMEANS_H__
#define __KMEANS_H__

#include <vector>

#include "TD.h"
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
        KMeans(int _size): size(_size) {
            //cs.resize(size);
        }
        void initClusters() {
            // TODO
            cs.push_back(new Cluster(new TD(-1,-1)));
            cs.push_back(new Cluster(new TD(1000,1000)));

            for(int i = 0; i < 1000; ++i) {
                ps.push_back(new TD(i, i));
            }
            p2c.resize(ps.size());
            ds.resize(ps.size(), -1);
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
            for(auto c : cs) c->center->output();
        }

};

#endif
