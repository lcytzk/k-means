#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include "point.h"

class Cluster {
    friend class KMeans;
    private:
        Point *center;
        Point *newCenter;
        int size = 0;
        int id;

    public:
        Cluster(Point *p, int _id): id(_id) {
            center = p->duplicate();
        }
        void beforeUpdate() {
            newCenter = center->newOne();
            size = 0;
        }
        void update(Point &p) {
            newCenter->add(p);
            ++size;
        }
        float finishUpdate() {
            if(!size) {
                delete newCenter;
                return 0;
            }
            newCenter->divide(size);
            float d = *newCenter - *center;
            delete center;
            center = newCenter;
            return d;
        }
        float operator-(const Point &p) const {
            return *center - p;
        }
};

#endif
