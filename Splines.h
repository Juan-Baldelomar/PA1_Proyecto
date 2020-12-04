//
// Created by juan on 28/11/20.
//

#ifndef PROYECTO_PA1_SPLINES_H
#define PROYECTO_PA1_SPLINES_H

#include <vector>
#include "Tools.h"
#include "point.h"

using namespace std;

typedef vector<point> line;

class Splines {
private:
    vector<vector<double>>M, RM;
    vector<vector<double>>x_, Rx_;
    vector<vector<double>>f_, Rf_;

public:
    Splines(vector<double> &x_, vector<double> &f_);
    void buildSplineSegment(vector<double> &x_, vector<double> &f_);
    void rotateAxixSplineSegment(vector<double> &x_, vector<double >&f_);
    vector<point> getCurve();
    vector<point> getVerticalCurve();
    double P(double x, int i, int row);
    double RP(double x, int i, int row);
    double reverseP(double x, int i);
};


#endif //PROYECTO_PA1_SPLINES_H
