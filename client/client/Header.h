#include <iostream>
#include <iomanip>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

void getSuppliers(const SOCKET& sock) {
	char stroka[100];
	recv(sock, stroka, sizeof(stroka), 0);
	int size = atoi(stroka);
	int num, amount;
	string name;
	float area, volume, turnover;
	string status;
	if (size) {
		cout << "|------------------------------------------------------------------------------------------------------------------------------------------|\n";
		cout << "| № заявки  |     Название предприятия     | Количество поз | Объем поставки в | Требуемая площадь | Оборачиваемость       |     Статус    |\n";
		cout << "|           |                              |                | ден.экв.$        | склада            | в временном экв.месяц |               |\n";
		cout << "|------------------------------------------------------------------------------------------------------------------------------------------|\n";
		for (int i = 0; i < size; ++i) {
			recv(sock, stroka, sizeof(stroka), 0);
			num = atoi(stroka);
			recv(sock, stroka, sizeof(stroka), 0);
			amount = atoi(stroka);
			recv(sock, stroka, sizeof(stroka), 0);
			name = stroka;
			recv(sock, stroka, sizeof(stroka), 0);
			area = atof(stroka);
			recv(sock, stroka, sizeof(stroka), 0);
			volume = atof(stroka);
			recv(sock, stroka, sizeof(stroka), 0);
			turnover = atof(stroka);
			recv(sock, stroka, sizeof(stroka), 0);
			status = stroka;
			cout << "|" << setw(11) << num << "|" << setw(30) << name << "|" << setw(16) << amount << "|" << setw(17) << volume << "$" << "|" << setw(17) << area << "м2" << "|" << setw(21) << turnover << "м." << "|" << setw(15) << status << "|" << endl;
			cout << "|------------------------------------------------------------------------------------------------------------------------------------------|\n";
		}

	}
	else cout << "Нет ни одной записи\n";
}

void getUsers(const SOCKET& sock) {
	char stroka[100];
	recv(sock, stroka, sizeof(stroka), 0);
	int size = atoi(stroka);
	string login, password;
	cout << "Cписок пользователей:" << endl;
	if (size) {
		for (int i = 0; i < size; ++i) {
			recv(sock, stroka, sizeof(stroka), 0);
			login = stroka;
			recv(sock, stroka, sizeof(stroka), 0);
			password = stroka;
			cout << i+1 << setw(11) << login << endl;
		}

	}
	else cout << "Нет ни одной записи\n";
}

int getSuppliersAmount(const SOCKET& sock) {
	char stroka[100];
	recv(sock, stroka, sizeof(stroka), 0);
	int size = atoi(stroka);
	int i;
	if (size) {
		for (i = 0; i < size; ++i) {

			for (int j = 0; j < 7; j++) {
				recv(sock, stroka, sizeof(stroka), 0);
			}
		}
	}
	else cout << "Нет ни одной записи\n";
	return i;
}
