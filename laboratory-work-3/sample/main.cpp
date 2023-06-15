#include "solver.h"
#include "functions.h"
#include <iostream>

using namespace std;

int main() {
    Problem TestTask(TestFunc, -1.0, 1.0, 0.0, 0.0);
    Problem Task1(MainFunc1, 2.0, 4.0, 0.0, 0.0);
    Problem Task2(MainFunc2, 0.0, 1.0, 0.0, 0.0);
    Problem Task3(MainFunc3, 0.0, 2.0, 0.0, 0.0);
    Problem Task4(MainFunc4, 0.2, 2.0, 0.0, 0.0);
    Solver Sol(5, Task4);
    Spline S = Sol.getSpline();

    double x = Task4.a;
    int i = 0;
    double step = (Task4.b - Task4.a) / 10;
    while (x <= Task4.b) {
        cout << "x=" << x << " (i=" << i << ")\tSi(x)=" << S(x) << endl;
        x += step;
        i++;
    }


    return 0;
}