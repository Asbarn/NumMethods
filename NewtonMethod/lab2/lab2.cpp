
#include "pch.h"
#include <iostream>
#include "cmath"
double f1(double x1, double x2)
{
	return cos(0.4*x2 + x1 * x1) + x2 * x2 + x1 * x1 - 1.6;

}

double f2(double x1, double x2)
{
	return (1.5*x1*x1 - x2 * x2) / (0.36 - 1);

}

double df1dx1(double x1, double x2)
{
	return -sin(0.4*x2 + x1 * x1) * 2 * x1 + 2 * x1;

}

double df2dx1(double x1, double x2)
{
	return (3 * x1) / (0.36 - 1);

}

double df1dx2(double x1, double x2)
{
	return -sin(0.4*x2 + x1 * x1) * 0.4 + 2 * x2;

}

double df2dx2(double x1, double x2)
{
	return (-2 * x2) / (0.36 - 1);

}

double jakob1(double x1, double x2)
{
	return df1dx1(x1, x2)*df2dx2(x1, x2) - df1dx2(x1, x2) * df2dx1(x1, x2);

}

double *gauss(double **a, double *y, int n)
{
	double *x, max;
	int k, index;
	const double eps = 0.0000001;
	x = new double[n];
	k = 0;
	while (k < n)
	{

		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}

		if (max < eps)
		{

			std::cout << "Нулевой столбец в ";
			std::cout << index << " матрице A" << std::endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;

		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}

	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}

int main()
{
	double eps1 = pow(0.1, 9), eps2 = pow(0.1, 9), M = 0.1,x1=1,x2=1, x11 = 1, x12 = 1, x21 = -1, x22 = 1;
//	int INT = 1; std::cout << "Enter INT:"; std::cin >> INT;
	double d1 = 1, d2 = 1;
	int choose = 0; std::cout << "Choose 1 or 2 (1-analiticheski,2 - chislenno)"; std::cin >> choose;
	if (choose == 1) {
		for (int i = 1; d1 > eps1 || d2 > eps2; i++)
		{
			std::cout << "Numb of iter: " << i << std::endl;
			double vecnev[2]; vecnev[0] = f1(x1, x2); vecnev[1] = f2(x1, x2);
			double **a; a = new double *[2];
			for (int j = 0; j < 2; j++)	a[j] = new double[2];
			a[0][0] = df1dx1(x1, x2);
			a[0][1] = df1dx2(x1, x2);
			a[1][0] = df2dx1(x1, x2);
			a[1][1] = df2dx2(x1, x2);
			double *dx, *y; y = new double[2];
			for (int j = 0; j < 2; j++)
			{
				y[j] = -vecnev[j];
			}
			dx = gauss(a, y, 2);
			x1 += dx[0]; x2 += dx[1];
			double max = fabs(f1(x1, x2));
			if (fabs(f2(x1, x2)) > max)max = fabs(f2(x1, x2));
			d1 = max;
			if (fabs(x1) < 1)max = dx[0];
			else max = dx[0] / x1;

			double max2 = 0;
			if (fabs(x1) < 1)max2 = dx[0];
			else max2 = dx[0] / x1;
			if (max > max2)d2 = max;
			else d2 = max2;
			std::cout << "d1 = " << d1 << "  d2 = " << d2 << std::endl;
			std::cout << "x1 =  " << x1 << "  x2 = " << x2 << std::endl;
			std::cout << (f1(x1, x2)) << "   " << f2(x1, x2) << std::endl;
			std::cout << std::endl;

		}
	}
	else if (choose == 2)
	{
		for (int i = 1; d1 > eps1 || d2 > eps2; i++)
		{
			std::cout << "Numb of iter: " << i << std::endl;
			double vecnev[2]; vecnev[0] = f1(x1, x2); vecnev[1] = f2(x1, x2);
			double **a; a = new double *[2];
			for (int j = 0; j < 2; j++)	a[j] = new double[2];
			a[0][0] = (f1(x1*(1+M), x2)-f1(x1,x2)) / (M*x1);
			a[0][1] = (f1(x1, x2*(1 + M)) - f1(x1, x2)) / (M*x2);
			a[1][0] = (f2(x1*(1 + M), x2) - f2(x1, x2))/(M*x1);
			a[1][1] = (f2(x1, x2*(1 + M)) - f2(x1, x2))/(M*x2);
			double *dx, *y; y = new double[2];
			for (int j = 0; j < 2; j++)
			{
				y[j] = -vecnev[j];
			}
			dx = gauss(a, y, 2);
			x1 += dx[0]; x2 += dx[1];
			double max = fabs(f1(x1, x2));
			if (fabs(f2(x1, x2)) > max)max = fabs(f2(x1, x2));
			d1 = max;
			if (fabs(x1) < 1)max = dx[0];
			else max = dx[0] / x1;

			double max2 = 0;
			if (fabs(x1) < 1)max2 = dx[0];
			else max2 = dx[0] / x1;
			if (max > max2)d2 = max;
			else d2 = max2;
			std::cout << "d1 = " << d1 << "  d2 = " << d2 << std::endl;
			std::cout << "x1 =  " << x1 << "  x2 = " << x2 << std::endl;
			std::cout << (f1(x1, x2)) << "   " << f2(x1, x2) << std::endl;
			std::cout << std::endl;

		}

	}
	else std::cout << "Wrong answer." << std::endl;
	//std::cout << "x1 =  " << x1 << "  x2 = " << x2 << std::endl;
	//std::cout << (f1(x1, x2)) << "   " << f2(x1, x2) << std::endl;




	return 0;
}

