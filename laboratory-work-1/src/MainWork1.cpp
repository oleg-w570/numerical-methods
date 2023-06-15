#include "MainWork1.h"

MainWork1::MainWork1(double right_border, double initial_value, double initial_step, int max_steps, bool ctrl_local_err, double eps)
{
	mult = 0;
	div = 0;
	this->ctrl_local_err = ctrl_local_err;
	this->eps = eps;
	this->max_steps = max_steps;
	this->right_border = right_border;
	mult2.push_back(mult);
	div2.push_back(div);
	grid.push_back(0);
	grid_step.push_back(initial_step);
	num_values.push_back(initial_value);
	d_num_values.push_back(initial_value);
	final_num_values.push_back(initial_value);
}

double MainWork1::Func(double x, double u)
{
    return (1/(pow((1+pow(x,2)),(1/3))))*pow(u,2)+u-pow(u,3)*sin(10*x);
}


double MainWork1::NumFunc(double x, double v, double h)
{
    const double k1 = Func(x, v);
    const double k2 = Func(x + h / 2, v + h / 2 * k1);
    const double k3 = Func(x + h / 2, v + h / 2 * k2);
    const double k4 = Func(x + h, v + h * k3);
	return (v + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
}

double MainWork1::DNumFunc(double x, double v, double h)
{
	const double v_tmp = NumFunc(x, v, h / 2);
    return NumFunc(x + h/2, v_tmp, h / 2);
}

void MainWork1::MethodStep()
{
	double h = grid_step.back();
    const double v = NumFunc(grid.back(), final_num_values.back(), h);
    const double v2 = DNumFunc(grid.back(), final_num_values.back(), h);
	const double s = abs(v2 - v) / 15;

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
		num_values.push_back(v);
		d_num_values.push_back(v2);
        final_num_values.push_back(v + 16 * s);

	}
}

void MainWork1::Run()
{
	int n = 0;
    while (grid.back() + grid_step.back() < right_border && n < max_steps)
	{
		MethodStep();
		n++;
	}

    if (right_border - grid.back() > 1e-8 && grid.back() + grid_step.back() > right_border)
    {
        grid_step.back() = right_border - grid.back();
        MethodStep();
    }
    std::cout << grid.back() << ", " << grid_step.back() << ", " << right_border << ", " << n << ", " << max_steps << std::endl;
}

void MainWork1::Print()
{
	unsigned long long N = grid.size();
	for (unsigned int i = 0; i < N; i++)
	{
		std::cout << "Num: (" << grid[i] << ", " << num_values[i] << ")"
			<< "\th = " << grid_step[i] << "\tv = " << num_values[i] << "\tv2 = " << d_num_values[i]
			<< "\nmult2 = " << mult2[i] << ", div = " << div2[i]
			<< std::endl;
	}
}
