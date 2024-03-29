#include "pch.h"
#include <stdlib.h> 
#include <math.h> 
#include <fstream>
#include "iostream"
#define  PRES  double 
#define  NXB 15
#define  NX        NXB*3+1 
#define  NYB     12 
#define  NY        NYB*3+1 
#define  REP     3000 
#define  EPSL   1.e-5
#define  LL        1.7f 
#define  TEM1   5.0f
#define  TEM2  15.0f

#define  HX    0.2f 
#define  HY    0.3f
using namespace std;
void maxpvr(PRES *t1, PRES *del, PRES *maxdel)
{    PRES d = fabs(*del)/fabs(*t1);  
if (d > *maxdel) *maxdel = d;
}

int main(int argc, char **argv)
{ 
	ofstream foutT("C:/Users/asbarn/Desktop/учеба2/Числаки/Lab6/Lab6/dT.dat",ios_base::out | ios_base::trunc | ios_base::binary);
	ofstream fout1y;
	fout1y.open("file1y.txt", ios::out);
int    i1, i2,i3, j1, j2,j3, rp, i, j, k=0; 
PRES  T1=TEM1,  T2=TEM2, h=HX, r=HY, tx, t0, t1, del, maxdel=0.0f;
PRES  T[NY][NX]; PRES  lam = LL;
PRES  eps = EPSL; 
int    prz = 1; 
int    nT = 0;
PRES  alf_1 = -h / r;
PRES  alf_2 = -r / h;
PRES  alf_3 = alf_2 * 0.5f; 
PRES  alf_4 = alf_1 * 0.5f; 
PRES  gam_1 = -2.f * (alf_1 + alf_2);
PRES  gam_2 = -1.5f * (alf_1 + alf_2);
PRES  gam_3 = -(alf_1 + alf_2); 
PRES  gam_4 = -(alf_3 + alf_4); 
i1 = NXB ;  
i2 = i1 + NXB;
i3 = i2 + NXB;
j1 = NYB;  
j2 = j1 + NYB;
j3 = j2 + NYB;
rp = REP;
for (j = 0; j <= j3; j++)
{ for (i = 0; i <= i3; i++) 
{ T[j][i] = 0.0f; } } 
for (j = j1; j <= j3; j++) T[j][0] = T1;
for (i = 0; i <= i1; i++) T[j3][i] = T1;

for (j = 0; j <= j1; j++) T[j][i3] = T2;
for (i = i2; i <= i3; i++) T[0][i] = T2;

while (k < rp && prz == 1)
{
	k++;
	for (j = 0; j < j3; j++) {
		for (i = 0; i <= i3; i++) {
			t0 = T[j][i];
			if (i == 0 && j < j1 && j > 0)
			{
				
				tx = -(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i + 1]) / gam_3;
			del = lam * (tx - t0); 
			t1 = t0 + del;
			T[j][i] = t1;
			maxpvr(&t1, &del, &maxdel); }
			else if (i == 0 && j == 0)
			{
				tx = -(alf_3*T[j][i + 1] + alf_4 * T[j + 1][i]) / gam_4;
				del = lam * (tx - t0);
				t1 = t0 + del;
				T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel);
			}
			else if (i >0 && i<i2 && j == 0)
			{
				tx = -(alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1 * T[j + 1][i]) / gam_3;
			del = lam * (tx - t0);
			t1 = t0 + del; 
			T[j][i] = t1; 
			maxpvr(&t1, &del, &maxdel); }
			

			if (i == i1 && j < j3 && j > j2) 
			{
				tx = -(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i - 1]) / gam_3;
			del = lam * (tx - t0);
			t1 = t0 + del;
			T[j][i] = t1; 
			maxpvr(&t1, &del, &maxdel);
			}
			else if (i == i1 && j == j2) {
				tx = -(alf_2*T[j][i - 1] + alf_4 * T[j + 1][i] + alf_3 * T[j][i + 1] + alf_1 * T[j-1][i]) / gam_2;
				del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel);
			}
			else if (i > i1 && i < i2 && j == j2)
			{ 
				tx = -(alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1 * T[j - 1][i]) / gam_3;
				del = lam * (tx - t0); 
				t1 = t0 + del; T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel); 
			}


			else if (i == i2 && j == j2)
			{
				tx = -(alf_4*T[j-1][i] + alf_3 * T[j ][i-1]) / gam_4;
				del = lam * (tx - t0);
				t1 = t0 + del; T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel);
			}
			else if (i == i2 && j < j2 && j>j1)
			{
				tx = -(alf_4*(T[j - 1][i] + T[j + 1][i]) + alf_2 * T[j][i - 1]) / gam_3;
				del = lam * (tx - t0);
				t1 = t0 + del; T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel);
			}
			else if (i == i2 && j == j1) {
				tx = -(alf_2*T[j][i - 1] + alf_4 * T[j + 1][i] + alf_3 * T[j][i + 1] + alf_1 * T[j - 1][i]) / gam_2;
				del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel);
			}
			else if (i > i2 && i < i3 && j == j1)
			{
				tx = -(alf_3*(T[j][i - 1] + T[j][i + 1]) + alf_1 * T[j - 1][i]) / gam_3;
				del = lam * (tx - t0);
				t1 = t0 + del; T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel);
			}



			else if (i > 0 && i < i3 && j>0 && j < j1) 
			{ 
				tx = -(alf_1*(T[j - 1][i] + T[j + 1][i]) + alf_2 * (T[j][i - 1] + T[j][i + 1])) / gam_1;
				del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel); 
			}
			else if (i > 0 && i < i2 && j>j1-1 && j < j2)
			{
				tx = -(alf_1*(T[j - 1][i] + T[j + 1][i]) + alf_2 * (T[j][i - 1] + T[j][i + 1])) / gam_1;
				del = lam * (tx - t0); t1 = t0 + del; T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel);
			}
			else if (i > 0 && i<i1 && j>j2 - 1 && j < j3) 
			{ 
				tx = -(alf_1*(T[j - 1][i] + T[j + 1][i]) + alf_2 * (T[j][i - 1] + T[j][i + 1])) / gam_1;
				del = lam * (tx - t0); t1 = t0 + del;
				T[j][i] = t1;
				maxpvr(&t1, &del, &maxdel);
			}
		}
	} 
	nT++;  
	PRES w = maxdel; 
	foutT.write((char*)&w, sizeof w);
	if (maxdel < eps) prz = 0; maxdel = 0.0f;
}
foutT.close();  fout1y.close();

ofstream fouT("C:/Users/asbarn/Desktop/учеба2/Числаки/Lab6/Lab6/nT.dat", ios_base::out | ios_base::trunc | ios_base::binary); fouT.write((char*)&nT, sizeof nT); fouT.close(); 

fout1y.open("file1y.txt", ios::out);  fout1y.write((char*)&nT, sizeof nT); fout1y.close();
// закрываем файл
ofstream fout("C:/Users/asbarn/Desktop/учеба2/Числаки/Lab6/Lab6/Pole.dat",ios_base::out | ios_base::trunc | ios_base::binary);
ofstream fout2y;
fout2y.open("file1y.txt", ios::out);
for (j = 0; j < NY; j++) 
{    for (i = 0; i < NX; i++) 
{  PRES w = T[j][i];  
fout.write((char*)&w, sizeof w);
fout2y.write((char*)&w, sizeof w);
}  

} fout.close(); fout2y.close(); int n_x = NX;  int n_y = NY;



ofstream fou("C:/Users/asbarn/Desktop/учеба2/Числаки/Lab6/Lab6/Param.dat",ios_base::out | ios_base::trunc | ios_base::binary); 
ofstream fout3y;
fout3y.open("file1y.txt", ios::out);
fou.write((char*)&n_x, sizeof n_x); 
fout3y.write((char*)&n_x, sizeof n_x);
fou.write((char*)&n_y, sizeof n_y); fou.close(); 
fout3y.write((char*)&n_y, sizeof n_y); fout3y.close();
} 
