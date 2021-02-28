#pragma once

#ifndef POINT_H
#define POINT_H
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

class Point{
    public:
    static const int ORIENTATION_COLINEAR=0;
    static const int ORIENTATION_CLOCKWISE=1;
    static const int ORIENTATION_COUNTERCLOCKWISE=2;    
    int x;
    int y;
    

    Point() {}
    Point(int X, int Y){        
        x=X;
        y=Y;
    }
    
    bool operator==(const Point &p) const {return (x==p.x) && (y==p.y); }

    friend ostream& operator<<(ostream & os, const Point& pt);
    
    int distSquared(const Point & q);    
    static vector<Point> fillVectorRandom(int size, int minX, int maxX, int minY, int maxY);    
    static Point random(int minX, int maxX, int minY, int maxY);
    static int orientation(const Point& p, const Point& q, const Point& r);    
    static void printVector(vector<Point> &p);
};




#endif