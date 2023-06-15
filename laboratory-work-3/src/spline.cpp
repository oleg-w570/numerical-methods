#include "spline.h"

double Spline::operator()(double x) {
    int i = indOf(x);
    return A[i] + B[i] * (x - grid[i + 1]) + C[i] * (x - grid[i + 1]) * (x - grid[i + 1]) / 2 +
           D[i] * (x - grid[i + 1]) * (x - grid[i + 1]) * (x - grid[i + 1]) / 6;
}

double Spline::d(double x) {
    int i = indOf(x);
    return B[i] + C[i] * (x - grid[i + 1]) + D[i] * (x - grid[i + 1]) * (x - grid[i + 1]) / 2;
}

double Spline::d2(double x) {
    int i = indOf(x);
    return C[i] + D[i] * (x - grid[i + 1]);
}

int Spline::indOf(double x) {
    int l = -1;
    int r = grid.size() - 1;
    while (l < r - 1) {
        int m = (l + r) / 2;
        if (grid[m] < x || std::abs(grid[m] - x) < 1e-8)
            l = m;
        else
            r = m;
    }
    return l;
}
