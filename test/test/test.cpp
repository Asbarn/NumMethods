// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "cmath"
#include "fstream"
#include <iostream>
#include <iomanip>
#include "math.h"
using namespace std;


double getStep(double* Eps, double eps_dop, double t_step, int n)
{
	
	double* min_vect = new double[n];
	for (int i = 0; i < n; ++i)
		min_vect[i] = 0;
	double min = t_step * sqrt(eps_dop / fabs(Eps[0]));
	for (int i = 1; i < n; ++i)
	{
		min_vect[i] = t_step * sqrt(eps_dop / fabs(Eps[i]));
		if (min_vect[i] < min) min = min_vect[i];
	}
	return min;

}
double* newton(double** A, double* B, double* Y_now, double t_step);

double fabs(double x)
{
	if (x >= 0)return x;
	else return -x;
}
void YavEyler();
void NeyavEyler();
double* gauss(double** a, double* y, int n)
{
	double* x, max;
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

			std::cout << "Nulevoy stolbec v ";
			std::cout << index << " matrice A" << std::endl;
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

double du1dt(double u1, double u2, double t)
{
	if (t == 0)return-u1 * u2;
	else return -u1 * u2 + (sin(t)) / t;
}

double du2dt(double u1, double u2, double t, double a)
{
	return -u2 * u2 + a * t / (1 + t * t);


}


double f(double yn, double tn, double A, double b)
{
	return (A * yn - b);
}
double f1(double y1, double y2, double y3, double* Y_now, double** A, double* B, double t_step)
{
	return y1 - Y_now[0] - t_step * (A[0][0] * y1 + A[0][1] * y2 + A[0][2] * y3 - B[0]);
}
double f2(double y1, double y2, double y3, double* Y_now, double** A, double* B, double t_step)
{
	return y2 - Y_now[1] - t_step * (A[1][0] * y1 + A[1][1] * y2 + A[1][2] * y3 - B[1]);
}
double f3(double y1, double y2, double y3, double* Y_now, double** A, double * B, double t_step)
{
	return y3 - Y_now[2] - t_step * (A[2][0] * y1 + A[2][1] * y2 + A[2][2] * y3 - B[2]);
}

double dfdy(double yn, double tn, double A)
{
	return A;

}


int main()
{
	cout << "Yav Eyler:" << endl;
	YavEyler();



	cout << endl << "Neyav Eyler:" << endl;
	NeyavEyler();


}

void NeyavEyler()
{
	double eps = 1e-4;
	double eps_dop = 1e-4;
	

	double* Eps_vect = new double[3];
	for (int i = 0; i < 3; ++i)
		Eps_vect[i] = 0;

	double lam1, lam2, lam3;
	lam1 = -10;
	lam2 = -20;
	lam3 = -30;
	
	double** A = new double*[3];
	for (int i = 0; i < 3; ++i)
		A[i] = new double[3];
	A[0][0] = (2 * lam1 + 4 * lam2) / 6;
	A[0][1] = A[0][2] = A[1][0] = A[2][0] = (lam1 - lam2) / 3;
	A[1][1] = A[2][2] = (2 * lam1 + lam2 + 3 * lam3) / 6;
	A[2][1] = A[1][2] = (2 * lam1 + lam2 - 3 * lam3) / 6;
	
	double* B = new double[3];
	B[0] = -(2 * lam1 + lam2) / 3;
	B[1] = -(4 * lam1 - lam2 - 9 * lam3) / 6;
	B[2] = -(4 * lam1 - lam2 + 9 * lam3) / 6;

	
	double* Y_pred = new double[3];
	for (int i = 0; i < 3; ++i)
		Y_pred[i] = 0;

	double* Y_sled = NULL; 

	
	double* Y = new double[3];
	for (int i = 0; i < 3; ++i)
		Y[i] = 0;

	Y[0] = Y_pred[0] = 10;
	Y[1] = Y_pred[1] = 22;
	Y[2] = Y_pred[2] = 9;
	double t_step_min = 0.00001;
	double t_step_max = 0.001;
	double t = 0, t_pred = 0, t_step_pred = t_step_min, t_step = t_step_min;
	double T = 1;

	ofstream fout1;
	fout1.open("file1.txt", ios::out);
	ofstream fout2;
	fout2.open("file2.txt", ios::out);
	ofstream fout3;
	fout3.open("file3.txt", ios::out);
	ofstream foutt;
	foutt.open("fileе.txt", ios::out);


	//setprecision(20);

	int choice = 0;
	cout << "Kvazi(1)/three zones(2)" << endl;
	cin >> choice;
	
	cout.setf(ios::left);
	cout << setw(15) << "Y1" << setw(15) << "Y2" << setw(15) << "Y3" << setw(15) << "t" << endl;

	do {
		if (choice == 1)
		{
			t_pred = t;
			do {
				t += t_step;
				Y_sled = newton(A, B, Y, t_step);
				
				for (int i = 0; i < 3; ++i)
					Eps_vect[i] = -t_step / (t_step + t_step_pred) * (Y_sled[i] - Y[i] - t_step / t_step_pred * (Y[i] - Y_pred[i]));
				
				for (int i = 0; i < 3; ++i)
				{
					if (fabs(Eps_vect[i]) > eps_dop)
					{
						t_step /= 2;
						Y_sled = NULL;
						t = t_pred;
						break;
					}
				}
			} while (t == t_pred);
			t_step_pred = t_step;
			t_step = getStep(Eps_vect, eps_dop, t_step, 3);
		}
		else if(choice==2)
		{
			t += t_step;
			Y_sled = newton(A, B, Y, t_step);
			for (int i = 0; i < 3; ++i)
				Eps_vect[i] = -t_step / (t_step + t_step_pred) * (Y_sled[i] - Y[i] - t_step / t_step_pred * (Y[i] - Y_pred[i]));
			for (int i = 0; i < 3; ++i)		Eps_vect[i] = -t_step / (t_step + t_step_pred) * (Y_sled[i] - Y[i] - t_step / t_step_pred * (Y[i] - Y_pred[i]));
			t_step_pred = t_step; 
			t_step = getStep(Eps_vect, eps_dop, t_step, 3);

		}
		else { 
			cout << "incorrect choice ";
		break;
		}
		if (t_step > t_step_max)t_step = t_step_max;
		cout << setw(20) << Y_sled[0] << setw(20) << Y_sled[1] << setw(20) << Y_sled[2] << setw(20) << t << endl;
		fout1 << Y_sled[0] << ";";
		fout2 << Y_sled[1] << ";";
		fout3 << Y_sled[2] << ";";
		foutt << t << ";";
		Y_pred = Y; Y = Y_sled;
	} while (t < T);

	fout1.close();
	cin.get();
	fout2.close();
	cin.get();
	fout3.close();
	cin.get();
	foutt.close();
	cin.get();
}





void YavEyler()
{
	double u10, u20, Tpred = 1, T, edop1 = pow(10, -2), edop2 = pow(10, -2), Tmax, w = 25, a = 2.5 + w / 40;
	cout << "u10="; u10 = 0;
	cout << "u20="; u20 = -0.412;
	cout << "T"; Tpred = 1;
	cout << "edop"; 
	cout << "Tmax"; Tmax = pow(10, -3);
	cout << endl;
	ofstream fout1y;
	fout1y.open("file1y.txt", ios::out);
	ofstream fout2y;
	fout2y.open("file2y.txt", ios::out);
	
	ofstream foutty;
	foutty.open("fileеy.txt", ios::out);
	double t = 0, y1 = u10, y2 = u20; int k = 1;
	while (t < Tpred)
	{
		
		double T1 = edop1 / fabs(fabs(du1dt(y1, y2, t)) + edop1 / Tmax);
		double T2 = edop2 / fabs(fabs(du2dt(y1, y2, t, a)) + edop2 / Tmax);
		if (T1 < T2)T = T1;
		else T = T2;
		double y1n = y1 + T * du1dt(y1, y2, t), y2n = y2 + T * du2dt(y1, y2, t, a);
		y1 = y1n;
		y2 = y2n;
		t = t + T;
		cout << "Shag №" << k << endl; k++;
		cout << "u1= " << y1 << endl;
		cout << "u2= " << y2 << endl;
		cout << "t= " << t << endl;
		cout << endl;
		fout1y <<y1 << ";";
		fout2y << y2 << ";";
		foutty <<t << ";";
		
	}
	fout1y.close();
	cin.get();
	fout2y.close();
	cin.get();
	
	foutty.close();
	cin.get();

}












double* newton(double** A, double* B, double* Y_now, double t_step)
{
	double eps1 = 10e-9, eps2 = 10e-9;
	int n = 3;
	int NIT = 10; 
	double* X = new double[n];
	for (int i = 0; i < n; ++i)
		X[i] = 0;

	

	double* F = new double[n];
	for (int i = 0; i < n; ++i)
		F[i] = 0;
	

	double** J = new double*[n];
	for (int i = 0; i < n; ++i)
		J[i] = new double[n];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			J[i][j] = 0;

	double* VectDelta = new double[n];
	for (int i = 0; i < n; ++i)
		VectDelta[i] = 0;

	
	double* X2 = new double[n];
	for (int i = 0; i < n; ++i)
		X2[i] = 0;

	double miniDelta1;
	double miniDelta2;

	double M = 0.01; 

	
	double* p = NULL;
	p = NULL;
	X[0] = Y_now[0];
	X[1] = Y_now[1];
	X[2] = Y_now[2];
	
	double delX = X[0] * M;
	J[0][0] = (f1(X[0] + delX, X[1], X[2], Y_now, A, B, t_step) - f1(X[0], X[1], X[2], Y_now, A, B, t_step)) / delX;
	J[1][0] = (f2(X[0] + delX, X[1], X[2], Y_now, A, B, t_step) - f2(X[0], X[1], X[2], Y_now, A, B, t_step)) / delX;
	J[2][0] = (f3(X[0] + delX, X[1], X[2], Y_now, A, B, t_step) - f3(X[0], X[1], X[2], Y_now, A, B, t_step)) / delX;
	delX = X[1] * M;
	J[0][1] = (f1(X[0], X[1] + delX, X[2], Y_now, A, B, t_step) - f1(X[0], X[1], X[2], Y_now, A, B, t_step)) / delX;
	J[1][1] = (f2(X[0], X[1] + delX, X[2], Y_now, A, B, t_step) - f2(X[0], X[1], X[2], Y_now, A, B, t_step)) / delX;
	J[2][1] = (f3(X[0], X[1] + delX, X[2], Y_now, A, B, t_step) - f3(X[0], X[1], X[2], Y_now, A, B, t_step)) / delX;
	delX = X[2] * M;
	J[0][2] = (f1(X[0], X[1], X[2] + delX, Y_now, A, B, t_step) - f1(X[0], X[1], X[2], Y_now, A, B, t_step)) / delX;
	J[1][2] = (f2(X[0], X[1], X[2] + delX, Y_now, A, B, t_step) - f2(X[0], X[1], X[2], Y_now, A, B, t_step)) / delX;
	J[2][2] = (f3(X[0], X[1], X[2] + delX, Y_now, A, B, t_step) - f3(X[0], X[1], X[2], Y_now, A, B, t_step)) / delX;
	int k_itter = 0;
	do
	{
		
		F[0] = -f1(X[0], X[1], X[2], Y_now, A, B, t_step);
		F[1] = -f2(X[0], X[1], X[2], Y_now, A, B, t_step);
		F[2] = -f3(X[0], X[1], X[2], Y_now, A, B, t_step);
		VectDelta = gauss(J, F, n);
		if (VectDelta == NULL)
		{
			cout << "error" << endl;
			return NULL;
		}
		
		X2[0] = X[0] + VectDelta[0];
		X2[1] = X[1] + VectDelta[1];
		X2[2] = X[2] + VectDelta[2];
		double eps = 1e-9;
		double max = 0;

		miniDelta1 = fabs(f1(X[0], X[1], X[2], Y_now, A, B, t_step));
		max = fabs(f2(X[0], X[1], X[2], Y_now, A, B, t_step));
		if (max > miniDelta1) miniDelta1 = max;
		else
		{
			max = fabs(f3(X[0], X[1], X[2], Y_now, A, B, t_step));
			if (max > miniDelta1) miniDelta1 = max;
		}
		
		if (fabs(X2[0] - 1) >= eps)
			miniDelta2 = fabs((X2[0] - X[0]) / X2[0]);
		else miniDelta2 = fabs(X2[0] - X[0]);

		for (int i = 1; i < n; ++i)
		{
			if (fabs(X2[i] - 1) >= eps)
				max = fabs((X2[i] - X[i]) / X2[i]);
			else max = fabs(X2[i] - X[i]);
			if (miniDelta2 < max) miniDelta2 = max;
		}
		
		p = X;
		X = X2;
		X2 = p;
		k_itter += 1;
		if (k_itter > NIT) {
			cout << "MaxIter" << endl;
			break;
		}
	} while (fabs(miniDelta1) >= eps1 && fabs(miniDelta2) >= eps2);

	return X;
}
