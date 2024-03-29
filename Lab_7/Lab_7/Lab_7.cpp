// Lab_7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h> 
#include <cmath> 
#include <fstream> 
#define  PRES double 
#define  NXB   15 
#define  NYB   12 
#define  NX   NXB*3+1
#define  NY   NYB*3+1
#define  NYK2  NYB*2
#define  REP   3000 
#define  DEL   100 
#define  AMAT  1.1f 
#define  TEM1  5.0f 
#define  TEM2  15.0f 
#define  HX    0.2f 
#define  HY    0.3f 

using namespace std; 

template <class T> const T& min(const T& a, const T& b) {
	return !(b < a) ? a : b;     
}
int main(int argc, char **argv)
{
	int    i, j, k;
	int    idt = 0; 
	int    ndt = 0; 
	PRES  T1 = TEM1,T2 = TEM2, h = HX, r = HY, a = AMAT, t0; 
	PRES  T[NY][NX], TT[NY][NX]; 
	PRES  rr = min(h, r);
	PRES  tau = 0.25f*rr*rr / a;
	PRES  alf_1 = -h / r;
	PRES  alf_2 = -r / h; 
	PRES  alf_3 = 0.5f * alf_2;
	PRES  alf_4 = 0.5f * alf_1;
	PRES  bet_1 = a * tau / (h*r);
	PRES  bet_2 = 2.0f*bet_1;
	PRES  bet_3 = 4.0f*bet_1; 
	PRES  bet_4 = 4.0f*bet_1/3.0f;
	cout << bet_4;
	PRES  gam_1 = -2.f*(alf_1 + alf_2);
	PRES  gam_2 = -1.5*(alf_1 + alf_2);
	PRES  gam_3 = -(alf_1 + alf_2); 
	PRES  gam_4 = -(alf_3 + alf_4);
	char  filename[128];
	int i1 = NXB, i2 = 2 * NXB, i3 = 3 * NXB;
	int j1 = NYB, j2 = 2 * NYB, j3 = 3 * NYB;
	for (j = 0; j < NY; j++)
	{ for (i = 0; i < NX; i++)
	{ T[j][i] = 0.0f; TT[j][i] = 0.0f;
	} }
	
	for (j = j1; j <= j3; j++)
	{ T[j][0] = T1; TT[j][0] = T1;
	}
	for (i = 0; i <= i1; i++) 
	{ T[j3][i] = T1; TT[j3][i] = T1;
	}

	for (j = 0; j <= j1; j++) 
	{T[j][i3] = T2; TT[j][i3] = T2;
	}
	for (i = i2; i <= i3; i++) 
	{ T[0][i] = T2; TT[0][i] = T2;
	}

	ofstream fout("C:/Users/asbarn/Desktop/учеба2/Числаки/Lab_7/Lab_7/T1.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	for (j = 0; j < NY; j++)
	{ for (i = 0; i < NX; i++)
	{ PRES w = T[j][i];
	fout.write((char*)&w, sizeof w); } }
	fout.close(); 
	for (k = 0; k < REP; k++) {
		for (j = 0; j < NY; j++) {
			for (i = 0; i < NX; i++) {
				t0 = T[j][i]; 
				if (i == 0 && j < j1 && j > 0)
				{ 
					TT[j][i] = t0 - bet_2 * (alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i + 1] + gam_3 * t0);
				}
				else if (i == 0 && j == 0)
				{ TT[j][i] = t0 - bet_3 * (alf_3* T[j][i + 1] + alf_4 * T[j + 1][i] + gam_4 * t0); }
				else if (i > 0 && i < i2 && j == 0)
				{ TT[j][i] = t0 - bet_2 * (alf_3*(T[j ][i-1] + T[j ][i+1]) + alf_1 * T[j+1][i ] + gam_3 * t0); }
				else if (i == i1 && j < j3 && j > j2)
				{
					TT[j][i] = t0 - bet_2 * (alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i - 1] + gam_3 * t0);
				}
				else if (i == i1 && j == j2)
				{ TT[j][i] = t0 - bet_4 * (alf_2*T[j][i - 1] + alf_4 * T[j + 1][i] + alf_3 * T[j][i + 1] + alf_1 * T[j - 1][i] + gam_2 * t0); }
				else if (i > i1 && i < i2 && j == j2)
				{ TT[j][i] = t0 - bet_2 * (alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1 * T[j - 1][i] + gam_3 * t0); }
				else if (i == i2 && j == j2)
				{ TT[j][i] = t0 - bet_3 * (alf_4*T[j - 1][i] + alf_3 * T[j][i - 1] + gam_4 * t0); }
				else if (i == i2 && j < j2 && j>j1)
				{
					TT[j][i] = t0 - bet_2 * (alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i - 1] + gam_3 * t0);
				}
				else if (i == i2 && j == j1)
				{
					TT[j][i] = t0 - bet_4 * (alf_2*T[j][i - 1] + alf_4 * T[j + 1][i] + alf_3 * T[j][i + 1] + alf_1 * T[j - 1][i] + gam_2 * t0);
				}
				else if (i > i2 && i < i3 && j == j1)
				{
					TT[j][i] = t0 - bet_2 * (alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1 * T[j - 1][i] + gam_3 * t0);
				}




				else if (i > 0 && i < i3 && j>0 && j < j1)
				{
					TT[j][i] = t0 - bet_1 * (alf_1*(T[j - 1][i] + T[j + 1][i]) + alf_2 * (T[j][i - 1] + T[j][i + 1]) + gam_1 * t0);
				}
				else if (i > 0 && i < i2 && j>j1 - 1 && j < j2)
				{
					TT[j][i] = t0 - bet_1 * (alf_1*(T[j - 1][i] + T[j + 1][i]) + alf_2 * (T[j][i - 1] + T[j][i + 1]) + gam_1 * t0);
				}
				else if (i > 0 && i<i1 && j>j2 - 1 && j < j3)
				{
					TT[j][i] = t0 - bet_1 * (alf_1*(T[j - 1][i] + T[j + 1][i]) + alf_2 * (T[j][i - 1] + T[j][i + 1]) + gam_1 * t0);
				}






			}
		}
		for (j = 0; j < NY; j++)
		{ for (i = 0; i < NX; i++) 
		{ T[j][i] = TT[j][i]; } }
		idt++; 
		if (idt == DEL)
		{ idt = 0; ndt++; 
		sprintf_s(filename, sizeof(filename), "C:/Users/asbarn/Desktop/учеба2/Числаки/Lab_7/Lab_7/T%d.dat", ndt + 1);
		ofstream fout(filename, ios_base::out | ios_base::trunc | ios_base::binary);
		for (j = 0; j < NY; j++) 
		{ for (i = 0; i < NX; i++)
		{ PRES w = T[j][i];
		fout.write((char*)&w, sizeof w);
		} }
		fout.close();
		}
	} int n_x = NX; 
	int n_y = NY; 
	int n_k = ndt;
	ofstream fou("C:/Users/asbarn/Desktop/учеба2/Числаки/Lab_7/Lab_7/Param.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	fou.write((char*)&n_x, sizeof n_x);
	fou.write((char*)&n_y, sizeof n_y); 
	fou.write((char*)&n_k, sizeof n_y); fou.close();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
