#pragma once

#include <vector>
#include <iostream>
#include <cmath>

class TestWork
{
public:
	std::vector<double> grid;
	std::vector<double> grid_step;
	std::vector<double> true_values;
	std::vector<double> num_values;
	std::vector<double> d_num_values;
	std::vector<double> final_num_values;
	std::vector<int> mult2;
	std::vector<int> div2;
	double right_border;
    double eps;
	bool ctrl_local_err;
	int max_steps;
	int mult;
	int div;

    TestWork(double right_border = 1.0, double initial_value = 1.0, double initial_step = 0.01, int max_steps = 1000, bool ctrl_local_err = true, double eps = 1e-8);
	double Func(double u);
	double TrueFunc(double x);
	double NumFunc(double v, double h);
	double DNumFunc(double v, double h);
	void MethodStep();
	void Run();
	void Print();
};

