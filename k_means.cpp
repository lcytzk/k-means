#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>

#include "kmeans.h"
#include "point.h"
#include "TD.h"

using namespace std;

void geneData(vector<Point*> &ps, string &&filename) {
    ifstream fi(filename);
    string str;
    getline(fi, str);
    while(!fi.eof()) {
        getline(fi, str);
        if(str.size() < 2) break;
        vector<string> ss;
        splitString(str, ss, ' ');
        ps.push_back(new TD(ss));
    }
    fi.close();
    cout << "size is: " << ps.size() << endl;
}

int main(int argc, char* argv[]) {
    vector<Point*> ps;
    geneData(ps, string(argv[3]));
    int r = 300;
    if (argc > 5) {
        r = atoi(argv[5]);
    }
    KMeans ks(atoi(argv[1]), ps, atoi(argv[2]), r);
    ks.start();
    ks.output(argv[4]);
    return 0;
}
