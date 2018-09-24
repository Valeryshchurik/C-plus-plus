//#include <iostream>
//#include <Windows.h>
//#include <string>
//#include <fstream>
//struct mystruct
//{
//	int code;
//	char name[10];
//	double price;
//	int sold;
//	int left;
//};
//using namespace std;
//
//int main(int argc, char *argv[])
//{
	/*STARTUPINFO si;
	PROCESS_INFORMATION info;
	CreateProcess("Creator.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &info);
	CreateProcess("Reporter.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &info);*/
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
	struct Order
	{
		int code;
		char name[256];
		double price;
		int sold;
		int left;
	};
	using namespace std;

	int main(int argc, char *argv[])
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		char commandArgsCreator[520];
		char commandArgsReporter[800];
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION info;
		ZeroMemory(&info, sizeof(PROCESS_INFORMATION));
		strcpy_s(commandArgsCreator, "Creator.exe ");
		strcpy_s(commandArgsReporter, "Reporter.exe ");

		char binaryFile[256];
		cout << "Enter the name of binary file for creator to save the information: ";
		fgets(binaryFile, 256, stdin);
		binaryFile[strlen(binaryFile) - 1] = '\0';
		strcat_s(commandArgsCreator, binaryFile);
		strcat_s(commandArgsReporter, binaryFile);
		cout << "Starting creator...\n";
		CreateProcess("Creator.exe", commandArgsCreator, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &info);
		WaitForSingleObject(info.hProcess, INFINITE);
		CloseHandle(info.hThread);
		CloseHandle(info.hProcess);

		ifstream fin(binaryFile);
		Order ord;
		while (fin.read((char*)&ord, sizeof(ord)))
			cout.write((char*)&ord, sizeof(ord));
		cout << "\n\n";

		char reportFile[256];
		char code[3];
		cout << "Enter the name of report file: ";
		fgets(reportFile, 256, stdin);
		cout << "Enter the report code: ";
		fgets(code, 3, stdin);
		reportFile[strlen(reportFile) - 1] = '\0';
		code[strlen(code) - 1] = '\0';

		strcat_s(commandArgsReporter, " ");
		strcat_s(commandArgsReporter, reportFile);
		strcat_s(commandArgsReporter, " ");
		strcat_s(commandArgsReporter, code);

		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		ZeroMemory(&si, sizeof(PROCESS_INFORMATION));
		cout << "Starting reporter...\n\n";
		CreateProcess("Reporter.exe", commandArgsReporter, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &info);
		WaitForSingleObject(info.hProcess, INFINITE);
		CloseHandle(info.hThread);
		CloseHandle(info.hProcess);
		ifstream finr(reportFile);
		string reportString;
		while (getline(finr, reportString))
			cout << reportString << endl;
		system("pause");
	}
