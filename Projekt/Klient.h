#ifndef klient_h
#define klient_h

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <iostream>
#include <bitset>
#include <string>
#include "enum.h"
using namespace std;

class klient {

public:

	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	SOCKADDR_IN adres;
	SOCKET gniazdko;

	char pakiet[10];

	bitset<3> operacje;
	bitset<32> liczA;
	bitset<32> liczB;
	bitset<2> status;
	bitset<8> id;

	const long long zakres = (long long)pow(2, 32) / 2 - 1;
	void main();
	void test();
	void odpakuj();
	void zapakuj();
	void zeruj();
	void program();
	void wyslij();
	bool odbierz();
	void wynik();
	void zakoncz();
};


#endif