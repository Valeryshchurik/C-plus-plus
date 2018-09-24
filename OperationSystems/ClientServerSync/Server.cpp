#include <windows.h> 
#include <stdio.h> 
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstdlib>
#include "Sync.h"
using namespace std;

enum query {READ = 1, WRITE};

struct Student
{
	int num;
	char name[10]; 
	double grade;
};

struct Proc
{
	HANDLE hWritePipe;
	HANDLE hReadPipe;
	vector<unique_ptr<Sync>> *sync;
};


unordered_map <int, int> idx;
HANDLE hMappedFile;
LPVOID pMemory;
fstream file;
int recordCount = 0;
char filename[256];

void createBin();
void printBin();
Proc startClient();
DWORD WINAPI clientThread(LPVOID param);

int main(int argc, char *argv[])
{
	createBin();
	printBin();
	
	int clientNumber;
	cout << "Enter the amount of clients to start: ";
	cin >> clientNumber;
	
	Proc *hClients = new Proc[clientNumber];
	HANDLE *hThreads = new HANDLE[clientNumber];
	vector <unique_ptr<Sync>> sync;
	for (int i = 0; i < recordCount; i++)
		sync.push_back(unique_ptr<Sync>(new Sync(clientNumber)));
	for (int i = 0; i < clientNumber; i++)
	{
		hClients[i] = startClient();
		hClients[i].sync = &sync;
		hThreads[i] = CreateThread(NULL, 0, clientThread, (LPVOID)(&hClients[i]), 0, NULL);
	}
	WaitForMultipleObjects(clientNumber, hThreads, TRUE, INFINITE);
	
	printBin();
	file.close();
	for (int i = 0; i < recordCount; i++)
		CloseHandle(hThreads[i]);
	UnmapViewOfFile(pMemory);
	CloseHandle(hMappedFile);
	cout << "Press any key to exit...\n";
	system("pause");
}

void createBin()
{
	cout << "Enter binary file name: ";
	cin.getline(filename, 256);
	file.open(filename, ios::out | ios::binary | ios::trunc);
	cout << "Enter student info in format: number name grade. End input by typing \"*\"\n";

	while (true)
	{
		char str[60];
		cin.getline(str, 60);
		if (strcmp(str, "*") == 0)
			break;
		Student student;
		char *context = NULL;
		student.num = atoi(strtok_s(str, " ", &context));
		if (idx.find(student.num) != idx.end())
		{
			cout << "Error: student with such markbook number already exists\n";
			continue;
		}
		idx[student.num] = recordCount;
		strcpy_s(student.name, strtok_s(NULL, " ", &context));
		student.grade = atof(strtok_s(str, " ", &context));
		file.write((char*)&student, sizeof(Student));
		
		recordCount++;
	}
	cout << endl;
	
	file.close();
	HANDLE hFile = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	hMappedFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
	pMemory = MapViewOfFile(hMappedFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(Student) * recordCount);
	CloseHandle(hFile);
}

void printBin()
{
	file.open(filename, ios::in | ios::binary);
	Student student;
	file.seekg(0, ios::beg);
	for (int i = 0; i < recordCount; i++)
	{
		file.read((char*)&student, sizeof(Student));
		cout << "Num: " << student.num << endl;
		cout << "Name: " << student.name << endl;
		cout << "Grade: " << student.grade << endl << endl;
	}
	file.seekg(0, ios::beg);
	file.close();
}

Proc startClient()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES sa;
	Proc proc;
	proc.hReadPipe = 0;
	proc.hWritePipe = 0;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	HANDLE hWritePipe[2];
	HANDLE hReadPipe[2];
	for (int i = 0; i < 2; i++)
	{
		if (!CreatePipe(&hReadPipe[i], &hWritePipe[i], &sa, 0))
		{
			cout << "Create pipe failed\n";
			return proc;
		}
	}

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	char commArgs[400];
	sprintf_s(commArgs, "Client.exe %d %d", (int)hReadPipe[1], (int)hWritePipe[0]);
	CreateProcess("Client.exe", commArgs, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	CloseHandle(hReadPipe[1]);
	CloseHandle(hWritePipe[0]);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	proc.hReadPipe = hReadPipe[0];
	proc.hWritePipe = hWritePipe[1];
	return proc;
}

DWORD WINAPI clientThread(LPVOID param)
{
	Proc *proc = (Proc*)param;
	int query;
	int num;
	Student student;
	DWORD bytes;
	HANDLE hReadPipe = proc->hReadPipe;
	HANDLE hWritePipe = proc->hWritePipe;
	vector <unique_ptr<Sync>> *sync = proc->sync;
	int index;
	bool err;

	while (true)
	{
		int unlock;
		ReadFile(hReadPipe, &query, sizeof(query), &bytes, NULL);
		if (bytes == 0)
			break;
		ReadFile(hReadPipe, &num, sizeof(num), &bytes, NULL);
		if (bytes == 0)
			break;
		
		if (idx.find(num) == idx.end())
		{
			err = true;
			WriteFile(hWritePipe, &err, sizeof(err), &bytes, NULL);
			continue;
		}
		err = false;
		WriteFile(hWritePipe, &err, sizeof(err), &bytes, NULL);
		index = idx[num];

		if (query == READ)
		{
			(*sync)[index]->lockRead();
			CopyMemory(&student, (LPVOID)((Student*)pMemory + index), sizeof(Student));
			WriteFile(hWritePipe, &student, sizeof(Student), &bytes, NULL);
			ReadFile(hReadPipe, &unlock, sizeof(unlock), &bytes, NULL);
			(*sync)[index]->openRead();
			if (bytes == 0)
				break;
		}
		else if (query == WRITE)
		{
			(*sync)[index]->lockWrite();
			CopyMemory(&student, (LPVOID)((Student*)pMemory + index), sizeof(Student));
			WriteFile(hWritePipe, &student, sizeof(Student), &bytes, NULL);

			ReadFile(hReadPipe, &student, sizeof(student), &bytes, NULL);
			if (bytes == 0)
				break;

			if (idx.find(student.num) == idx.end())
			{
				idx.erase(num);
				idx[student.num] = index;
			}

			CopyMemory((LPVOID)((Student*)pMemory + index), &student, sizeof(Student));

			ReadFile(hReadPipe, &unlock, sizeof(unlock), &bytes, NULL);
			(*sync)[index]->openWrite();
			if (bytes == 0)
				break;
		}
	}
	return 0;
}