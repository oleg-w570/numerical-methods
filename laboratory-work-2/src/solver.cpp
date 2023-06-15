#include "solver.h"

Solver::Solver(double (**K)(double), double (**Q)(double), double (**F)(double), const double psi, const double a, const double b,
	const double initial_temp, const double final_temp)
	               : a(a), mu1(initial_temp), b(b), mu2(final_temp), psi(psi)
{
	if (K == nullptr)
	{
		K1 = [](double x) {return x * x + 2; };
		K2 = [](double x) {return x * x; };
	}
	else
	{
		K1 = K[0];
		K2 = K[1];
	}
	if (Q == nullptr)
	{
		Q1 = [](double x) {return x; };
		Q2 = [](double x) {return x * x; };
	}
	else
	{
		Q1 = Q[0];
		Q2 = Q[1];
	}
	if (F == nullptr)
	{
		F1 = [](double x) {return 1.0; };
		F2 = [](double x) {return sin(x * M_PI); };
	}
	else
	{
		F1 = F[0];
		F2 = F[1];
	}

}

void Solver::calculate(const unsigned int n, MODE mode)
{
    std::vector<double> alpha = calc_a(n, mode);
    std::vector<double> delta = calc_d(n, mode);
    std::vector<double> phi = calc_phi(n, mode);

	const unsigned long long size = delta.size();
	const double step = (b - a) / n;
	std::vector<double> A(size);
	std::vector<double> B(size);
	std::vector<double> C(size);

	for (unsigned long long i = 0; i < size; i++)
	{
        A[i] = alpha[i] / (step * step);
        B[i] = alpha[i + 1] / (step * step);
        C[i] = (alpha[i] + alpha[i + 1]) / (step * step) + delta[i];
	}
	num_solution = SolveTridiagonalMatrix(A, C, B, phi, { 0.0, 0.0 }, {mu1, mu2 });
    calc_second_solution(n, mode);
    calc_eps();
}

std::vector<double>& Solver::getNumSolution() {return num_solution;}

std::vector<double>& Solver::getSecondSolution() {return second_solution;}

std::vector<double> &Solver::getDifference() {return difference;}

std::vector<double> Solver::calc_a_test(const unsigned int n)
{
    std::vector<double> alpha;
    const double step = (b - a) / static_cast<double>(n);
    unsigned int brk = static_cast<int>(psi / step);
    double tmp1 = K1(psi), tmp2 = K2(psi);

    for (unsigned int i = 0; i < brk; ++i)
    {
        alpha.push_back(tmp1);
    }
    alpha.push_back(step / ((psi - brk * step) / tmp1 + (brk * step + step - psi) / tmp2));
    for (unsigned int i = brk+1; i < n; ++i)
    {
        alpha.push_back(tmp2);
    }

    return alpha;
}

std::vector<double> Solver::calc_d_test(const unsigned int n)
{
    std::vector<double> delta;
    const double step = (b - a) / static_cast<double>(n);
    unsigned int brk = static_cast<int>(psi / step - 0.5);
    double tmp1 = Q1(psi), tmp3 = Q2(psi);

    for (unsigned int i = 0; i < brk; ++i)
    {
        delta.push_back(tmp1);
    }
    delta.push_back(tmp1 * (psi / step - brk - 0.5) + tmp3 * (brk + 1.5 - psi / step));
    for (unsigned int i = brk + 1; i < n-1; ++i)
    {
        delta.push_back(tmp3);
    }

    return delta;
}

std::vector<double> Solver::calc_phi_test(const unsigned int n)
{
    std::vector<double> phi;
    const double step = (b - a) / static_cast<double>(n);
    unsigned int brk = static_cast<int>(psi / step - 0.5);
    double tmp2 = F1(psi), tmp4 = F2(psi);

    for (unsigned int i = 0; i < brk; ++i)
    {
        phi.push_back(tmp2);
    }
    phi.push_back(tmp2 * (psi / step - brk - 0.5) + tmp4 * (brk + 1.5 - psi / step));
    for (unsigned int i = brk + 1; i < n-1; ++i)
    {
        phi.push_back(tmp4);
    }

    return phi;
}

std::vector<double> Solver::calc_a_main(const unsigned int n)
{
    std::vector<double> alpha;
    const double step = (b - a) / n;
    double x = step;
    double x_half = step / 2;

    while (x <= psi)
    {
        alpha.push_back(K1(x_half));
        x += step;
        x_half += step;
    }
    alpha.push_back(step / ((psi - x + step) / K1((psi + x - step) / 2) + (x - psi) / K2((x + psi) / 2)));
    x += step;
    x_half += step;
    while (x < 1.0)
    {
        alpha.push_back(K2(x_half));
        x += step;
        x_half += step;
    }
    if (std::abs(x-1.0) < 1e-8)
    {
        alpha.push_back(K2(x_half));
    }

    return alpha;
}

std::vector<double> Solver::calc_d_main(const unsigned int n)
{
    std::vector<double> delta;
    const double step = (b - a) / static_cast<double>(n);
    double x_half = step * 3.0 / 2.0;
    double x = step;
    while (x_half <= psi)
    {
        delta.push_back(Q1(x));
        x += step;
        x_half += step;
    }
    delta.push_back((Q1((x_half - step + psi) / 2.0) * (psi - x_half + step) + Q2((x_half + psi) / 2.0) * (x_half - psi)) / step);
    x += step;
    x_half += step;
    while (x_half < 1.0)
    {
        delta.push_back(Q2(x));
        x += step;
        x_half += step;
    }

    return delta;
}

std::vector<double> Solver::calc_phi_main(const unsigned int n)
{
    std::vector<double> phi;
    const double step = (b - a) / static_cast<double>(n);
    double x_half = step * 3.0 / 2.0;
    double x = step;

    while (x_half <= psi)
    {
        phi.push_back(Q1(x));
        x += step;
        x_half += step;
    }
    phi.push_back((Q1((x_half - step + psi) / 2.0) * (psi - x_half + step) + Q2((x_half + psi) / 2.0) * (x_half - psi)) / step);
    x += step;
    x_half += step;
    while (x_half < 1.0)
    {
        phi.push_back(Q2(x));
        x += step;
        x_half += step;
    }

    return phi;
}

std::vector<double> Solver::calc_a(const unsigned int n, MODE mode)
{
    if (mode == TEST)
        return calc_a_test(n);
    else
        return calc_a_main(n);

}

std::vector<double> Solver::calc_d(const unsigned int n, MODE mode)
{
    if (mode == TEST)
        return calc_d_test(n);
    else
        return calc_d_main(n);
}

std::vector<double> Solver::calc_phi(const unsigned int n, MODE mode)
{
    if (mode == TEST)
        return calc_phi_test(n);
    else
        return calc_phi_main(n);
}

void Solver::calc_true_sol(const unsigned int n)
{
    const double C1 = -1.3730251475543289;
    const double C2 = -0.9603081857790043;
    const double C3 = -2.4598464013496;
    const double C4 = -6.2589035537192;
    const double C5 = 8.9890777152771;
    second_solution = std::vector<double>(n+1);
    unsigned long long i = 1;
    const double step = (b - a) / static_cast<double>(n);
    double x = step;

    second_solution[0] = 1.0;
    while (x <= psi)
    {
        second_solution[i] = C1 * exp(-sqrt(30.0/209.0) * x) + C2 * exp(sqrt(30.0/209.0) * x) + 10.0 / 3.0;
        x += step;
        i++;
    }
    for (; i < n; i++)
    {
        second_solution[i] = C4 * exp(-x) + C3 * exp(x) + C5;
        x += step;
    }
    second_solution[n] = 0.0;
}

void Solver::calc_doubled_num_sol(const unsigned int n)
{
    std::vector<double> alpha = calc_a(2*n, MAIN);
    std::vector<double> delta = calc_d(2*n, MAIN);
    std::vector<double> phi = calc_phi(2*n, MAIN);

    const unsigned long long size = delta.size();
    const double step = (b - a) / static_cast<double>(2*n);
    std::vector<double> A(size);
    std::vector<double> B(size);
    std::vector<double> C(size);

    for (unsigned long long i = 0; i < size; i++)
    {
        A[i] = alpha[i] / (step * step);
        B[i] = alpha[i + 1] / (step * step);
        C[i] = (alpha[i] + alpha[i + 1]) / (step * step) + delta[i];
    }

    std::vector<double> tmp_sol = SolveTridiagonalMatrix(A, C, B, phi, { 0.0, 0.0 }, { mu1, mu2 });
    second_solution = std::vector<double>(n+1);
    for (unsigned long long i = 0; i < n+1; i++)
    {
        second_solution[i] = tmp_sol[i*2];
    }

}

void Solver::calc_second_solution(const unsigned int n, MODE mode)
{
    if (mode == TEST)
        calc_true_sol(n);
    else
        calc_doubled_num_sol(n);
}

void Solver::calc_eps()
{
    const unsigned long long size = num_solution.size();
    difference = std::vector<double>(size);
    for (unsigned long long i = 0; i < size; ++i)
    {
        difference[i] = std::abs(num_solution[i] - second_solution[i]);
    }
}
