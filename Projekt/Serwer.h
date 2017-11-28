#ifndef serwer_h
#define serwer_h

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <iostream>
#include <bitset>
#include <ctime>
#include <string>
#include "enum.h"
using namespace std;

class serwer {
public:
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	SOCKADDR_IN adresSerwera, adresKlienta;
	SOCKET gniazdkoListen, gniazdkoKlient;

	char pakiet[10];

	bitset<3> operacje;
	bitset<32> liczA;
	bitset<32> liczB;
	bitset<2> status;
	bitset<8> id;

	bitset<32> posredni;

	void main();
	void test();
	void zeruj();
	void wyslij();
	bool odbierz();
	void odpakuj();
	void zapakuj();
	void program();
	void error();


	const  long long zakres = (long long)pow(2, 32) / 2 - 1;

	bool dodawanie();
	bool odejmowanie();
	bool mnozenie();
	bool dzielenie();
	bool modulo();
	bool potega();
	bool and();
	bool or();

};

#endif