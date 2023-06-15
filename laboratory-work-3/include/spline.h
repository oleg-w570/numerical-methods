#pragma once

#include <vector>
#include <cmath>


struct Spline {
    std::vector<double> A;
    std::vector<double> B;
    std::vector<double> C;
    std::vector<double> D;
    std::vector<double> grid;
    int size;

    int indOf(double x);

    double operator()(double x);

    double d(double x);

    double d2(double x);
};
