#include "solver.h"

Solver::Solver(int n, const Problem &problem)
        : problem(problem), n(n) {
    step = (problem.b - problem.a) / n;

    double x = problem.a;
    while (x < problem.b - 1e-6) {
        spline.grid.push_back(x);
        F.push_back(problem.f(x));
        x += step;
    }
    spline.grid.push_back(problem.b);
    F.push_back(problem.f(problem.b));

    spline.A = std::vector<double>(n);
    spline.B = std::vector<double>(n);
    spline.C = std::vector<double>(n + 1);
    spline.D = std::vector<double>(n);
    spline.size = n;
}

void Solver::calcA() {
    spline.A = F;
    spline.A.erase(spline.A.begin());
}

void Solver::calcB() {
    for (int i = 0; i < spline.size; ++i) {
        spline.B[i] = (F[i + 1] - F[i]) / step + spline.C[i + 1] * step / 3 + spline.C[i] * step / 6;
    }
}

void Solver::calcC() {
    std::vector<double> AB(n - 1, step);
    std::vector<double> C(n - 1, -4 * step);
    std::vector<double> phi(n - 1);
    for (int i = 0; i < n - 1; i++) {
        phi[i] = -6 * (F[i + 2] - 2 * F[i + 1] + F[i]) / step;
    }

//    double mu1 = (2.5*F[0] - 6*F[1] + 4.5*F[2] - F[3]) / step / step;
//    double mu2 = (-F[n-3] + 4.5*F[n-2] - 6*F[n-1] + 2.5*F[n]) / step / step;

    spline.C = SolveTridiagonalMatrix(AB, C, AB, phi, {0.0, 0.0}, {problem.mu1, problem.mu2});
//    spline.C = SolveTridiagonalMatrix(AB, C, AB, phi, {-0.5, -0.5}, {mu1, mu2});
}

void Solver::calcD() {
    for (int i = 0; i < n; ++i) {
        spline.D[i] = (spline.C[i + 1] - spline.C[i]) / step;
    }
}

Spline Solver::getSpline() {
    calcC();
    calcA();
    calcB();
    calcD();
    spline.C.erase(spline.C.begin());
    return spline;
}
