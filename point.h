#ifndef __POINT_H__
#define __POINT_H__

#include <string>

class Point {
    friend class KMeans;
    protected:
        std::string label;
    public:
        virtual float operator-(const Point &p) const = 0;
        virtual Point* duplicate() = 0;
        virtual Point* newOne() = 0;
        virtual void add(Point &p) = 0;
        virtual void divide(int k) = 0;
        virtual void output() = 0;
};

#endif
