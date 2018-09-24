#include <fstream>
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main() {
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	map<string, int> Cities;
	int n_cities, n_flights;

	fin >> n_cities >> n_flights;

	for (int i = 0; i < n_cities; ++i) {
		string city;
		fin >> city;
		Cities[city] = i;
	}

	bool** Flights = new bool*[n_cities];
	for (int i = 0; i < n_cities; ++i) {
		Flights[i] = new bool[n_cities];
		for (int j = 0; j < n_cities; ++j) {
			Flights[i][j] = false;
		}
	}

	for (int i = 0; i < n_flights; ++i) {
		string city1, city2;
		fin >> city1 >> city2;
		int j = Cities[city1];
		int k = Cities[city2];
		Flights[j][k] = true;
		Flights[k][j] = true;
	}
	fin.close();

	int** Way = new int*[n_cities];
	for (int i = 0; i < n_cities; ++i) {
		Way[i] = new int[n_cities] {0};
	}

	Way[0][0] = 1;
	for (int i = 1; i < n_cities; ++i) {
		for (int j = 0; j <= i; ++j) {
			int delta = (i == j) ? 0 : 1;
			for (int k = 0; k < n_cities; ++k) {
				if (Flights[k][i] && ((k != j || j == 0) && Way[k][j] != 0 && Way[k][j] + 1 > Way[i][j])) {
					Way[i][j] = Way[k][j] + delta;
					Way[j][i] = Way[i][j];
				}
			}
		}
	}

	if (Way[n_cities - 1][n_cities - 1] == 0)
		fout << "No solution";
	else
		fout << Way[n_cities - 1][n_cities - 1];
	fout.close();
	return 0;
}