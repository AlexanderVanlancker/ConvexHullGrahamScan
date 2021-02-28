#pragma once

#ifndef CONVEXHULLALGORITHM_H
#define CONVEXHULLALGORITHM_H

#include "Point.h"
#include <vector>

using namespace std;

class ConvexHullAlgorithm {   
    public: 
        virtual vector<Point> findConvexHull(vector<Point> &) const = 0;
};

#endif