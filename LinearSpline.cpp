//
// Created by juan on 02/12/20.
//

#include "LinearSpline.h"

vector<point> LinearSpline::getSplineCurve(vector<point> &points){
    int n = points.size();
    vector<point> returnLine;

    for (int i = 1; i<n; i++){
        point p = points[i];
        point q = points[i-1];
        double m = p.x!= q.x? (p.y-q.y)/(p.x-q.x) : 0;
        double p0 = p.y - m * p.x;

        if (m == 0){
            double a = p.y,  b = q.y;
            double y = a;
            int direction = a<b? 1 : -1;
            while (y!=b){
                returnLine.push_back(point(p.x, y));
                y+= direction;
            }
            returnLine.push_back(point(p.x, b));
        }else{
            double a = p.x < q.x? p.x : q.x,  b = q.x > p.x? q.x : p.x;
            double x = a;

            while(x<b){
                double fx = m*x + p0;
                returnLine.push_back(point(x, fx));
                x+= 1/10.0;
            }
            returnLine.push_back(point(b, m*b + p0));
        }
    }

    return  returnLine;
}