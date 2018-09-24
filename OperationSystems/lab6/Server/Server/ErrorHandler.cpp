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
		case WSAEINTR: ErrorText = "Работа функции прервана";break;
		case WSAEACCES: ErrorText = "Разрешение отвергнуто"; break;
		case WSAEFAULT: ErrorText = "Ошибочный адрес"; break;
		case WSAEINVAL: ErrorText = "Ошибка в аргументе"; break;
		case WSAEMFILE:	"Слишком много файлов открыто"; break;
		case WSAEWOULDBLOCK: ErrorText = "Ресурс временно недоступен"; break;
		case WSAEINPROGRESS: ErrorText = "Операция в процессе развития"; break;
		case WSAEALREADY: ErrorText = "Операция уже выполняется"; break;
		case WSAENOTSOCK: ErrorText = "Сокет задан неправильно"; break;
		case WSAEDESTADDRREQ: ErrorText = "Требуется адрес расположения"; break;
		case WSAEMSGSIZE: ErrorText = "Сообщение слишком длинное"; break;
		case WSAEPROTOTYPE: ErrorText = "Неправильный тип протокола для сокета"; break;
		case WSAENOPROTOOPT: ErrorText = "Ошибка в опции протокола"; break;
		case WSAEPROTONOSUPPORT: ErrorText = "Протокол не поддерживается"; break;
		case WSAESOCKTNOSUPPORT: ErrorText = "Тип сокета не поддерживается"; break;
		case WSAEOPNOTSUPP: ErrorText = "Операция не поддерживается"; break;
		case WSAEPFNOSUPPORT: ErrorText = "Тип протоколов не поддерживается"; break;
		case WSAEAFNOSUPPORT: ErrorText = "Тип адресов не поддерживается протоколом"; break;
		case WSAEADDRINUSE: ErrorText = "Адрес уже используется"; break;
		case WSAEADDRNOTAVAIL: ErrorText = "Запрошенный адрес не может быть использован"; break;
		case WSAENETDOWN: ErrorText = "Сеть отключена"; break;
		case WSAENETUNREACH: ErrorText = "Сеть не достижима"; break;
		case WSAENETRESET: ErrorText = "Сеть разорвала соединение"; break;
		case WSAECONNABORTED: ErrorText = "Программный отказ связи"; break;
		case WSAECONNRESET: ErrorText = "Связь восстановлена"; break;
		case WSAENOBUFS: ErrorText = "Не хватает памяти для буферов"; break;
		case WSAEISCONN: ErrorText = "Сокет уже подключен"; break;
		case WSAENOTCONN: ErrorText = "Сокет не подключен"; break;
		case WSAESHUTDOWN: ErrorText = "Нельзя выполнить send : сокет завершил работу"; break;
		case WSAETIMEDOUT: ErrorText = "Закончился отведенный интервал  времени"; break;
		case WSAECONNREFUSED: ErrorText = "Соединение отклонено"; break;
		case WSAEHOSTDOWN: ErrorText = "Хост в неработоспособном состоянии"; break;
		case WSAEHOSTUNREACH: ErrorText = "Нет маршрута для хоста"; break;
		case WSAEPROCLIM: ErrorText = "Слишком много процессов"; break;
		case WSASYSNOTREADY: ErrorText = "Сеть не доступна"; break;
		case WSAVERNOTSUPPORTED: ErrorText = "Данная версия недоступна"; break;
		case WSANOTINITIALISED: ErrorText = "Не выполнена инициализация WS2_32.DLL"; break;
		case WSAEDISCON: ErrorText = "Выполняется отключение"; break;
		case WSATYPE_NOT_FOUND: ErrorText = "Класс не найден"; break;
		case WSAHOST_NOT_FOUND: ErrorText = "Хост не найден"; break;
		case WSATRY_AGAIN: ErrorText = "Неавторизированный хост не найден"; break;
		case WSANO_RECOVERY: ErrorText = "Неопределенная  ошибка"; break;
		case WSANO_DATA: ErrorText = "Нет записи запрошенного типа"; break;
		case WSA_INVALID_HANDLE: ErrorText = "Указанный дескриптор события  с ошибкой"; break;
		case WSA_INVALID_PARAMETER: ErrorText = "Один или более параметров с ошибкой"; break;
		case WSA_IO_INCOMPLETE: ErrorText = "Объект ввода - вывода не в сигнальном состоянии"; break;
		case WSA_IO_PENDING: ErrorText = "Операция завершится позже"; break;
		case WSA_NOT_ENOUGH_MEMORY: ErrorText = "Не достаточно памяти"; break;
		case WSA_OPERATION_ABORTED: ErrorText = "Операция отвергнута"; break;
		case WSASYSCALLFAILURE: ErrorText = "Аварийное завершение системного вызова"; break;
		default: ErrorText = "Тип ошибки не определён"; break;
		}
		cout << "Ошибка WinSock2. Код " << ErrorCode << " - " << ErrorText << endl;
	}

};