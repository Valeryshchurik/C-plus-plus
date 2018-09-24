#include "Sync.h"

Sync::Sync(int count)
{
	maxNum = count;
	num = 0;
	//hSemaphoreRead = CreateSemaphore(NULL, maxNum, maxNum, NULL);
	InitializeCriticalSection(&csWrite);
	InitializeCriticalSection(&csNum);
	hEventAllowRead = CreateEvent(NULL, TRUE, TRUE, NULL);
	hEventAllowWrite = CreateEvent(NULL, TRUE, TRUE, NULL);
}
Sync::~Sync()
{
	//CloseHandle(hSemaphoreRead);
	DeleteCriticalSection(&csWrite);
	CloseHandle(hEventAllowWrite);
	CloseHandle(hEventAllowRead);
	DeleteCriticalSection(&csNum);
}

void Sync::lockRead()
{
	//WaitForSingleObject(hSemaphoreRead, INFINITE);
	WaitForSingleObject(hEventAllowRead, INFINITE);
	EnterCriticalSection(&csNum);
	num++;
	ResetEvent(hEventAllowWrite);
	LeaveCriticalSection(&csNum);
}

void Sync::lockWrite()
{
	/*
	EnterCriticalSection(&csWrite);
	for (int i = 0; i < maxNum; i++)
	{
		WaitForSingleObject(hSemaphoreRead, INFINITE);
	}
	*/
	WaitForSingleObject(hEventAllowWrite, INFINITE);
	EnterCriticalSection(&csWrite);
	ResetEvent(hEventAllowRead);
}

void Sync::openRead()
{
	//ReleaseSemaphore(hSemaphoreRead, 1, NULL);
	EnterCriticalSection(&csNum);
	num--;
	if (num == 0)
		SetEvent(hEventAllowWrite);
	LeaveCriticalSection(&csNum);
}

void Sync::openWrite()
{
	//ReleaseSemaphore(hSemaphoreRead, 1, NULL);
	//LeaveCriticalSection(&csWrite);
	SetEvent(hEventAllowRead);
	LeaveCriticalSection(&csWrite);
}