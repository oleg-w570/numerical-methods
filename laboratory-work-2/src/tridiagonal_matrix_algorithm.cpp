#include "tridiagonal_matrix_algorithm.h"

std::vector<double> SolveTridiagonalMatrix(const std::vector<double> &A,
                                           const std::vector<double> &C,
                                           const std::vector<double> &B,
                                           const std::vector<double> &Fi,
                                           const std::vector<double> &ae,
                                           const std::vector<double> &mu)
{
    const unsigned long long n = Fi.size() + 2;
    if (A.size() != n-2 || C.size() != n-2 || B.size() != n-2 || ae.size() != 2 || mu.size() != 2)
        throw std::logic_error("Wrong size of vectors!");

    std::vector<double> y(n);
    std::vector<double> alpha(n-1);
    std::vector<double> beta(n-1);

    alpha[0] = ae[0];
    beta[0] = mu[0];

    for (unsigned long long i = 0; i < n - 2; ++i)
    {
        alpha[i + 1] = B[i] / (C[i] - alpha[i] * A[i]);
        beta[i + 1] = (Fi[i] + A[i] * beta[i]) / (C[i] - alpha[i] * A[i]);
    }

    y[n - 1] = (mu[1] + beta[n - 2] * ae[1]) / (1 - alpha[n - 2] * ae[1]);

    for (long long i = n - 2; i >= 0; i--)
    {
        y[i] = alpha[i] * y[i+1] + beta[i];
    }

    return y;
}
