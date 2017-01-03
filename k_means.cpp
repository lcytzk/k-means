#include <iostream>

#include "kmeans.h"

using namespace std;

int main(int argc, char* argv[]) {
    KMeans ks(2);
    ks.start();
    ks.output();
    return 0;
}
