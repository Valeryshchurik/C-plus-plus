#include "stdafx.h"
#include "ServerCore.h"
#include "ErrorHandler.h"
ServerCore::ServerCore(/*string name*/)
{
	WSADATA SocketData;
	if(WSAStartup(MAKEWORD(2, 0), &SocketData)!=0)
	{
		ErrorHandler::ErrorInfo(WSAGetLastError());
	}
	//name = "\\\\.\\pipe\\" + name;
	//char* temp=new char[50];
	//strcpy(temp, name.c_str());
	send_bufer = new char[BUFER_SIZE];
	resive_bufer = new char[BUFER_SIZE];
	Serwername = TEXT("\\\\.\\pipe\\Tube1");
	hPipe = CreateNamedPipe(Serwername, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, BUFER_SIZE, BUFER_SIZE, INFINITE, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		ErrorHandler::ErrorInfo(WSAGetLastError());
	}
	if (!ConnectNamedPipe(hPipe, NULL))
	{
		ErrorHandler::ErrorInfo(WSAGetLastError());
	}
	resived_message = resive_bufer;
	resive_bufer = new char[BUFER_SIZE];
	send_bufer = new char[BUFER_SIZE];
	resived_message = resive_bufer;
}
ServerCore::~ServerCore()
{
	CloseHandle(hPipe);
	delete[] send_bufer;
	delete[] resive_bufer;
}
const char* ServerCore::Receve()
{
	for (int i = 0; i < BUFER_SIZE; i++) resive_bufer[i] = '\0';
	DWORD cbRead;
	ReadFile(hPipe, resive_bufer, BUFER_SIZE, &cbRead, NULL);
	return resived_message;
}
void ServerCore::Send(char* message)
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
}
void ServerCore::Kick()
{
	DisconnectNamedPipe(hPipe);
	cout << "Клиент успешно отключен, ожидание нового..." << endl;
	if (!ConnectNamedPipe(hPipe, NULL))
	{
		ErrorHandler::ErrorInfo(WSAGetLastError());
	}
	cout << "Подключился новый клиент" << endl;
}