#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#include <iostream>
#include <string>
#define BUFER_SIZE 200
using namespace std;
class ServerCore
{
public:
	ServerCore(/*string name*/);
	~ServerCore();
	const char* Receve();
	void Send(char* message);
	const char * resived_message;
	void Kick();
	void Fix() { resive_bufer[0] = 's'; };
private:
	HANDLE hPipe;
	LPTSTR Serwername;
	char* send_bufer;
	char* resive_bufer;
};
