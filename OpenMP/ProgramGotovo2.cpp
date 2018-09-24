#include <omp.h>
#include <iostream>
#include <ctime>


using namespace std;

double func(double x, double y) {
	return x*y*y;
}

double ompFunction(double A, double B, double C, double D, int N, int vnN, double(*f)(double x, double y)) {
	double result = 0;
	double current = 0;
#pragma omp parallel for private (current)
	for (int i = 0; i < N; ++i)
	{
		current = 0;
		for (int j = 0; j < vnN; j++)
		{
			double x = A + ((double)rand() / RAND_MAX)*(B - A);
			double y = C + ((double)rand() / RAND_MAX)*(D - C);
			current += f(x, y) / N / vnN;
		}
#pragma omp atomic
		result += current;
	}
	double S = (B - A)*(D - C);
	return S*result;
}

int main(int argc, char *argv[])
{
	int N = 750000000;
	int num = 1;
	int jtrying = N / num;
	srand(time(NULL));
	double A = 1;
	double B = 2;
	double C = 0;
	double D = 3;
	double(*p)(double x, double y);
	p = func;
	double result = 0;
	omp_set_num_threads(num);
	double t1 = omp_get_wtime();
	result = ompFunction(A, B, C, D, num, jtrying, p);
	cout << "Function: f(x,y) = x*y^2\nIntegration limits:  x [" << A << "," << B << "]" << " y " << "[" << C <<"," << D
	<< "]\nThe value of the integral: " << result <<
		"\nWorking time in ms: " << (omp_get_wtime() - t1) * 1000 << endl;
	system("pause");
}
