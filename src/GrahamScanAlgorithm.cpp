
#include "GrahamScanAlgorithm.h"
#include <stack>
#include <iostream>
#include <Point.h>

Point p0;

bool comparePolarAngle(const Point &p1, const Point &p2){ //p1<p2 ? true : false;
    if(Point::orientation(p0, p1, p2) == Point::ORIENTATION_COLINEAR){
        return p0.distSquared(p1) < p0.distSquared(p2) ? true : false; 
    }
    
    return Point::orientation(p0,p1,p2) == Point::ORIENTATION_COUNTERCLOCKWISE ? true : false;
}

vector<Point> GrahamScanAlgorithm::findConvexHull(vector<Point> &points) const{
    vector<Point> hullpoints;

    if(points.size()<3)
        return hullpoints;
    
    //Step1: find element with minimum Y coordinate, and put it at the beginning of the vector.
    int minY=0;
    for(int i=1; i<points.size(); i++){
        if(points[i].y < points[minY].y)
            minY = i;
        else if(points[i].y == points[minY].y && points[i].x < points[minY].x)
            minY = i;
    }
    swap(points[0], points[minY]);
    p0 = points[0];

    //Step2: sort all but first element by polar angle. If two points have same angle, only keep the point with the largest distance.
    std::sort(points.begin()+1, points.end(), comparePolarAngle);

    
    for(int i=1; i<points.size()-1; i++){
        if(Point::orientation(p0,points[i],points[i+1]) == Point::ORIENTATION_COLINEAR){
            if(p0.distSquared(points[i]) < p0.distSquared(points[i+1]))
                points.erase(points.begin() + i);
            else
                points.erase(points.begin() + i+1);
        }
    }
    
    //Step3: construct convex hull using method orientation and stack
    std::stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    for(int i=3;i<points.size();i++){
        while(Point::orientation(nextToTop(hull),hull.top(),points[i]) != Point::ORIENTATION_COUNTERCLOCKWISE){
            hull.pop();
        }
        hull.push(points[i]);
    }
    
    //Step4: convert into vector and reverse orde so that point with minimum Y-coordinate comes first
    while(!hull.empty()){
        hullpoints.push_back(hull.top());
        hull.pop();
    }
    std::reverse(hullpoints.begin(),hullpoints.end());

    return hullpoints;
};


/*Helper method that returns second element from stack, while leaving the stack unmodified*/
/*Static method for educational purposes, as it allows for easier testing*/
Point GrahamScanAlgorithm::nextToTop(stack<Point>& s){
    Point top = s.top();
    s.pop();
    Point next = s.top();
    s.push(top);
    return next;
}
