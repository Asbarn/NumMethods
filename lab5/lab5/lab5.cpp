#include <pch.h>
#include <iostream>
#include "clocale"
#include "cmath"

using namespace std;


void trapec(double a, double b, double F(double x))
{
	double h,eps=0.000001,f=0,f2=0,x=a;
	int n = 2;
	h = (b - a) / n;
	f = h * (F(a) + F((b - a) / 2) + F(b)) / 2;

	n++;

	
	for (h = (b - a) / n; ;n++,h=(b-a)/n)
	{
		//if (abs(f2 - f) < 3 * eps) break;
		if (n > 3) {
			f = f2; f2 = 0;
		}


		x = a; f2 += F(x); x += h;
		while (x < b) {
		
			f2 = f2 + 2*F(x);
			x += h;
		}
		f2 += F(b);
		f2 = h * f2 / 2;
		if (abs(f2 - f) < 3 * eps)break;
		
	}
	
	double result = f2;
	cout << "Integral = " << result << endl;
	double R = (f2 - f) / (pow(0.5, 2) - 1);
	cout << "Pogreshnost = " << R<<endl;
	
}

void simpson(float a, float b, float F(float x))
{
	double h, eps = 0.000001, f = 0, f2 = 0, x = a;
	int n = 2;
	h = (b - a) / n;
	f = h * (F(a) + F((b - a) / 2) + F(b)) / 2;
	n+=2;

	for (h = (b - a) / n; ; n+=2, h = (b - a) / n)
	{
		if (n > 4) {
			f = f2; f2 = 0;
		}


		x = a; f2 += F(x); x += h;
		for (int i = 1; x < b;) {

			
			f2 = f2 + 4 * F(x);
			x += h;
		}
		f2 += F(b);
		f2 = h * f2 / 2;
		if (abs(f2 - f) < 15 * eps)break;

	}

	double result = f2;
	cout << "Integral = " << result << endl;
	double R = (f2 - f) / (pow(0.5, 2) - 1);
	cout << "Pogreshnost = " << R << endl;


}


double F(double x) {return (pow((1 + x * x * x), (1 / 2)));}
double Fseven(double x) { return pow(1+2*x*x*x,1/2); }
double Fexp(double x) { return x*x; }
int main()
{
    std::cout << "Hello World!\n";
	double a, b;
	cout << "a="; cin >> a; cout << endl;
	cout << "b="; cin >> b; cout << endl;
	trapec(a,b,Fexp);
}

