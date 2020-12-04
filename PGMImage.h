//
// Created by juan on 14/11/20.
//

#ifndef MN_T9_PGMIMAGE_H
#define MN_T9_PGMIMAGE_H

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;
class PGMImage {
private:
    bool hasHeader = false;
    int nRows = -1;
    int nCols = -1;
    int max = -1;
    vector<vector<unsigned char>> transpose;




public:
    PGMImage(string filename);
    void writeFile(string filename);
    void showData();
    vector<vector<unsigned char>> pixels;
    int getCols();
    int getRows();


};

#endif //MN_T9_PGMIMAGE_H
