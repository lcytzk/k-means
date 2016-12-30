#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime> 

using namespace std;

class Coordinate {
    public:
        virtual operator-(const Coordinate &coor) const = 0;
};

class TD : Coordinate {
    protected:
        float x, y;

    public:
        TD(float _x, float _y): x(_x), y(_y) {}
        TD(TD& td): x(td.x), y(td.y) {}
        float operator-(const Coordinate &td) const {
            const TD &td2 = static_cast<const TD&>(td);
            return sqrt(td2.x * td2.x + td2.y * td2.y);
        }

};

template<typename T>
class Point {
    friend class Center;
    private:
        float distance = -1;
        T coor;
    public:
        Point(T &_coor): coor(_coor) {}
        float operator-(const T &coor2) const {
            return coor - coor2;
        }
        
};

template<typename T>
class Center {
    private:
        // Center's coordinate.
        T coor;
        T buff;
        // Center's cluster.
        vector<T*> *ps;

    public:
        Center(T &_coor):coor(_coor) {
            ps = new vector<T*>();
        }
        float operator-(const T &coor2) const {
            return coor - coor2;
        }
        void updateMember(T *coor2) {
            float dis = coor - *coor2;
            if(dis < p->distance) {
                ps->push_back(p);
                p->distance = dis;
            }
        }
        void countDiff(Point *p) {

        }

};

void geneData(vector<Point<TD>*> ps) {
    for(int i = 0; i < 100; ++i) {
        ps.push_back(new TD(i, i));
    }
}

void outputCenters(vector<Center<TD>*> &centers) {}

void initCenters(vector<Point<TD>*> ps, vector<Center<TD>*> cs, int centerNum) {
    srand(time(NULL));
    int size = ps.size();
    for(int i = 0; i < centerNum; ++i) {
        int index = rand() % size;
        cs.push_back(new Center<TD>(*ps[i]));
    }
}

void k_means(vector<Point<TD>*> ps, int centerNum, vector<Center<TD>*> cs) {
    initCenters(cs);
    int round = 1;
    while(round--) {
        for(Point *p : ps) {
            for(Center *c : cs) {
                c->updateMember(p);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    vector<Point*> ps;
    vector<Center<TD>*> cs;
    geneData(ps);
    int centerNum = 2;
    auto centers = k_means(ps, centerNum, cs);
    outputCenters(centers);
    return 0;
}
