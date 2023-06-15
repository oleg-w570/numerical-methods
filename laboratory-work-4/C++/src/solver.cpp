// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "solver.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

Solver::Solver(int n, int m, double eps, int maxiter, int K)
        : n(n), m(m), eps(eps), maxiter(maxiter), K(K) {
    niter = 0;
    accuracy = 1;
    maxdiff = 0;

    CalculateGrid();
    CalculateGU();
    CalculateTrueSolution();
    CalculateChebishevParameters();
    initialR = CalculateDiscrepancy();
}

void Solver::CalculateTrueSolution() {
    u = std::vector<std::vector<double>>(n + 1, std::vector<double>(m + 1));
    int borderBottom = m / 4;
    int borderTop = 3 * m / 4;
    int borderRight = 7 * n / 8;
    int borderInsideLeft = n / 4;
    int borderInsideRight = n / 2;

    for (int j = 0; j <= borderBottom; j++) {
        u[n][j] = task.U(task.b, y[j]);
    }
    for (int j = borderBottom; j <= borderTop; j++) {
        u[borderRight][j] = task.U(x[borderRight], y[j]);
    }
    for (int j = borderTop; j < m + 1; j++) {
        u[n][j] = task.U(task.b, y[j]);
    }
    for (int i = borderRight; i < n + 1; i++) {
        u[i][borderBottom] = task.U(x[i], y[borderBottom]);
        u[i][borderTop] = task.U(x[i], y[borderTop]);
    }

    for (int j = borderBottom; j <= borderTop; j++) {
        u[borderInsideLeft][j] = task.U(x[borderInsideLeft], y[j]);
        u[borderInsideRight][j] = task.U(x[borderInsideRight], y[j]);
    }
    for (int i = borderInsideLeft; i <= borderInsideRight; i++) {
        u[i][borderBottom] = task.U(x[i], y[borderBottom]);
        u[i][borderTop] = task.U(x[i], y[borderTop]);
    }

    for (int i = 0; i < n + 1; i++) {
        u[i][0] = task.U(x[i], task.c);
        u[i][m] = task.U(x[i], task.d);
    }
    for (int j = 0; j < m + 1; j++) {
        u[0][j] = task.U(task.a, y[j]);
    }

    for (int j = 1; j < borderBottom; j++) {
        for (int i = 1; i < n; i++) {
            u[i][j] = task.U(x[i], y[j]);
        }
    }
    for (int j = borderBottom; j < borderTop + 1; j++) {
        for (int i = 1; i < borderInsideLeft; i++) {
            u[i][j] = task.U(x[i], y[j]);
        }
        for (int i = borderInsideRight + 1; i < borderRight; i++) {
            u[i][j] = task.U(x[i], y[j]);
        }
    }
    for (int j = borderTop + 1; j < m; j++) {
        for (int i = 1; i < n; i++) {
            u[i][j] = task.U(x[i], y[j]);
        }
    }
}

void Solver::CalculateGU() {
    v = std::vector<std::vector<double>>(n + 1, std::vector<double>(m + 1));
    int borderBottom = m / 4;
    int borderTop = 3 * m / 4;
    int borderRight = 7 * n / 8;
    int borderInsideLeft = n / 4;
    int borderInsideRight = n / 2;

    for (int j = 0; j <= borderBottom; j++) {
        v[n][j] = task.U(task.b, y[j]);
    }
    for (int j = borderBottom; j <= borderTop; j++) {
        v[borderRight][j] = task.U(x[borderRight], y[j]);
    }
    for (int j = borderTop; j < m + 1; j++) {
        v[n][j] = task.U(task.b, y[j]);
    }
    for (int i = borderRight; i < n + 1; i++) {
        v[i][borderBottom] = task.U(x[i], y[borderBottom]);
        v[i][borderTop] = task.U(x[i], y[borderTop]);
    }

    for (int j = borderBottom; j <= borderTop; j++) {
        v[borderInsideLeft][j] = task.U(x[borderInsideLeft], y[j]);
        v[borderInsideRight][j] = task.U(x[borderInsideRight], y[j]);
    }
    for (int i = borderInsideLeft; i <= borderInsideRight; i++) {
        v[i][borderBottom] = task.U(x[i], y[borderBottom]);
        v[i][borderTop] = task.U(x[i], y[borderTop]);
    }

    for (int i = 0; i < n + 1; i++) {
        v[i][0] = task.U(x[i], task.c);
        v[i][m] = task.U(x[i], task.d);
    }
    for (int j = 0; j < m + 1; j++) {
        v[0][j] = task.U(task.a, y[j]);
    }

}

void Solver::CalculateGrid() {
    h = (task.b - task.a) / n;
    k = (task.d - task.c) / m;
    x = std::vector<double>(n + 1);
    y = std::vector<double>(m + 1);

    double xi = task.a;
    for (int i = 0; i < n + 1; i++) {
        x[i] = xi;
        xi += h;
    }

    double yj = task.c;
    for (int j = 0; j < m + 1; j++) {
        y[j] = yj;
        yj += k;
    }
}

void Solver::CalculateChebishevParameters() {
    tau = std::vector<double>(K);
    double Mmin = 4 / (h * h) * std::sin(M_PI / (2 * n)) * std::sin(M_PI / (2 * n))
                  + 4 / (k * k) * std::sin(M_PI / (2 * m)) * std::sin(M_PI / (2 * m));
    double Mmax = 4 / (h * h) * std::sin(M_PI * (n - 1) / (2 * n)) * std::sin(M_PI * (n - 1) / (2 * n))
                  + 4 / (k * k) * std::sin(M_PI * (m - 1) / (2 * m)) * std::sin(M_PI * (m - 1) / (2 * m));

    for (int s = 0; s < K; s++) {
        double tmp = 0.5 * (Mmax + Mmin) + 0.5 * (Mmax - Mmin) * std::cos(M_PI * (1 + 2 * s) / (2 * K));
        tau[s] = 1 / tmp;
    }
}

double
Solver::VectorDiffNorm(const std::vector<std::vector<double>> &v1, const std::vector<std::vector<double>> &v2) const {
    double max_diff = 0;
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            const double curr_diff = std::abs(v1[i][j] - v2[i][j]);
            if (curr_diff > max_diff)
                max_diff = curr_diff;
        }
    }
    return max_diff;
}

std::vector<std::vector<double>> Solver::ChebishevLocalIteration(const std::vector<std::vector<double>> &vcurr, int s) {
    std::vector<std::vector<double>> vnew(vcurr);
    double t = tau[s];
    double h2 = 1 / (h * h);
    double k2 = 1 / (k * k);
    double A = -2 * (h2 + k2);
    int borderBottom = m / 4;
    int borderTop = 3 * m / 4;
    int borderRight = 7 * n / 8;
    int borderInsideLeft = n / 4;
    int borderInsideRight = n / 2;
    for (int j = 1; j < borderBottom; j++) {
        for (int i = 1; i < n; i++) {
            vnew[i][j] = vcurr[i][j] * (1 + t * A)
                         + t * (k2 * (vcurr[i][j - 1] + vcurr[i][j + 1]) + h2 * (vcurr[i - 1][j] + vcurr[i + 1][j]) -
                                task.F(x[i], y[j]));
        }
    }
    for (int j = borderBottom; j < borderTop + 1; j++) {
        for (int i = 1; i < borderInsideLeft; i++) {
            vnew[i][j] = vcurr[i][j] * (1 + t * A)
                         + t * (k2 * (vcurr[i][j - 1] + vcurr[i][j + 1]) + h2 * (vcurr[i - 1][j] + vcurr[i + 1][j]) -
                                task.F(x[i], y[j]));
        }
        for (int i = borderInsideRight + 1; i < borderRight; i++) {
            vnew[i][j] = vcurr[i][j] * (1 + t * A)
                         + t * (k2 * (vcurr[i][j - 1] + vcurr[i][j + 1]) + h2 * (vcurr[i - 1][j] + vcurr[i + 1][j]) -
                                task.F(x[i], y[j]));
        }
    }
    for (int j = borderTop + 1; j < m; j++) {
        for (int i = 1; i < n; i++) {
            vnew[i][j] = vcurr[i][j] * (1 + t * A)
                         + t * (k2 * (vcurr[i][j - 1] + vcurr[i][j + 1]) + h2 * (vcurr[i - 1][j] + vcurr[i + 1][j]) -
                                task.F(x[i], y[j]));
        }
    }
    return vnew;
}

std::vector<std::vector<double>> Solver::ChebishevGlobalIteration(const std::vector<std::vector<double>> &vnull) {
    std::vector<std::vector<double>> vres(vnull);
    for (int s = 0; s < K; s++) {
        vres = ChebishevLocalIteration(vres, s);
    }
    return vres;
}

void Solver::ChebishevMethod() {
    while (accuracy > eps && niter < maxiter) {
        std::vector<std::vector<double>> vprev(v);
        v = ChebishevGlobalIteration(vprev);
        accuracy = VectorDiffNorm(vprev, v);
        niter += K;
    }
}

void Solver::CalculateDiffSolutions() {
    diff = std::vector<std::vector<double>>(n + 1, std::vector<double>(m + 1));
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            const double currdiff = std::abs(u[i][j] - v[i][j]);
            diff[i][j] = currdiff;
            if (currdiff > maxdiff) {
                maxdiff = currdiff;
                maxdiffX = x[i];
                maxdiffY = y[j];
            }
        }
    }

}

double Solver::CalculateDiscrepancy() {
    double maxR = 0;
    double h2 = 1 / (h * h);
    double k2 = 1 / (k * k);
    double A = -2 * (h2 + k2);
    int borderBottom = m / 4;
    int borderTop = 3 * m / 4;
    int borderRight = 7 * n / 8;
    int borderInsideLeft = n / 4;
    int borderInsideRight = n / 2;
    for (int j = 1; j < borderBottom; j++) {
        for (int i = 1; i < n; i++) {
            double R = std::abs(A * u[i][j] + h2 * (u[i - 1][j] + u[i + 1][j]) + k2 * (u[i][j - 1] + u[i][j + 1]) -
                                task.F(x[i], y[j]));
            if (R > maxR)
                maxR = R;
        }
    }
    for (int j = borderBottom; j < borderTop + 1; j++) {
        for (int i = 1; i < borderInsideLeft; i++) {
            double R = std::abs(A * v[i][j] + h2 * (v[i - 1][j] + v[i + 1][j]) + k2 * (v[i][j - 1] + v[i][j + 1]) -
                                task.F(x[i], y[j]));
            if (R > maxR)
                maxR = R;
        }
        for (int i = borderInsideRight + 1; i < borderRight; i++) {
            double R = std::abs(A * v[i][j] + h2 * (v[i - 1][j] + v[i + 1][j]) + k2 * (v[i][j - 1] + v[i][j + 1]) -
                                task.F(x[i], y[j]));
            if (R > maxR)
                maxR = R;
        }
    }
    for (int j = borderTop + 1; j < m; j++) {
        for (int i = 1; i < n; i++) {
            double R = std::abs(A * v[i][j] + h2 * (v[i - 1][j] + v[i + 1][j]) + k2 * (v[i][j - 1] + v[i][j + 1]) -
                                task.F(x[i], y[j]));
            if (R > maxR)
                maxR = R;
        }
    }
    return maxR;
}

void Solver::Solve() {
    ChebishevMethod();
    CalculateDiffSolutions();
    resultR = CalculateDiscrepancy();
}

