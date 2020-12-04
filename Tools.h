//
// Created by juan on 23/10/20.
//

#ifndef MN_T9_TOOLS_H
#define MN_T9_TOOLS_H
#include <vector>
#include <iostream>
#include "fstream"
#include <iomanip>
#include <vector>
using namespace std;
void ReadMatrix(vector<vector<double> > &M, string filename);
void ReadVector(vector<double> &V, string filename);
void WriteMatrix(const vector< vector<double > > &M, string filename, bool flag_append=false);
void WriteVector(const vector<double> &V, string filename, bool flag_append=false);
ostream &operator<<(ostream &os, const vector< vector<double> > &M);
ostream &operator<<(ostream &os, const vector<double> &V);
ostream &operator<<(ostream &os, const vector< vector<unsigned char> > &M);
ostream &operator<<(ostream &os, const vector<unsigned char> &V);
#endif //MN_T9_TOOLS_H
