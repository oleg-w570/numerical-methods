#pragma once

#include <vector>
#include <stdexcept>

std::vector<double>
SolveTridiagonalMatrix(const std::vector<double> &A,
                       const std::vector<double> &C,
                       const std::vector<double> &B,
                       const std::vector<double> &Fi,
                       const std::vector<double> &ae,
                       const std::vector<double> &mu);


