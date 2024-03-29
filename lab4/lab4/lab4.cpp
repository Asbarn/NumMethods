// lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <iomanip>
using namespace std;

const int N = 7;
const int m = 1;

void swp(double B[][m + 2], int a, int b)
{
	double x;
	for (int j = 0; j < m; j++)
	{
		x = B[a][j];
		B[a][j] = B[b][j];
		B[b][j] = x;
	}
}
void triangle(double B[][m + 2])
{
	for (int z = 0; z < m + 1; z++)
	{
		double y;
		int sgn;
		int x = INT_MIN;
		float max = LONG_MIN;
		for (int i = z; i < m + 1; i++)
		{
			if (abs(B[i][z]) > max)
			{
				max = abs(B[i][z]);
				if (B[i][z] > 0)
				{
					sgn = 1;
				}
				else
				{
					sgn = -1;
				}
				x = i;
			}
		}
		swp(B, z, x);
		for (int j = 0; j < m + 2; j++)
		{
			if (max != 0)
			{
				B[z][j] = (B[z][j] / max) * sgn;
			}
		}
		for (int i = z + 1; i < m + 1; i++)
		{
			y = B[i][z] / B[z][z];
			for (int j = 0; j < m; j++)
			{
				B[i][j] = B[i][j] - B[z][j] * y;
				if (j == 0 || abs(B[i][j]) < 1e-10)
				{
					B[i][j] = 0;
				}
			}
		}
	}
}
void Gauss(double B[][m + 2], double C[m + 1])
{
	triangle(B);
	for (int i = 0; i < m + 1; i++)
	{
		C[i] = B[i][m + 1];
	}
	int i = m;
	int j;
	while (i >= 0)
	{
		j = m;
		while (i != j)
		{
			C[i] -= B[i][j] * C[j];
			j--;
		}
		i--;
	}
}

int main()
{
	int X[N];
	double Y[N];
	int t1;
	for (int j = 0; j < N; j++)
	{
		cin >> t1;
		X[j] = t1;
	}
	double t2;
	for (int j = 0; j < N; j++)
	{
		cin >> t2;
		Y[j] = log(t2);
	}
	double POWERX[2 * m];
	for (int j = 0; j < 2 * m; j++)
	{
		POWERX[j] = -1;
	}
	int RES = 0;
	int x1 = 0;
	for (int k = 1; k < 2 * m + 1; k++)
	{
		for (int j1 = 0; j1 < N; j1++)
		{
			RES += pow(X[j1], k);
		}
		for (int i2 = 0; POWERX[i2] != -1; i2++)
		{
			x1 = i2 + 1;
		}
		POWERX[x1] = RES;
		RES = 0;
	}
	int SUMX[m + 1][m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			SUMX[i][j] = POWERX[i + j - 1];
		}
	}
	SUMX[0][0] = N;
	double PRAW[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		PRAW[i] = 0;
	}
	for (int i = 0; i < m + 1; i++)
	{
		for (int i1 = 0; i1 < N; i1++)
		{
			PRAW[i] += Y[i1] * pow(X[i1], i);
		}
	}
	double B[m + 1][m + 2];
	for (int i = 0; i < m + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			B[i][j] = SUMX[i][j];
		}
	}
	for (int i = 0; i < m + 1; i++)
	{
		B[i][m + 1] = PRAW[i];
	}
	double A[m + 1];
	Gauss(B, A);
	double S2 = 0;
	double S1 = 0;
	double al;
	double bt;
	al = exp(A[0]);
	bt = -A[1];
	cout << "alpha = :" << " " << al;
	cout << endl;
	cout << "beta = :" << " " << bt;
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		cout << i << ")" << " " << X[i] << "  " << exp(Y[i]) << "  " << al * exp(-bt * X[i]);
		cout << endl;
	}
	for (int i = 0; i < N; i++)
	{
		S2 = exp(Y[i]) - al * exp(-bt * X[i]);
	}
	S2 = S2 / (N - m - 1);
	double o;
	o = sqrt(S2);
	cout << o << endl;
	system("pause");
}