#include <omp.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <cmath>
using namespace std;
double step = 0.00209439510239319549230842892219;
int N = 10000000;
static void Print(const std::stringstream& buffer);
	static double GetEllapsedMilliseconds(double startTime)
	{
		return (omp_get_wtime() - startTime) * 1000;
	}
int main()
{
	omp_set_num_threads(16);
	double time1 = omp_get_wtime();
	double time2 = omp_get_wtime();
	cout << (time2 - time1) * 1000 << endl;
	auto startTime = omp_get_wtime();
	double min = 10;
	double max = -3;
	double func;
	omp_set_nested(true);
#pragma omp sections nowait
	{
#pragma omp section
		{
			cout << "Start section min\n";
#pragma omp parallel for shared(min) private (func)
			for (int i = 0;i < N;i++)
			{
				func = sin((double)i*step) + cos((double)i*step);
				if (func < min)
					min = func;
			}
		}

#pragma omp section
		{
#pragma omp parallel for shared(max) private (func)
			for (int i = 0;i < N; i++)
			{
				func = sin((double)i*step) + cos((double)i*step);
				if (func > max)
					max = func;
			}
		}
	}
	std::cout << "Min of func=" << min << endl;
	std::cout << "Max of func=" << max << endl;
	auto ms = GetEllapsedMilliseconds(startTime);
	std::cout << "Time: " << ms << " ms" << std::endl;
	system("pause");
}
static void Print(const std::stringstream& buffer)
{
	std::cout << buffer.str();
}