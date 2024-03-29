
#include "pch.h"
#include <iostream>
#include <iostream>
#include "clocale"
using namespace std;


float *gauss(float **a, float *y, int n)
{
	float *x, max;
	int k, index;
	const float eps = 0.0000001;  
	x = new float[n];
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
			std::cout << index << " матрице A" << endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			float temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		float temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		
		for (int i = k; i < n; i++)
		{
			float temp = a[i][k];
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

void task3(int n, float *y1, float *x1, float*x, float **a1)
{
	x1 = gauss(a1, y1, n);

	float max = 0, maxx = x[0];
	for (int i = 0; i < n; i++)
	{
		if (x1[i] - x[i] > max)max = x1[i] - x[i];
		if (x[i] > maxx)maxx = x[i];
	}
	std::cout << "Относительная погрешность = " << fabs(max / maxx);



}

void task2(int n, float *y1, float *y2)
{
	float *fmax = new float[n]; for (int i = 0; i < n; i++)fmax[i] = 0;
	float Fmax = fabs(y1[0] - y2[0]);
	for (int i = 0; i < n; i++) {
		fmax[i] = fabs(y1[i] - y2[i]);
		if (fmax[i] > Fmax)Fmax = fmax[i];
	}
	for (int i = 0; i < n; i++) { std::cout << "F[" << i << "] " << fmax[i] << " "; }
	std::cout << " Fmax = " << Fmax << endl;
	std::cout << endl;

}

int main()
{
	setlocale(LC_ALL, "rus");
	int n;
	float **a, *y, *x;
	float **a1, *y1, *x1;
	float **a2, *y2, *x2;
	
	std::cout << "Введите n: ";
	std::cin >> n;
	a = new float*[n];
	y = new float[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new float[n];
		for (int j = 0; j < n; j++)
		{
			std::cout << "a[" << i << "][" << j << "]= ";
			std::cin >> a[i][j];
		}
	}

	a1 = new float*[n];
	y1 = new float[n]; for (int i = 0; i < n; i++)y1[i] = 0;
	for (int i = 0; i < n; i++)
	{
		a1[i] = new float[n];
		for (int j = 0; j < n; j++)
		{
			a1[i][j] = a[i][j];
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		std::cout << "y[" << i << "]= ";
		std::cin >> y[i];
	}
	y2 = new float[n];
	for (int i = 0; i < n; i++)y2[i] = y[i];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << a[i][j] << "*x" << j;
			if (j < n - 1)
				std::cout << " + ";
		}
		std::cout << " = " << y[i] << endl;
	}

	x = gauss(a, y, n);
	for (int i = 0; i < n; i++)
		std::cout << "x[" << i << "]=" << x[i] << endl;

	
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
			y1[i] += (a1[i][k] * x[k]);
	}
	x1 = new float[n];

	task2(n,y1, y2);
	task3(n,y1,x1,x,a1);
	
	
	return 0;
}
