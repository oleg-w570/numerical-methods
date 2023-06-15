#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

class MainWork2
{
public:
	std::vector<double> grid;
	std::vector<double> grid_step;
	std::vector<double> num_values_1;
	std::vector<double> d_num_values_1;
	std::vector<double> final_num_values_1;
	std::vector<double> num_values_2;
	std::vector<double> d_num_values_2;
	std::vector<double> final_num_values_2;
	std::vector<int> mult2;
	std::vector<int> div2;
	int mult;
	int div;
	double right_border;
	double eps;
	bool ctrl_local_err;
	int max_steps;
	double a;
	double b;

	MainWork2(double a = 1.0, double b = 1.0, double right_border = 1.0, double initial_value = 1.0,double initial_value_2 = 1.0, double initial_step = 0.01, int max_steps = 1000, bool ctrl_local_err = true, double eps = 1e-8);
	double Func1(double u2);
	double Func2(double u1, double u2);
	double NumFunc(double v1, double v2, double h);
	double NumFunc2(double v1, double v2, double h);
	double DNumFunc(double v1, double v2, double h);
	double DNumFunc2(double v1, double v2, double h);
	void MethodStep();
	void Run();
	void Print();
};

