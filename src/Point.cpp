#include <random>
#include <algorithm>
#include <iostream>
#include "Point.h"

using namespace std;

ostream& operator<<(ostream &os, const Point& pt)
{
        return os << "(" << pt.x << ", " << pt.y << ") ";
};

//note: return value optimization will avoid the copy
Point Point::random(int minX, int maxX, int minY, int maxY){
    static random_device rnd_device;
    static mt19937 eng {rnd_device()};
    static uniform_int_distribution<int> distX(minX, maxX);
    static uniform_int_distribution<int> distY(minY, maxY);
    Point p(distX(eng),distY(eng));    
    return p;
}

//note: return value optimization will avoid the copy
vector<Point> Point::fillVectorRandom(int size, int minX, int maxX, int minY, int maxY){
    
    vector<Point> result(size);
    auto gen = [minX, maxX, minY, maxY](){return Point::random(minX, maxX, minY, maxY);};
    generate(result.begin(), result.end(), gen);
    return result;
};

int Point::orientation(const Point& p, const Point& q, const Point& r){
    int y0 = (q.y-p.y);
    int y1 = (r.y-q.y);
    int x0 = (q.x-p.x);
    int x1 = (r.x-q.x);
    
    int y0x1 = y0 * x1;
    int y1x0 = y1 * x0;

    if(y0x1 == y1x0)
        return Point::ORIENTATION_COLINEAR;

    return y0x1 > y1x0 ? Point::ORIENTATION_CLOCKWISE : Point::ORIENTATION_COUNTERCLOCKWISE;
};

void Point::printVector(vector<Point> &p){
    for(auto const& value: p){
        cout << value << endl;
    }   
};

int Point::distSquared(const Point & a){
    return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);
}
