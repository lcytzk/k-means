#ifndef __TD_H__
#define __TD_H__

#include <iostream>
#include <cmath>

#include "point.h"

class TD : public Point {
    private:
        float x, y;

    public:
        TD(float _x, float _y): x(_x), y(_y) {}
        float operator-(const Point &p) const {
            const TD &t = static_cast<const TD&>(p);
            return sqrt(pow(x - t.x, 2) + pow(y - t.y, 2));
        }
        Point* duplicate() {
            return new TD(x, y);
        }
        Point* newOne() {
            return new TD(0, 0);
        }
        void add(Point &p) {
            const TD &t = static_cast<const TD&>(p);
            x += t.x;
            y += t.y;
        }
        void divide(int k) {
            x /= k;
            y /= k;
        }
        void output() {
            std::cout << x << ' ' << y << std::endl;
        }

};

#endif
