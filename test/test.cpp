#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include <algorithm>
#include "Point.h"
#include "GrahamScanAlgorithm.h"
#include <vector>

void helperDistance(Point const& myObj);

TEST_CASE("Squared distance between points is correctly calculated","[Point]"){
    
    Point p1(100,200);
    Point p2(200,200);
    Point p3(300,350);
    Point p4(300,200);
    Point p5(350,100);

    REQUIRE(p1.distSquared(p2) == 10000);
    REQUIRE(p2.distSquared(p1) == 10000);
    REQUIRE(p2.distSquared(p3) == 32500);   
    
}

TEST_CASE("Orientation between points is correctly calculated","[Point]"){
    
    Point p1(100,200);
    Point p2(200,200);
    Point p3(300,350);
    Point p4(300,200);
    Point p5(350,100);

    int out1 = Point::orientation(p1,p2,p4);
    int out2 = Point::orientation(p1,p2,p3);
    int out3 = Point::orientation(p3,p2,p1);
    int out4 = Point::orientation(p3,p2,p1);
    int out5 = Point::orientation(p3,p2,p5);

    int colinear = Point::ORIENTATION_COLINEAR;
    int counterclock = Point::ORIENTATION_COUNTERCLOCKWISE;
    int clock = Point::ORIENTATION_CLOCKWISE;

    REQUIRE(out1 == colinear);
    REQUIRE(out2 == counterclock);
    REQUIRE(out3 == clock);
    REQUIRE(out4 == clock);
    REQUIRE(out5 == counterclock);
    
}

// TEST_CASE("Orientation between points is correctly calculated","[Point]"){
    
//     Point p1(100,200);
//     Point p2(200,200);
//     Point p3(300,350);
//     Point p4(300,200);
//     Point p5(350,100);

//     REQUIRE(Point::orientation(p1,p2,p4) == Point::ORIENTATION_COLINEAR);
//     REQUIRE(Point::orientation(p1,p2,p3) == Point::ORIENTATION_COUNTERCLOCKWISE);
//     REQUIRE(Point::orientation(p3,p2,p1) == Point::ORIENTATION_CLOCKWISE);
//     REQUIRE(Point::orientation(p3,p2,p1) == Point::ORIENTATION_CLOCKWISE);
//     REQUIRE(Point::orientation(p3,p2,p5) == Point::ORIENTATION_COUNTERCLOCKWISE);
    
// }

TEST_CASE("Method nextToTop correctly returned and removed from stack","[GrahamScanAlgorithm]"){
    Point p1(100,200);
    Point p2(200,200);
    Point p3(300,350);
    Point p4(300,200);
    Point p5(350,100);
    stack<Point>s;
    s.push(p1);
    s.push(p2);
    s.push(p3);
    s.push(p4);
    s.push(p5);

    Point res = GrahamScanAlgorithm::nextToTop(s);    
    REQUIRE(res==p4);
    REQUIRE(s.top() == p5);

    //repeat to check if second element was not popped from stack!
    res = GrahamScanAlgorithm::nextToTop(s);
    REQUIRE(res==p4);
    REQUIRE(s.top()==p5);    
}

TEST_CASE("Convex Hull correctly calculated","[GrahamScanAlgorithm]"){
    //include all edge cases: similar points with minimum Y coordinate, points with same polar angle, straight line on convex hull, internal points...
    Point p0(500,100);
    Point p1(550,100); //same minimum Y coordinate
    Point p2(600,150); //lies on straight line with p2
    Point p3(650,200);
    Point p4(525,130);
    Point p5(625,250); //same polar angle with P0 as P4.
    Point p6(580,225); //point that is first added and then removed from convex hull, together with next point
    Point p7(535,195); //point that is first added and then removed from convex hull
    Point p8(400,300);
    Point p9(300,150);
    Point p10(475,175); //internal point

    vector<Point> points;
    points.push_back(p0);
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
    points.push_back(p7);
    points.push_back(p8);
    points.push_back(p9);
    points.push_back(p10);
    random_shuffle(points.begin(),points.end());

    GrahamScanAlgorithm algo;
    vector<Point> hull = algo.findConvexHull(points);
    REQUIRE(hull.size() == 6);
    REQUIRE(hull[0] == p0);
    REQUIRE(hull[1] == p1);
    REQUIRE(hull[2] == p3);
    REQUIRE(hull[3] == p5);
    REQUIRE(hull[4] == p8);
    REQUIRE(hull[5] == p9);    

}