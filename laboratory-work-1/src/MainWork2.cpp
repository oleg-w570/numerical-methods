#include "MainWork2.h"

MainWork2::MainWork2(double a, double b, double right_border, double initial_value, double initial_value_2, double initial_step, int max_steps, bool ctrl_local_err, double eps)
{
	this->a = a;
	this->b = b;
	this->ctrl_local_err = ctrl_local_err;
	this->eps = eps;
	this->max_steps = max_steps;
	this->right_border = right_border;
	mult = 0;
	div = 0;
	mult2.push_back(0);
	div2.push_back(0);
	grid.push_back(0);
	grid_step.push_back(initial_step);
	num_values_1.push_back(initial_value);
	d_num_values_1.push_back(initial_value);
	final_num_values_1.push_back(initial_value);
	num_values_2.push_back(initial_value_2);
	d_num_values_2.push_back(initial_value_2);
	final_num_values_2.push_back(initial_value_2);
}

double MainWork2::Func1(double u2)
{
	return u2;
}

double MainWork2::Func2(double u1, double u2)
{
    return -a * u2 * u2 - b * u1;
    //return -0.15 * u2 - 2 * u1;
}


double MainWork2::NumFunc(double v1, double v2, double h)
{
	const double k1 = Func1(v2);
	const double k2 = Func1(v2 + h / 2 * k1);
	const double k3 = Func1(v2 + h / 2 * k2);
	const double k4 = Func1(v2 + h * k3);

	return (v1 + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
}

double MainWork2::NumFunc2(double v1, double v2, double h)
{
	const double k1 = Func2(v1, v2);
	const double k2 = Func2(v1 + h / 2 * k1, v2 + h / 2 * k1);
	const double k3 = Func2(v1 + h / 2 * k2, v2 + h / 2 * k2);
	const double k4 = Func2(v1 + h * k3, v2 + h * k3);

	return (v2 + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
}

double MainWork2::DNumFunc(double v1, double v2, double h)
{
	const double v1_tmp = NumFunc(v1, v2, h / 2);
	const double v2_tmp = NumFunc2(v1, v2, h / 2);
	return NumFunc(v1_tmp,v2_tmp, h / 2);
}

double MainWork2::DNumFunc2(double v1, double v2, double h)
{
	const double v1_tmp = NumFunc(v1, v2, h / 2);
	const double v2_tmp = NumFunc2(v1, v2, h / 2);
	return NumFunc2(v1_tmp, v2_tmp, h / 2);
}


void MainWork2::MethodStep()
{
	double h = grid_step.back();
	const double v1 = NumFunc(final_num_values_1.back(), final_num_values_2.back(), h);
	const double vD1 = DNumFunc(final_num_values_1.back(), final_num_values_2.back(), h);

	const double v2 = NumFunc2(final_num_values_1.back(), final_num_values_2.back(), h);
	const double vD2 = DNumFunc2(final_num_values_1.back(), final_num_values_2.back(), h);

	double s1 = abs(vD1 - v1) / 15;
	double s2 = abs(vD2 - v2) / 15;
	double s = std::max(s1, s2);

	if (s > eps && ctrl_local_err)
	{
		grid_step.back() /= 2;
		div++;
	}
	else
	{
		const double x = grid.back() + h;
		if (s < eps / 32 && ctrl_local_err)
		{
			h *= 2;
			mult++;
		}

		mult2.push_back(mult);
		div2.push_back(div);
		grid_step.push_back(h);
		grid.push_back(x);
		num_values_1.push_back(v1);
		d_num_values_1.push_back(vD1);
		final_num_values_1.push_back(v1 + 16 * s1);
		num_values_2.push_back(v2);
		d_num_values_2.push_back(vD2);
		final_num_values_2.push_back(v2 + 16 * s2);
	}
}

void MainWork2::Run()
{
	int n = 0;
	while (grid.back() + grid_step.back() < right_border && n < max_steps)
	{
		MethodStep();
		n++;
	}

    if (right_border - grid.back() > 1e-8 && grid.back() + grid_step.back() > right_border )
    {
        grid_step.back() = right_border - grid.back();
        MethodStep();
    }
}

void MainWork2::Print()
{
	unsigned long long N = grid.size();
	for (unsigned int i = 0; i < N; i++)
	{
		std::cout << "Num: (" << grid[i] << ", " << num_values_1[i] << ")"
			<< "\th = " << grid_step[i] << "\tv = " << num_values_1[i] << "\tv2 = " << d_num_values_1[i] << "\tv_2 = " << num_values_2[i] << "\tv2_2 = " << d_num_values_2[i]
			<< "\nmult2 = " << mult2[i] << ", div2 = " << div2[i]
			<< std::endl;
	}
}
