#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;
int _rank;
int _processCount;

void InitMatrix(int matr[]);
void PrintMatrix(int arr[]);

int main(int argc, char** argv) {
	srand(time(0));
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &_processCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &_rank);
	int *matrix1 = NULL;
	int *matrix2 = NULL;
	matrix2 = new int[_processCount*_processCount];
	if (_rank == 0) {
		matrix1 = new int[_processCount*_processCount];
		InitMatrix(matrix1);
		InitMatrix(matrix2);
		cout << "Matrix1: " << endl;
		PrintMatrix(matrix1);
		cout << endl;
		cout << "Matrix2: " << endl;
		PrintMatrix(matrix2);
		cout << endl;
	}
	int *result = new int[_processCount];
	MPI_Scatter(matrix1, _processCount, MPI_INT, result, _processCount, MPI_INT, 0, MPI_COMM_WORLD);
	delete[] matrix1;

	MPI_Bcast(matrix2, _processCount*_processCount, MPI_INT, 0, MPI_COMM_WORLD);

	int *result_array = new int[_processCount];
	for (int i = 0; i < _processCount; i++) {
		result_array[i] = 0;
	}
	int counter = 0;
	int c = 0;
	int cell = 0;
	for (int k = 0; k < _processCount;k++)
	{
		cell = 0;
		for (int i = 0; i < _processCount; i++)
			cell += result[i]*matrix2[(i+1)*(k+1)-1];
		result_array[k] = cell;
	}

	delete[] matrix2;
	int *res = new int[_processCount * _processCount];
	MPI_Gather(result_array, _processCount, MPI_INT, res, _processCount, MPI_INT, 0, MPI_COMM_WORLD);
	if (_rank == 0) {
		delete[] result_array;
		cout << "Result: " << endl;
		PrintMatrix(res);
	}

	delete[]res;
	MPI_Finalize();
}

void InitMatrix(int matr[]) {
	for (int i = 0; i < _processCount * _processCount; i++)
		matr[i] = rand() % 4;
}

void PrintMatrix(int arr[]) {
	for (int i = 0; i < _processCount*_processCount; i++) {
		if (i % _processCount == 0 && i != 0) {
			cout << endl;
		}
		cout << arr[i] << "\t ";
	}
}