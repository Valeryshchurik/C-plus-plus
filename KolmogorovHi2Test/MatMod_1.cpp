// MatMod_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <algorithm>
bool Testhisq(double* mas_check, int size, int accuracy, double coef);
bool TestKolm(double* mas_check, int size, double coef);

using namespace std;
int N1 = 1000, N2 = 1000;
int K = 64;
double* randommas = new double[N2 + K];
unsigned long long a0 = 16807;
unsigned long long M = pow(2, 31);
unsigned long long b = 16807;
unsigned long long a;
const double KOLM_QUANT = 1.36;
const double HI_SQ_QUANT = 66.3386;
int main()
{
	ofstream resultbaz("baz.txt");
	ofstream resultMakl("Makl.txt");

	double* multkong = new double[N2 + K];
	double* result1 = new double[N1];
	double* MaklarenResult = new double[N2];
	double* assistant = new double[K];
	multkong[0] = a0;
	for (int i = 1; i < N2 + K; i++)
	{
		multkong[i] = (long long)(b*multkong[i - 1]) % M;
	}
	for (int i = 0; i < N2 + K; i++)
	{
		(double)multkong[i] /= M;
	}
	for (int i = 0; i < N2 + K-1; i++)
	{
		resultbaz << multkong[i] << ", ";
	}
	resultbaz << multkong[N2 + K - 1];
	for (int i = 0; i < N2 + K; i++)
		//randommas[i] = 1;
		randommas[i] = (rand() % 100 / (double)100);
	for (int i = 0; i < 64; i++)
		assistant[i] = multkong[i];
	double x = 0;
	for (int i = 0; i < N2;i++)
	{
		int cell = randommas[i] * K;
		MaklarenResult[i] = assistant[cell];
		assistant[cell] = multkong[63 + i];
		x += MaklarenResult[i];
	}
	for (int i = 0; i < N2-1;i++)
	{
		resultMakl << MaklarenResult[i] <<", ";
	}
	resultMakl << MaklarenResult[N2];
	cout << x / N2<<endl;
	cout << "Testhisq " << Testhisq(multkong, N2, 50, HI_SQ_QUANT) << endl;
	cout << "Testkolm " << TestKolm(multkong, N2, 1.36) << endl;
	cout<< "Testhisq " << Testhisq(MaklarenResult, N2, 50, HI_SQ_QUANT)<<endl;
	cout<< "Testkolm " << TestKolm(MaklarenResult, N2, 1.36)<<endl;
}

bool Testhisq(double* mas_check, int size, int accuracy, double coef)
{
	int* chastoty = new int[accuracy];
	for (int i = 0; i < accuracy; i++)
		chastoty[i] = 0;
	for (int i = 0; i < size; i++)
		chastoty[(int)(mas_check[i] * accuracy)]++;
	double hikvadrat = 0;
	for (int i = 0; i < accuracy; i++)
		hikvadrat += pow(chastoty[i] - N2 / accuracy, 2.0) / N2*accuracy;
	if (hikvadrat < coef)
		return true;
	else return false;
}

bool TestKolm(double* mas_check, int size, double coef)
{
	double* gen= new double[size];
	for (int i = 0; i < size; i++)
		gen[i] = mas_check[i];
	sort(gen, gen + size);
	double kolm = gen[0];
	for (int i = 1; i < size; i++)
		kolm = max(kolm, max(fabs(gen[i] - (double)i / size), fabs(gen[i - 1] - (double)i / size)));
	kolm *= sqrt((double)size);
	if (kolm < KOLM_QUANT)
		return true;
	else return false;
}