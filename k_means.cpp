#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Point {
    public:
        virtual float operator-(const Point &p) const = 0;
        virtual Point* duplicate() = 0;
        virtual Point* newOne() = 0;
        virtual void add(Point &p) = 0;
        virtual void divide(int k) = 0;
        virtual void output() = 0;
};

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
            cout << x << ' ' << y << endl;
        }

};

class Cluster {
    friend class KMeans;
    private:
        Point *center;
        Point *newCenter;
        int size = 0;

    public:
        Cluster(Point *p): center(p) {}
        void beforeUpdate() {
            newCenter = center->newOne();
            size = 0;
        }
        void update(Point &p) {
            newCenter->add(p);
            ++size;
        }
        float finishUpdate() {
            newCenter->divide(size);
            float d = newCenter - center;
            delete center;
            center = newCenter;
            return d;
        }
        float operator-(const Point &p) const {
            return *center - p;
        }
};

class KMeans {
    private:
        int size;
        vector<Point*> ps;
        vector<float> ds;
        vector<Cluster*> p2c;
        vector<Cluster*> cs;

    public:
        KMeans(int _size): size(_size) {
            //cs.resize(size);
        }
        void initClusters() {
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
            cout << "finish" << endl;
            for(auto c : cs) c->center->output();
        }

};

int main(int argc, char* argv[]) {
    KMeans ks(2);
    ks.start();
    ks.output();
    return 0;
}
