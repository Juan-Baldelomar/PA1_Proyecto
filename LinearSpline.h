//
// Created by juan on 02/12/20.
//

#ifndef PROYECTO_PA1_LINEARSPLINE_H
#define PROYECTO_PA1_LINEARSPLINE_H

#include "vector"
#include "point.h"
#include "iostream"
struct point;
using namespace std;

class LinearSpline {
public:
    LinearSpline(){};
    vector<point> getSplineCurve(vector<point> &points);
};


#endif //PROYECTO_PA1_LINEARSPLINE_H
