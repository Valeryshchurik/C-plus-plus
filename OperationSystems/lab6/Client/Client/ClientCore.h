#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#include <iostream>
#include <string>
#define BUFER_SIZE 200

using namespace std;
class ClientCore
{
public:
	ClientCore(int mode);
	~ClientCore();
	void Send(char* message);
	const char* Receve();
	const char * resived_message;
	enum ServerMode{ NORMAL=1, CALL=3, TRANSACTIONAL=2 };
	void Fix() { resive_bufer[0] = 's'; };
	const char* Transact(char* message);
private:
	char* send_bufer;
	char* resive_bufer;
	HANDLE hPipe;
	LPTSTR Serwername;
	int CurrentServerMode;
};
