#include "test_task.h"
#include <vector>

class Solver {
private:
    TestTask task;
    std::vector<double> tau;
    int K;
    double h, k;
    int n, m;
    double eps;
    int maxiter;
public:
    std::vector<std::vector<double>> u;
    std::vector<std::vector<double>> v;
    std::vector<std::vector<double>> diff;
    std::vector<double> x, y;
    double maxdiff, maxdiffX, maxdiffY;
    double initialR, resultR;
    double accuracy;
    int niter;

private:
    void CalculateTrueSolution();
    void CalculateGU();
    void CalculateGrid();
    void CalculateChebishevParameters();
    double VectorDiffNorm(const std::vector<std::vector<double>>& v1, const std::vector<std::vector<double>>& v2) const;
    std::vector<std::vector<double>> ChebishevLocalIteration(const std::vector<std::vector<double>>& vcurr, int s);
    std::vector<std::vector<double>> ChebishevGlobalIteration(const std::vector<std::vector<double>>& vnull);
    void ChebishevMethod();
    void CalculateDiffSolutions();
    double CalculateDiscrepancy();
public:
    explicit Solver(int n = 8, int m = 8, double eps = 1e-6, int maxiter = 10000, int K = 4);
    void Solve();
};