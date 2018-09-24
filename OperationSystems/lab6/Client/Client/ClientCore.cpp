#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include "ClientCore.h"
#include "ErrorHandler.h"
ClientCore::ClientCore(int mode)
{
	WSADATA SocketData;
	if (WSAStartup(MAKEWORD(2, 0), &SocketData) != 0)
	{
		ErrorHandler::ErrorInfo(WSAGetLastError());
	}
	send_bufer = new char[BUFER_SIZE];
	resive_bufer = new char[BUFER_SIZE];
	Serwername = TEXT("\\\\.\\pipe\\Tube1"); //"\\servname\pipe\Tube1"
	resived_message = resive_bufer;
	CurrentServerMode = mode;
	if (CurrentServerMode != CALL)
	{
		hPipe = CreateFile(Serwername, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, NULL, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			ErrorHandler::ErrorInfo(WSAGetLastError());
		}
	}
}
ClientCore::~ClientCore()
{
	if (CurrentServerMode != CALL)
		CloseHandle(hPipe);
	WSACleanup();
}
const char* ClientCore::Transact(char* message)
{

	for (int i = 0; i < BUFER_SIZE; i++) send_bufer[i] = '\0';
	int i = 0;
	while (message[i] != '\0')
	{
		send_bufer[i] = message[i];
		i++;
	}
	DWORD cbWritten;
	WriteFile(hPipe, send_bufer, BUFER_SIZE, &cbWritten, NULL);
	for (int i = 0; i < BUFER_SIZE; i++) resive_bufer[i] = '\0';
	DWORD cbRead;
	ReadFile(hPipe, resive_bufer, BUFER_SIZE, &cbRead, NULL);
	return resived_message;
}
const char* ClientCore::Receve()
{
	for (int i = 0; i < BUFER_SIZE; i++) resive_bufer[i] = '\0';
	DWORD cbRead;
	ReadFile(hPipe, resive_bufer, BUFER_SIZE, &cbRead, NULL);
	return resived_message;
}
void ClientCore::Send(char* message)
{
	for (int i = 0; i < BUFER_SIZE; i++) send_bufer[i] = '\0';
	int i = 0;
	while (message[i] != '\0')
	{
		send_bufer[i] = message[i];
		i++;
	}
	DWORD cbWritten;
	switch (CurrentServerMode)
	{
	case NORMAL:
		WriteFile(hPipe, send_bufer, BUFER_SIZE, &cbWritten, NULL);
		break;
	case TRANSACTIONAL:
		Transact(message);
		//TransactNamedPipe(hPipe, send_bufer, BUFER_SIZE, resive_bufer, BUFER_SIZE, &cbWritten, NULL);
		cout << "Ответ транзакции: " << resive_bufer<<endl;
		break;
	case CALL:
		for (int i = 0; i < BUFER_SIZE; i++) resive_bufer[i] = '\0';
		CallNamedPipe(Serwername, send_bufer, BUFER_SIZE, resive_bufer, BUFER_SIZE, &cbWritten, NULL);
		cout << "Ответ транзакции: " << resive_bufer << endl;
		break;
	default:
		break;
	}
}