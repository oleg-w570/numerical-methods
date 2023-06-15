#pragma once

#include "tridiagonal_matrix_algorithm.h"
#include "problems.h"
#include "spline.h"
#include <vector>

class Solver {
    Problem problem;
    Spline spline;
    int n;
    double step;
    std::vector<double> F;

public:
    Solver(int n, const Problem &problem);

    void calcA();

    void calcB();

    void calcC();

    void calcD();

    Spline getSpline();
};