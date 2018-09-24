#include <windows.h> 
#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace std;

enum query {READ = 1, WRITE, EXIT};

struct Student
{
	int num;
	char name[10];
	double grade;
};

void read();
void write();

HANDLE hReadPipe;
HANDLE hWritePipe;
DWORD bytes;

int main(int argc, char *argv[])
{
	hReadPipe = (HANDLE)atoi(argv[1]);
	hWritePipe = (HANDLE)atoi(argv[2]);

	while (true)
	{
		int option;
		cout << "Enter next option\n";
		cout << "1 - Read\n";
		cout << "2 - Write\n";
		cout << "3 - Exit\n";
		cin >> option;

		switch (option)
		{
		case READ:
			WriteFile(hWritePipe, &option, sizeof(option), &bytes, NULL);
			read();
			break;
		case WRITE:
			WriteFile(hWritePipe, &option, sizeof(option), &bytes, NULL);
			write();
			break;
		case EXIT:
			CloseHandle(hWritePipe);
			CloseHandle(hReadPipe);
			return 0;
		}
		
	}
	return 0;
}

void read()
{
	bool err;
	int num;
	cout << "Enter student markbook number: ";
	cin >> num;
	WriteFile(hWritePipe, &num, sizeof(num), &bytes, NULL);
	ReadFile(hReadPipe, &err, sizeof(err), &bytes, NULL);
	if (err)
	{
		cout << "Error: student with such markbook number does not exist\n\n";
		return;
	}
	Student student;
	ReadFile(hReadPipe, &student, sizeof(student), &bytes, NULL);
	cout << "Markbook number: " << student.num << endl;
	cout << "Name: " << student.name << endl;
	cout << "Grade: " << student.grade << endl;

	int out;
	cout << "Write \"1\" to release record\n";
	cin >> out;
	WriteFile(hWritePipe, &out, sizeof(out), &bytes, NULL);
}

void write()
{
	bool err;
	int num;
	cout << "Enter student markbook number: ";
	cin >> num;
	WriteFile(hWritePipe, &num, sizeof(num), &bytes, NULL);
	ReadFile(hReadPipe, &err, sizeof(err), &bytes, NULL);
	if (err)
	{
		cout << "Error: student with such markbook number does not exist\n\n";
		return;
	}
	Student student;
	ReadFile(hReadPipe, &student, sizeof(student), &bytes, NULL);
	cout << "Markbook number: " << student.num << endl;
	cout << "Name: " << student.name << endl;
	cout << "Grade: " << student.grade << endl << endl;

	cout << "Enter new markbook number: ";
	cin >> student.num;
	cout << "Enter new student name: ";
	cin.ignore();
	cin.getline(student.name, 10);
	cout << "Enter new student grade: ";
	cin >> student.grade;

	WriteFile(hWritePipe, &student, sizeof(student), &bytes, NULL);

	int out;
	cout << "Write \"1\" to release record\n";
	cin >> out;
	WriteFile(hWritePipe, &out, sizeof(out), &bytes, NULL);
}
