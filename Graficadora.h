/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graficadora.h
 * Author: juan
 *
 * Created on August 16, 2020, 9:11 PM
 */

#ifndef GRAFICADORA_H
#define GRAFICADORA_H
#define MIN std::numeric_limits<double>::min()
#define MAX std::numeric_limits<double>::max()

#include <limits>
#include <iostream>
#include "stdio.h"
#include "cairo/cairo.h"
#include <math.h>
#include "vector"
#include "point.h"


using namespace std;
typedef unsigned char pixel ;

void generateGraphics(vector<vector<pixel>> &pixels, vector<vector<pixel>> &originalPixels, vector<point> &biffPoints);
#endif /* GRAFICADORA_H */

