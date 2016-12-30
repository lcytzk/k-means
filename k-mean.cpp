#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime> 

using namespace std;

class Point {
    public:
        virtual float operator-(const Point &td) const = 0;
};

class TD : public Point {
    protected:
        float x, y;

    public:
        TD(float _x, float _y): x(_x), y(_y) {}
        float operator-(const Point &td) const {
            const TD &td2 = static_cast<const TD&>(td);
            return sqrt(td2.x * td2.x + td2.y * td2.y);
        }

};

class Center : public Point {
    private:
        Point &p;

    public:
        Center(Point &_p):p(_p) {}
        float operator-(const Point &p2) const {
            return p - p2;
        }

};

void geneData(vector<Point*> ps) {
    for(int i = 0; i < 100; ++i) {
        ps.push_back(new TD(i, i));
    }
}

void outputCenters(vector<Center*> &centers) {}

void initCenters(vector<Point*> ps, vector<Center*> cs, int centerNum) {
    srand (time(NULL));
    int size = ps.size();
    for(int i = 0; i < centerNum; ++i) {
        int index = rand() % size;
        cs.push_back(new Center(*ps[i]));
    }
}

vector<Center*> k_means(vector<Point*> ps, int centerNum) {}

int main(int argc, char* argv[]) {
    vector<Point*> ps;
    geneData(ps);
    int centerNum = 2;
    auto centers = k_means(ps, centerNum);
    outputCenters(centers);
    return 0;
}
