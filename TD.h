#ifndef __TD_H__
#define __TD_H__

#include <iostream>
#include <cmath>
#include <vector>

#include "point.h"

class TD : public Point {
    private:
        std::vector<float> dimensions;

    public:
        TD(float k) {
            for(int i = 0; i < 64; ++i) dimensions.push_back(k);
        }
        float operator-(const Point &p) const {
            const TD &t = static_cast<const TD&>(p);
            float f = 0;
            for(int i = 0; i < dimensions.size(); ++i) f += pow(dimensions[i] - t.dimensions[i], 2);
            return sqrt(f);
        }
        Point* duplicate() {
            return new TD(dimensions[0]);
        }
        Point* newOne() {
            return new TD(0);
        }
        void add(Point &p) {
            const TD &t = static_cast<const TD&>(p);
            for(int i = 0; i < dimensions.size(); ++i) dimensions[i] += t.dimensions[i];
        }
        void divide(int k) {
            for(auto & f : dimensions) f /= k;
        }
        void output() {
            std::cout << dimensions[0] << std::endl;
        }

};

#endif
