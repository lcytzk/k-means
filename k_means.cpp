#include <iostream>

#include "kmeans.h"
#include "TD.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<Point*> ps;
    KMeans ks(2, ps);
    ks.start();
    ks.output();
    return 0;
}
