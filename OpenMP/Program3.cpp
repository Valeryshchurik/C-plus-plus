#include <omp.h> 
#include <math.h> 
#include <iostream> 

using namespace std;

double A = 1.0;
double B = 2;
int N = 70000000;
double step = (B - A) / N;

double func(double x) {
	return (x*x*x + 1);
}

double ompFunction(double(*f)(double x)) {
	double result = 0;
#pragma omp parallel for reduction(+:result) 
	for (int i = 0; i < N; ++i)
	{
		double a = A + i*step;
		double b = a + step;
		double res = (b - a)*(f(a) + 4 * f((a + b) / 2) + f(b)) / 6;
		result += res;
	}
	return result;
}

int main()
{
	double(*p)(double x);
	p = func;
	omp_set_num_threads(1);
	double result = 0;
	double t1 = omp_get_wtime();
	result = ompFunction(p);
	double t2 = omp_get_wtime();

	cout << "Function: f(x) = x^3+1\nF(PI/2) - F(0) = " << result <<
		"\nWorking time: " << (t2 - t1) * 1000 << endl;
	system("pause");
}








