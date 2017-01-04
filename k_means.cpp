#include <iostream>
#include <vector>
#include <cstdlib>

#include "kmeans.h"
#include "point.h"
#include "TD.h"

using namespace std;

void geneData(vector<Point*> &ps, int size) {
    for(int i = 0; i < size; ++i) ps.push_back(new TD(i));
}

int main(int argc, char* argv[]) {
    vector<Point*> ps;
    geneData(ps, atoi(argv[2]));
    KMeans ks(atoi(argv[1]), ps);
    ks.start();
    ks.output();
    return 0;
}
