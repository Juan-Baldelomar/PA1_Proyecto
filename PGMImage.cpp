//
// Created by juan on 14/11/20.
//

#include "PGMImage.h"
#include <bits/stdc++.h>
#include "Tools.h"

PGMImage::PGMImage(string filename) {
    ifstream file(filename);
    stringstream caster;
    string line;

    // verificar que archivo se pueda abrir
    if (!file.good()) {
        cout << "ERROR OPENING FILE IMG: " << filename << endl;
        return;
    }

    //read header
    while (getline(file, line)) {
        if (line.at(0) == '#')                                  //ignore comment
            continue;

        if (!hasHeader) {
            if (line.at(0) != 'P' && line.at(1) != '2') {
                cout << "ERROR: NO HEADER " << endl;
                return;
            }
            hasHeader = true;
            continue;
        }
        if (nRows == -1 && nCols == -1) {
            stringstream ss(line);
            string splitLine;
            getline(ss, splitLine, ' ');
            caster << splitLine;
            caster >> nCols;

            caster.clear();
            getline(ss, splitLine, ' ');
            caster << splitLine;
            caster >> nRows;
            pixels.assign(nRows, vector<unsigned char>(nCols, 0));
            transpose.assign(nCols, vector<unsigned char>(nRows, 0));
            continue;
        } else if (max == -1) {
            caster.clear();
            caster << line;
            caster >> max;
        }
        break;
    }

    //read data
    unsigned int number, i = 0, j = 0;
    while(getline(file, line)){
        stringstream ss(line);
        string splitLine;
        while(getline(ss, splitLine, ' ')){
            caster.clear();
            caster << splitLine;
            caster >> number;
            pixels[i][j] = number;

            j++;
            if (j%nCols == 0){
                j = 0;
                i++;
            }
        }
    }

    file.close();
}

void PGMImage::writeFile(string filename) {
    ofstream file(filename);
    file << "P2\n";
    file << "# IMG by Juan Luis" << endl;
    file << nCols << " " << nRows << endl;
    file << max << endl;

    //write data
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            file << (unsigned int) pixels[i][j] << endl;
        }
    }
    cout << "IMG writen successful" << endl;
    file.close();
}

void PGMImage::showData() {
    cout << "rows: " << nRows << endl;
    cout << "cols: " << nCols << endl;
    cout << "max: " << max << endl;
    cout << pixels << endl;
}

int PGMImage::getCols() {
    return nCols;
}

int PGMImage::getRows() {
    return nRows;
}