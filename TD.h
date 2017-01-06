#ifndef __TD_H__
#define __TD_H__

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "split_string.h"
#include "point.h"

class TD : public Point {
    private:
        std::vector<float> dimensions;

    public:
        TD(float k, int s) {
            for(int i = 0; i < s; ++i) dimensions.push_back(k);
        }
        TD(TD &t) {
            label = t.label;
            dimensions = t.dimensions;
        }
        TD(std::vector<std::string> &ss) {
            label = ss[0];
            for(int i = 1; i < ss.size(); ++i) {
                dimensions.push_back(atof(ss[i].c_str()));
            }
        }
        float operator-(const Point &p) const {
            const TD &t = static_cast<const TD&>(p);
            float f = 0;
            for(int i = 0; i < dimensions.size(); ++i) f += pow(dimensions[i] - t.dimensions[i], 2);
            return sqrt(f);
        }
        Point* duplicate() {
            return new TD(*this);
        }
        Point* newOne() {
            return new TD(0, dimensions.size());
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
