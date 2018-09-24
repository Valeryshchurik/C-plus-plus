#include "stdafx.h"
#include "ErrorHandler.h"
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#include <iostream>
#include <string>

using namespace std;

void ErrorHandler::ErrorInfo(int ErrorCode)
{
	try
	{
		throw ErrorCode;
	}
	catch (int code)
	{
		string ErrorText;
		switch (code)
		{
		case WSAEINTR: ErrorText = "������ ������� ��������";break;
		case WSAEACCES: ErrorText = "���������� ����������"; break;
		case WSAEFAULT: ErrorText = "��������� �����"; break;
		case WSAEINVAL: ErrorText = "������ � ���������"; break;
		case WSAEMFILE:	"������� ����� ������ �������"; break;
		case WSAEWOULDBLOCK: ErrorText = "������ �������� ����������"; break;
		case WSAEINPROGRESS: ErrorText = "�������� � �������� ��������"; break;
		case WSAEALREADY: ErrorText = "�������� ��� �����������"; break;
		case WSAENOTSOCK: ErrorText = "����� ����� �����������"; break;
		case WSAEDESTADDRREQ: ErrorText = "��������� ����� ������������"; break;
		case WSAEMSGSIZE: ErrorText = "��������� ������� �������"; break;
		case WSAEPROTOTYPE: ErrorText = "������������ ��� ��������� ��� ������"; break;
		case WSAENOPROTOOPT: ErrorText = "������ � ����� ���������"; break;
		case WSAEPROTONOSUPPORT: ErrorText = "�������� �� ��������������"; break;
		case WSAESOCKTNOSUPPORT: ErrorText = "��� ������ �� ��������������"; break;
		case WSAEOPNOTSUPP: ErrorText = "�������� �� ��������������"; break;
		case WSAEPFNOSUPPORT: ErrorText = "��� ���������� �� ��������������"; break;
		case WSAEAFNOSUPPORT: ErrorText = "��� ������� �� �������������� ����������"; break;
		case WSAEADDRINUSE: ErrorText = "����� ��� ������������"; break;
		case WSAEADDRNOTAVAIL: ErrorText = "����������� ����� �� ����� ���� �����������"; break;
		case WSAENETDOWN: ErrorText = "���� ���������"; break;
		case WSAENETUNREACH: ErrorText = "���� �� ���������"; break;
		case WSAENETRESET: ErrorText = "���� ��������� ����������"; break;
		case WSAECONNABORTED: ErrorText = "����������� ����� �����"; break;
		case WSAECONNRESET: ErrorText = "����� �������������"; break;
		case WSAENOBUFS: ErrorText = "�� ������� ������ ��� �������"; break;
		case WSAEISCONN: ErrorText = "����� ��� ���������"; break;
		case WSAENOTCONN: ErrorText = "����� �� ���������"; break;
		case WSAESHUTDOWN: ErrorText = "������ ��������� send : ����� �������� ������"; break;
		case WSAETIMEDOUT: ErrorText = "���������� ���������� ��������  �������"; break;
		case WSAECONNREFUSED: ErrorText = "���������� ���������"; break;
		case WSAEHOSTDOWN: ErrorText = "���� � ����������������� ���������"; break;
		case WSAEHOSTUNREACH: ErrorText = "��� �������� ��� �����"; break;
		case WSAEPROCLIM: ErrorText = "������� ����� ���������"; break;
		case WSASYSNOTREADY: ErrorText = "���� �� ��������"; break;
		case WSAVERNOTSUPPORTED: ErrorText = "������ ������ ����������"; break;
		case WSANOTINITIALISED: ErrorText = "�� ��������� ������������� WS2_32.DLL"; break;
		case WSAEDISCON: ErrorText = "����������� ����������"; break;
		case WSATYPE_NOT_FOUND: ErrorText = "����� �� ������"; break;
		case WSAHOST_NOT_FOUND: ErrorText = "���� �� ������"; break;
		case WSATRY_AGAIN: ErrorText = "������������������ ���� �� ������"; break;
		case WSANO_RECOVERY: ErrorText = "��������������  ������"; break;
		case WSANO_DATA: ErrorText = "��� ������ ������������ ����"; break;
		case WSA_INVALID_HANDLE: ErrorText = "��������� ���������� �������  � �������"; break;
		case WSA_INVALID_PARAMETER: ErrorText = "���� ��� ����� ���������� � �������"; break;
		case WSA_IO_INCOMPLETE: ErrorText = "������ ����� - ������ �� � ���������� ���������"; break;
		case WSA_IO_PENDING: ErrorText = "�������� ���������� �����"; break;
		case WSA_NOT_ENOUGH_MEMORY: ErrorText = "�� ���������� ������"; break;
		case WSA_OPERATION_ABORTED: ErrorText = "�������� ����������"; break;
		case WSASYSCALLFAILURE: ErrorText = "��������� ���������� ���������� ������"; break;
		default: ErrorText = "��� ������ �� ��������"; break;
		}
		cout << "������ WinSock2. ��� " << ErrorCode << " - " << ErrorText << endl;
	}

};