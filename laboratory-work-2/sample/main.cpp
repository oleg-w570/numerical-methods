#include "tridiagonal_matrix_algorithm.h"
#include "functions.h"
#include "solver.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    Solver S;
    int n = 10000;
    MODE mode = TEST;
    S.calculate(n, mode);
    std::vector<double> res1 = S.getNumSolution();
    std::vector<double> true_res = S.getSecondSolution();
    S.calculate(2*n, mode);
    std::vector<double> res2 = S.getNumSolution();
    std::vector<double> eps(n);
    for (int i = 0; i < n; i++)
    {
        eps[i] = abs(res1[i]-res2[i*2]);
    }
    auto max_eps = max_element(eps.begin(), eps.end());


    double x = 0.0;
    cout << endl << "solution" << endl;
    for (int i = 0; i < res1.size(); i++)
    {
        cout << "x = " << x << ",\tv = " << res1[i] << ", u = " << true_res[i] << ", |u-v| = " << abs(true_res[i]-res1[i]) << endl;
        x += 1.0 / n;
    }
    cout << "eps = " << *max_eps << endl;
	return 0;
}
