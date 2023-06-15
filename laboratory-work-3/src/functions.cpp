#include "functions.h"

double TestFunc(double x) {
    if (x >= -1.0 && x <= 0.0)
        return x * x * x + 3.0 * x * x;
    else if (x >= 0.0 && x <= 1.0)
        return -x * x * x + 3.0 * x * x;
    return 0.0;
}

double MainFunc4(double x) {
    return log1p(x) / (x + 1.0);
}

double MainFunc3(double x) {
    return sin(x + 1.0) / (x + 1.0);
}

double MainFunc2(double x) {
    return pow(1.0 + x * x, 1.0 / 3.0);
}

double MainFunc1(double x) {
    return sqrt(x * x - 1.0) / x;
}

double dTF(double x) {
    return 0;
}

double d2TF(double x) {
    return 0;
}

double dF4(double x) {
    return (1 - log1p(x)) / ((x + 1.0) * (x + 1.0));
}

double d2F4(double x) {
    return (2 * log1p(x) - 3) / ((x + 1.0) * (x + 1.0) * (x + 1.0));
}

double dF1(double x) {
    return 0;
}

double d2F1(double x) {
    return 0;
}

double dF2(double x) {
    return 0;
}

double d2F2(double x) {
    return 0;
}

double dF3(double x) {
    return 0;
}

double d2F3(double x) {
    return 0;
}
