#pragma once
#include <Windows.h>
class Sync
{
private:
	CRITICAL_SECTION csWrite;
	//HANDLE hSemaphoreRead;
	int maxNum;
	int num;
	HANDLE hEventAllowRead;
	HANDLE hEventAllowWrite;
	CRITICAL_SECTION csNum;

public:
	Sync(int count);
	~Sync();

	void lockRead();
	void lockWrite();
	void openRead();
	void openWrite();
};