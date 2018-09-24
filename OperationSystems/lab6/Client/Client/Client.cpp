#include "stdafx.h"
#include "ClientCore.h"
#include <sstream>
#include <conio.h>
int SEND_MODE;
void user_interface()
{
	cout << "нажмите 1, для ожидания входящих сообщений" << endl;
	switch (SEND_MODE)
	{
	case ClientCore::NORMAL:
		cout << "нажмите 2, для отправки сообщения" << endl;
		break;
	case ClientCore::TRANSACTIONAL:
		cout << "нажмите 2, для отправки транзакции и ожидания ответа" << endl;
		break;
	case ClientCore::CALL:
		cout << "нажмите 2, для отправки транзакции, ожидания ответа и отключения" << endl;
		break;
	default:
		break;
	}
	if (SEND_MODE == ClientCore::NORMAL) cout << "нажмите 3, для отправки 1000 сообщений" << endl; 
	if (SEND_MODE == ClientCore::NORMAL) cout << "нажмите 4, для отправки 1000 сообщений(усложнённое)" << endl;
	cout << "нажмите 5, для выхода" << endl;
};
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	bool isGood=false;
	while (!isGood)
	{
		cout << "Выберите режим именованного канала" << endl <<
			"1 - Simple Named Pipe" << endl <<
			"2 - Transact Named Pipe" << endl <<
			"3 - Call Named Pipe" << endl <<
			"Select:";
		cin >> SEND_MODE;
		cout << endl;
		switch (SEND_MODE)
		{
		case 1: case 2: case 3: isGood = true;
			break;
		default:
			cout << "Несуществующий вариант: " << SEND_MODE << endl;
			break;
		}
	}
	ClientCore Client(SEND_MODE);
	cout << endl;
	int choise;
	user_interface();
	while (1)
	{
		cin>>choise;
		fflush(stdin);
		switch (choise)
		{
		case 1:
			Client.Receve();
			cout << "Server: " << Client.resived_message << endl;
			break;
		case 2:
		{
			char* message = new char[BUFER_SIZE];
			for (int i = 0; i < BUFER_SIZE; i++) message[i] = '\0';
			cout << "Klient: ";
			gets(message);
			cout << endl;
			Client.Send(message);
			delete[] message;
			break;
		}
		case 3:
			if (SEND_MODE == ClientCore::NORMAL)
			{
				char *message;
				for (int i = 1; i < 1001; i++)
				{
					ostringstream msg;
					msg << "Hello from Client " << i;
					message = new char[msg.str().length() + 1];
					strcpy(message, msg.str().c_str());
					Client.Send(message);
					delete[] message;
				}
			}
			break;
		case 4:
			if (SEND_MODE == ClientCore::NORMAL)
			{
				int number = 0;
				Client.Send("Hello from Client 1");
				cout.clear();
				char *message;
				cin.clear();
				for (; number < 999;)
				{
					Client.Receve();
					cout << Client.resived_message << endl;
					number = atoi(Client.resived_message + sizeof("Hello from Client"));
					ostringstream msg;
					msg << "Hello from Client " << number + 1;
					message = new char[msg.str().length() + 1];
					strcpy(message, msg.str().c_str());
					Client.Send(message);
					delete[] message;
				}
				number = 0;
				Client.Receve();
				cout << Client.resived_message << endl;
				Client.Send("1");
				Client.Fix();
				user_interface();
			}
			break;
		case 5:
			return 0;
			break;
		}
		cin.clear();
	}
}

