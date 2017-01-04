#include <iostream>
#include <vector>
#include <cstdlib>

#include "kmeans.h"
#include "point.h"
#include "TD.h"

using namespace std;

void geneData(vector<Point*> &ps) {
    for(int i = 0; i < 20; ++i) ps.push_back(new TD(i, i));
}

int main(int argc, char* argv[]) {
    vector<Point*> ps;
    geneData(ps);
    KMeans ks(atoi(argv[1]), ps);
    ks.start();
    ks.output();
    return 0;
}
