#include "stdafx.h"
#include "Serwer.h"
#include <algorithm>

void serwer::main() {
	WSAStartup(DllVersion, &wsaData);
	inet_pton(AF_INET, "127.0.0.1", &adresSerwera.sin_addr);
	adresSerwera.sin_port = htons(9999);
	adresSerwera.sin_family = AF_INET;
	int rozmiarAdresu = sizeof(sockaddr_in);

	gniazdkoListen = socket(AF_INET, SOCK_STREAM, 0);
	bind(gniazdkoListen, (SOCKADDR*)&adresSerwera, rozmiarAdresu);
	listen(gniazdkoListen, SOMAXCONN);

	while (1) {
		cout << "Trwa proba nawiazania polaczenia...";
		gniazdkoKlient = accept(gniazdkoListen, (SOCKADDR*)&adresSerwera, &rozmiarAdresu);
		if (gniazdkoKlient) {

			system("CLS");
			cout << "Nawiazano polaczenie" << endl;

			srand((unsigned int)time(NULL));
			id = rand() % 255 + 1;
			status = POWITANIE;
			zapakuj();
			send(gniazdkoKlient, pakiet, 11, 0);
			program();
			return;
		}
	}
}
void serwer::zapakuj() {
	string ciag;

	ciag = operacje.to_string(); //3
	ciag += liczA.to_string(); //32
	ciag += liczB.to_string(); //32
	ciag += status.to_string(); //2
	ciag += id.to_string(); //8 = 77
	ciag += "000";
	//cout << "Wyslano: " << ciag << endl << endl;

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
void serwer::odpakuj() {
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
}
void serwer::test() {
	cout << "operacje: " << operacje << " " << stoi(operacje.to_string(), nullptr, 2) << endl;
	cout << "liczba A: " << liczA << " " << stol(liczA.to_string(), nullptr, 2) << endl;
	cout << "liczba B: " << liczB << " " << stol(liczB.to_string(), nullptr, 2) << endl;
	cout << "status: " << status << " " << stoi(status.to_string(), nullptr, 2) << endl;
	cout << "id: " << id << " " << stoi(id.to_string(), nullptr, 2) << endl;
	//system("PAUSE");
}
void serwer::zeruj() {
	operacje = 0;
	status = 0;
	liczA = 0;
	liczB = 0;
}
void serwer::wyslij() {
	zapakuj();
	send(gniazdkoKlient, pakiet, 11, 0);
	cout << "Zwrocono wynik" << endl;
}
bool serwer::odbierz() {
	if (recv(gniazdkoKlient, pakiet, 11, 0) != 0) {
		odpakuj();
		return 1;
	}
	std::cout << "Klient zakonczyl polaczenie" << endl;
	return 0;
}
void serwer::error() {
	zeruj();
	status = BLAD;
	cout << "Przekroczono zakres" << endl;
}
void serwer::program() {
	while (1) {
		while (odbierz()) {
			if (status == WYNIK || status == KONIEC) {
				if (status == KONIEC) {
					cout << "Koniec zapytan klienta" << endl;
				}
				//multi
				liczB = posredni;
				bitset<32> pom = liczA;
				liczA = liczB;
				liczB = pom;
				switch ((int)(operacje.to_ulong())) {
				case DODAWANIE:
					if (dodawanie()) { status = WYNIK; }
					else error();
					break;
				case ODEJMOWANIE:
					if (odejmowanie()) { status = WYNIK; }
					else error();
					break;
				case MNOZENIE:
					if (mnozenie()) { status = WYNIK; }
					else error();
					break;
				case DZIELENIE:
					if (dzielenie()) { status = WYNIK; }
					else error();
					break;
				case POTEGA:
					if (potega()) { status = WYNIK; }
					else error();
					break;
				case MODULO:
					if (modulo()) { status = WYNIK; }
					else error();
					break;
				case AND:
					if (and ()) { status = WYNIK; }
					break;
				case OR:
					if (or ()) { status = WYNIK; }
					break;
				default:
					break;
				}
				posredni = liczA;
				wyslij();
			}
			if (status == POWITANIE) {
				//pojedyncze
				switch ((int)(operacje.to_ulong())) {
				case DODAWANIE:
					if (dodawanie()) { status = WYNIK; }
					else error();
					break;
				case ODEJMOWANIE:
					if (odejmowanie()) { status = WYNIK; }
					else error();
					break;
				case MNOZENIE:
					if (mnozenie()) { status = WYNIK; }
					else error();
					break;
				case DZIELENIE:
					if (dzielenie()) { status = WYNIK; }
					else error();
					break;
				case POTEGA:
					if (potega()) { status = WYNIK; }
					else error();
					break;
				case MODULO:
					if (modulo()) { status = WYNIK; }
					else error();
					break;
				case AND:
					if (and ()) { status = WYNIK; }
					break;
				case OR:
					if (or ()) { status = WYNIK; }
					break;
				default:
					break;
				}
				wyslij();
			}
		}
		return;
	}
	return;
}


bool serwer::dodawanie() {
	signed _int64 a = liczA.to_ullong();
	signed _int64 b = liczB.to_ullong();
	signed _int64 wynik = a + b;
	liczA = wynik;
	if (wynik >= zakres) { return 0; }
	return 1;
}
bool serwer::odejmowanie() {
	signed _int64 a = liczA.to_ullong();
	signed _int64 b = liczB.to_ullong();
	signed _int64 wynik = a - b;
	liczA = wynik;
	if (wynik >= zakres) { return 0; }
	return 1;
}
bool serwer::mnozenie() {
	signed _int64 a = liczA.to_ullong();
	signed _int64 b = liczB.to_ullong();
	signed _int64 wynik = a * b;
	liczA = wynik;
	if (wynik >= zakres) { return 0; }
	return 1;
}
bool serwer::dzielenie() {
	signed _int64 a = liczA.to_ullong();
	signed _int64 b = liczB.to_ullong();
	signed _int64 wynik = a / b;
	liczA = wynik;
	if (b == 0 || wynik >= zakres) { return 0; }
	return 1;
}
bool serwer::modulo() {
	signed _int64 a = liczA.to_ullong();
	signed _int64 b = liczB.to_ullong();
	signed _int64 wynik = a % b;
	liczA = wynik;
	if (b == 0 || wynik >= zakres) { return 0; }
	return 1;
}
bool serwer::potega() {
	signed _int64 a = liczA.to_ullong();
	signed _int64 b = liczB.to_ullong();
	signed _int64 wynik = (long)pow(a, b);
	liczA = (long)wynik;
	if (wynik >= zakres) { return 0; }
	return 1;
}
bool serwer:: and () {
	liczA &= liczB;
	return 1;
}
bool serwer:: or () {
	liczA |= liczB;
	return 1;
}