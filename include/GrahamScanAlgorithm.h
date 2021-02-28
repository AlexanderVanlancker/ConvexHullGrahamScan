#pragma once

#ifndef GRAHAMSCANALGORITHM_H
#define GRAHAMSCANALGORITHM_H

#include "ConvexHullAlgorithm.h"
#include <stack>

class GrahamScanAlgorithm : ConvexHullAlgorithm{

    public:
        vector<Point> findConvexHull(vector<Point> &) const;
        static Point nextToTop(stack<Point>&);
};

#endif