#include "stdafx.h"
#include "Serwer.h"
#include "Klient.h"
#include "enum.h"
#pragma comment(lib, "ws2_32.lib")

int main() {
	cout << "0 - serwer \n1 - klient" << endl;
	bool q;
	cin >> q;
	system("CLS");
	if (!q) {
		serwer S;
		S.main();
		system("PAUSE");
	}
	else {
		klient K;
		K.main();
		system("PAUSE");
	}
	return 0;
}