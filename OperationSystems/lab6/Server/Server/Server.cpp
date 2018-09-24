#include "stdafx.h"
#include "ServerCore.h"
#include <sstream>
#include <conio.h>
void user_interface()
{
	cout << "нажмите 1, для ожидания входящих сообщений" << endl;
	cout << "нажмите 2, для отправки сообщения" << endl;
	cout << "нажмите 3, для отправки 1000 сообщений" << endl;
	cout << "нажмите 4, для отправки 1000 сообщений(усложнённое)" << endl;
	cout << "нажмите 5, для отключения клиента, и ожидания нового" << endl;
	cout << "нажмите 6, для выхода" << endl;
};
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	char* name = new char[30];
	int chose;
	cout << "Сервер NamedPipe запущен, ожидание входящих подключений..." << endl;
	//cout << "Введите имя канала: ";
	//name = "hell";
	//gets(name);
	//cout << endl;
	ServerCore Server;
	cout << "Обнаруженно входящее подключение" << endl;
	user_interface();
	char* message;
	while (1)
	{
		cin >> chose;
		fflush(stdin);
		switch (chose)
		{
		case 1:
			Server.Receve();
			cout << "Принято сообщение: "<<Server.resived_message << endl;
			break;
		case 2:
				message = new char[BUFER_SIZE];
				for (int i = 0; i < BUFER_SIZE; i++) message[i] = '\0';
				cout << "Serwer: ";
				gets(message);
				cout << endl;
				Server.Send(message);
				delete[] message;
			break;
		case 3:
				for (int i = 0; i < 1000; i++)
				{
					Server.Receve();
					cout << "Klient: " << Server.resived_message << endl;
				}
				user_interface();
			
			break;
		case 4:
				char* res;
				while (1)
				{
					Server.Receve();
					if (Server.resived_message[0] == '1')
					{
						break;
					}
					cout << Server.resived_message << endl;
					res = new char[200];
					strcpy(res, Server.resived_message);
					Server.Send(res);
					delete res;
				}
				user_interface();
				Server.Fix();
				break;
		case 5:
			Server.Kick();
			break;
		case 6:
			return 0;
			break;
		default: break;
		}
		cin.clear();
	}
}

