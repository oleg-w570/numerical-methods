// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "test_task.h"
#include <cmath>

TestTask::TestTask() {
    a = -1;
    b = 1;
    c = -1;
    d = 1;
}

double TestTask::U(double x, double y) {
    return std::exp(1 - x * x - y * y);
}

double TestTask::F(double x, double y) {
    return -4 * (1 - x * x - y * y) * std::exp(1 - x * x - y * y);
}