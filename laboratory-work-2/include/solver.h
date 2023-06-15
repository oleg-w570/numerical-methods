#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "tridiagonal_matrix_algorithm.h"
#include <vector>
#include <iostream>


typedef double(*Funcs[2])(double);
typedef double(*Func)(double);


enum MODE
{
    TEST, MAIN
};

class Solver
{
    Func K1;
    Func K2;
    Func Q1;
    Func Q2;
    Func F1;
    Func F2;
    double a;
    double mu1;
    double b;
    double mu2;
    double psi;
    std::vector<double> num_solution;
    std::vector<double> second_solution; // для тестовой как истинное решение, для основной как решение с двойным шагом
    std::vector<double> difference;
public:
    Solver(Funcs K = nullptr, Funcs Q = nullptr, Funcs F = nullptr, const double psi = 0.3, const double a = 0.0, const double b = 1.0,
        const double initial_temp = 1.0, const double final_temp = 0.0);

    void calculate(const unsigned int n, MODE mode);

    std::vector<double>& getNumSolution();

    std::vector<double>& getSecondSolution();

    std::vector<double>& getDifference();

protected:
    std::vector<double> calc_a_test(const unsigned int n);

    std::vector<double> calc_d_test(const unsigned int n);

    std::vector<double> calc_phi_test(const unsigned int n);

    std::vector<double> calc_a_main(const unsigned int n);

    std::vector<double> calc_d_main(const unsigned int n);

    std::vector<double> calc_phi_main(const unsigned int n);

    std::vector<double> calc_a(const unsigned int n, MODE mode);

    std::vector<double> calc_d(const unsigned int n, MODE mode);

    std::vector<double> calc_phi(const unsigned int n, MODE mode);

    void calc_true_sol(const unsigned int n);

    void calc_doubled_num_sol(const unsigned int n);

    void calc_second_solution(const unsigned int n, MODE mode);

    void calc_eps();
};
