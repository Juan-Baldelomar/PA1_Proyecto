//
// Created by juan on 27/11/20.
//

#ifndef PROYECTO_PA1_IMGPROCESSING_H
#define PROYECTO_PA1_IMGPROCESSING_H

#include "vector"
#include "iostream"
#include <queue>
#include "Splines.h"
#include "point.h"
#include "LinearSpline.h"

using namespace std;

typedef unsigned char pixel;



struct Pattern{
public:
    pixel matrix[3][3];
    pixel p8 = '-', p9 = '-';
    Pattern();
    Pattern(int i_c, int j_c, vector<vector<pixel>> &pixels);
    void setValues(pixel values[3][3]);
    void print();
};

struct specialPattern{
public:
    pixel matrix[5][5];
    void setValues(pixel values[4][4]);
};

typedef vector<point> line;
class ImgProcessing{

private:
    vector<vector<pixel>> extractPixels(vector<vector<pixel>> &pixels);

     //get points and draw them
    void cleanLines(unsigned int limit=2);
    void getBiffurcations();
    vector<point> getNeighbors(point &current, vector<vector<pixel>> &pixels);
    bool criticPointExists(point p);

     //douglas Peucker
    void splitLine(line &l, line &l1, line &l2, int start, int split_index, int end);
    void mergeLine(line &l1, line &l2, line &result);

public:
    Pattern A, B, C, D, E, F, G, H, I, J, K, L, M, N, MIDDLE;
    specialPattern O, P, Q, S;
    vector<line> lines, originalLines;
    vector<point> criticPoints;                     // start, end and biffurcation points
    vector<double> errors;

    ImgProcessing();
    void setPatterns();
    char getPattern(Pattern &patt);
    void getSkeleton(vector<vector<pixel>> &pixels);

    //get points and draw them
    void getPoints(vector<vector<pixel>> &pixels);
    void drawLines(vector<vector<pixel>> &pixels);
    void printLines();
    vector<vector<pixel>> getPixelsMatrix(char code, int n, int m);        //code = 'O' -> original; 'S' splines


    //douglas Peucker
    line DouglasPeucker(line &l, double epsilon);
    void DecimateLines(double epsilon);

    // visvalingam
    void DecimateVisvalingam(double epsilon);
    void visvalingam(line &l, double epsilon);

    void hausdorff();

    //splines
    void getSplinesLines();
    vector<double> generateXVector(line l);
    vector<double> generateYVector(line l);
};

bool operator ==( Pattern& A,  Pattern &B);
bool operator ==(const specialPattern& A, const specialPattern &B);
bool operator !=(point &p, point &q);
bool operator ==(point &p, point &q);

#endif //PROYECTO_PA1_IMGPROCESSING_H
