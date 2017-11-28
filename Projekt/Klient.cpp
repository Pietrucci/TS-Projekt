#include "stdafx.h"
#include "Klient.h"


void klient::main() {
	WSAStartup(DllVersion, &wsaData);

	inet_pton(AF_INET, "127.0.0.1", &adres.sin_addr);
	adres.sin_port = htons(9999);
	adres.sin_family = AF_INET;

	int rozmiarAdresu = sizeof(sockaddr_in);
	gniazdko = socket(AF_INET, SOCK_STREAM, 0);

	while (1) {
		cout << "Trwa proba nawiazania polaczenia..." << endl;
		if (!connect(gniazdko, (SOCKADDR*)&adres, rozmiarAdresu)) {
			system("CLS");
			cout << "Nawiazano polaczenie" << endl;

			odbierz();
			odpakuj();
			program();
			zakoncz();
			cout << "Zakonczono polaczenie." << endl;
			return;
		}
		else
			cout << "Nie mozna nawiazac polaczenia" << endl;
	}
}
void klient::zapakuj() {
	string ciag;

	ciag = operacje.to_string(); //3
	ciag += liczA.to_string(); //32
	ciag += liczB.to_string(); //32
	ciag += status.to_string(); //2
	ciag += id.to_string(); //8 = 77
	ciag += "000";
	//	cout << "Wyslano: " << ciag << endl << endl;

	pakiet[0] = stoi(ciag.substr(0, 8), nullptr, 2);
	pakiet[1] = stoi(ciag.substr(8, 8), nullptr, 2);
	pakiet[2] = stoi(ciag.substr(16, 8), nullptr, 2);
	pakiet[3] = stoi(ciag.substr(24, 8), nullptr, 2);
	pakiet[4] = stoi(ciag.substr(32, 8), nullptr, 2);
	pakiet[5] = stoi(ciag.substr(40, 8), nullptr, 2);
	pakiet[6] = stoi(ciag.substr(48, 8), nullptr, 2);
	pakiet[7] = stoi(ciag.substr(56, 8), nullptr, 2);
	pakiet[8] = stoi(ciag.substr(64, 8), nullptr, 2);
	pakiet[9] = stoi(ciag.substr(72, 8), nullptr, 2);
}
void klient::odpakuj() {
	string ciag;
	bitset<8> wejscie;
	wejscie = pakiet[0];
	ciag = wejscie.to_string();
	wejscie = pakiet[1];
	ciag += wejscie.to_string();
	wejscie = pakiet[2];
	ciag += wejscie.to_string();
	wejscie = pakiet[3];
	ciag += wejscie.to_string();
	wejscie = pakiet[4];
	ciag += wejscie.to_string();
	wejscie = pakiet[5];
	ciag += wejscie.to_string();
	wejscie = pakiet[6];
	ciag += wejscie.to_string();
	wejscie = pakiet[7];
	ciag += wejscie.to_string();
	wejscie = pakiet[8];
	ciag += wejscie.to_string();
	wejscie = pakiet[9];
	ciag += wejscie.to_string();
	//	cout << "Odebrano: " << ciag << endl;

	operacje = stoi(ciag.substr(0, 3), nullptr, 2);
	liczA = stoll(ciag.substr(3, 32), nullptr, 2);
	liczB = stoll(ciag.substr(35, 32), nullptr, 2);
	status = stoi(ciag.substr(67, 2), nullptr, 2);
	id = stoi(ciag.substr(69, 8), nullptr, 2);
}
void klient::test() {
	cout << "operacje: " << operacje << " " << stoi(operacje.to_string(), nullptr, 2) << endl;
	cout << "liczba A: " << liczA << " " << stol(liczA.to_string(), nullptr, 2) << endl;
	cout << "liczba B: " << liczB << " " << stol(liczB.to_string(), nullptr, 2) << endl;
	cout << "status: " << status << " " << stoi(status.to_string(), nullptr, 2) << endl;
	cout << "id: " << id << " " << stoi(id.to_string(), nullptr, 2) << endl;
}
void klient::zeruj() {
	operacje = 0;
	status = 0;
	liczA = 0;
	liczB = 0;
}
void klient::wyslij() {
	zapakuj();
	send(gniazdko, pakiet, 11, 0);
}
bool klient::odbierz() {
	recv(gniazdko, pakiet, 11, 0);
	odpakuj();
	return 1;
}
void klient::wynik() {
	cout << (int)(liczA.to_ulong()) << endl;
}
void klient::zakoncz() {
	zeruj();
	if (shutdown(gniazdko, 2) == 0)
		send(gniazdko, pakiet, 11, 0);
	return;
}
void klient::program() {
	system("CLS");
	cout << "0 - operacje jednoargumentowe\n1 - operacje wieloargumentowe\n";
	int q = -1;
	cin >> q;
	system("CLS");

	if (q == 0)
		cout << "+ dodaj  \t- odejmij\n* pomnoz\t/ podziel\n% modulo\t^ potega\n| suma log.\t& iloczyn log.\n0x0 koniec" << endl << endl;
	if (q == 1)
		cout << "+ dodaj  \t- odejmij\n* pomnoz\t/ podziel\n% modulo\t^ potega\n| suma log.\t& iloczyn log.\n0x koniec" << endl;

	while (1) {
		if (q == 0) {
			long long a, b;
			char znak;
			cin >> a >> znak >> b;
			if (a > zakres || b > zakres) {
				cout << "Przekroczenie zakresu (klient)" << endl;
				continue;
			}

			liczA = a;
			liczB = b;
			status = POWITANIE;

			switch (znak) {
			case '+':
				operacje = DODAWANIE;
				break;
			case '-':
				operacje = ODEJMOWANIE;
				break;
			case '*':
				operacje = MNOZENIE;
				break;
			case '/':
				operacje = DZIELENIE;
				break;
			case '%':
				operacje = MODULO;
				break;
			case '^':
				operacje = POTEGA;
				break;
			case '&':
				operacje = AND;
				break;
			case '|':
				operacje = OR;
				break;
			default:
				return;
			}
			wyslij();
			odbierz();
			if (status == BLAD) { cout << "Przekroczenie zakresu (serwer)" << endl; }
			if (status == WYNIK) { wynik(); }
		}
		if (q == 1) {
			long long a;
			char znak;
			cin >> a >> znak;
			if (a > zakres) {
				cout << "Przekroczenie zakresu (klient)" << endl;
				continue;
			}

			zeruj();
			liczA = a;
			status = WYNIK;

			switch (znak) {
			case 'x':
				status = KONIEC;
				wyslij();
				odbierz();
				wynik();
				return;
			case '+':
				operacje = DODAWANIE;
				break;
			case '-':
				operacje = ODEJMOWANIE;
				break;
			case '*':
				operacje = MNOZENIE;
				break;
			case '/':
				operacje = DZIELENIE;
				break;
			case '%':
				operacje = MODULO;
				break;
			case '^':
				operacje = POTEGA;
				break;
			case '&':
				operacje = AND;
				break;
			case '|':
				operacje = OR;
				break;
			default:
				return;
			}
			wyslij();
			odbierz();
			if (status == BLAD) { cout << "Przekroczenie zakresu (serwer)" << endl; }
			if (status == WYNIK) { wynik(); }
		}
	}
}