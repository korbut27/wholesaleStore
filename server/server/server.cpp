#include "Header.h"
#include <Windows.h>
#define MY_SOCKET 327


DWORD WINAPI ThreadFunc(LPVOID client_socket) {
	Store store;
	User users;
	SOCKET s2 = ((SOCKET*)client_socket)[0];
	char buf[200];
	int b = 1;
	char string2[50];
	char login[100];
	char password[100];
	char res[20];
	int c;
	Account client;
	int result;
	while (b)
	{
		recv(s2, string2, sizeof(string2), 0);
		int flag = atoi(string2);
		switch (flag) {
		case 1: {
			recv(s2, login, sizeof(login), 0);
			recv(s2, password, sizeof(password), 0);
			result = client.check(AccountType::admin, login, password);
			itoa(result, res, 10);
			send(s2, res, 20, 0);
			if (result == 0 || result == 2 || result == -1) break;
			int a = 1;
			while (a) {
				recv(s2, string2, sizeof(string2), 0);
				int ch = atoi(string2);
				switch (ch) {
				case 1: {
					int b = 1;
					while (b) {
						recv(s2, string2, sizeof(string2), 0);
						int choise = atoi(string2);
						switch (choise) {
						case 1: {
							store.readFromFile();
							store.showSuppliersServ(s2);
							store.clear();
						}break;
						case 2: {
							store.readFromFile();
							int flag = 1;
							int num, amount;
							string name;
							float area, volume, turnover;
							while (flag) {
								num = store.getSize() + 1;
								recv(s2, string2, sizeof(string2), 0);
								name = string2;
								if (store.checkNameSupplier(name)) flag = 1;
								else flag = 0;
								itoa(flag, res, 10);
								send(s2, res, 20, 0);
							}
							recv(s2, string2, sizeof(string2), 0);
							amount = atoi(string2);
							recv(s2, string2, sizeof(string2), 0);
							area = atof(string2);
							recv(s2, string2, sizeof(string2), 0);
							volume = atof(string2);
							recv(s2, string2, sizeof(string2), 0);
							turnover = atof(string2);
							Supplier supplier(num, amount, name, area, volume, turnover);
							store.addSupplier(supplier);
							store.writeInFile();
							store.clear();
						} break;
						case 3: {
							store.readFromFile();
							store.showSuppliersServ(s2);
							int num;
							recv(s2, string2, sizeof(string2), 0);
							num = atoi(string2);
							int temp = store.checkNumSupplier(num);
							itoa(temp, res, 10);
							send(s2, res, 20, 0);
							if (temp) {

								store.redact(s2, num);
								store.writeInFile();
								store.clear();
							}
						}break;
						case 4: {
							store.readFromFile();
							store.showSuppliersServ(s2);
							int num;
							recv(s2, string2, sizeof(string2), 0);
							num = atoi(string2);
							num = store.deleteSupplier(num);

							if (num) {
								store.writeInFile();

							}
							itoa(num, res, 10);
							send(s2, res, 20, 0);
							store.clear();

						} break;
						case 5: {
							store.readFromFile();
							store.showSuppliersServ(s2);
							int num;
							recv(s2, string2, sizeof(string2), 0);
							num = atoi(string2);
							int temp = store.checkStatSupplier(num);
							itoa(temp, res, 10);
							send(s2, res, 20, 0);
							if (temp) {
								store.consider(s2, num);
								store.writeInFile();
								store.clear();
							}
						}break;
						case 6: {
							store.readFromFile();
							store.search(s2);
							store.clear();
						} break;
						case 7: {
							store.readFromFile();
							store.sorting(s2);
							store.writeInFile();
							store.clear();
						} break;
						case 8: {
							store.readFromFile();
							store.writeInFileReport();
							store.clear();
						} break;
						case 9: {
							store.readFromFile();
							store.showSuppliersServ(s2);
							store.showSuppliersServ(s2);
							store.clear();
							int num;
							recv(s2, string2, sizeof(string2), 0);
							num = atoi(string2);
							store.PreferenceMethod(s2, num);
						} break;
						case 10: b = 0; break;
						}
					}
				} break;
				case 2: {
					int e = 1;
					while (e) {
						recv(s2, string2, sizeof(string2), 0);
						int choise1 = atoi(string2);
						switch (choise1) {
						case 1: {
							users.readFromFile();
							users.showUsersServ(s2);
							users.clear();
						} break;
						case 2: {
							recv(s2, login, sizeof(login), 0);
							recv(s2, password, sizeof(password), 0);
							result = client.registr(AccountType::user, login, password);
							itoa(result, res, 10);
							send(s2, res, 20, 0);
						} break;
						case 3: {
							users.readFromFile();
							string login;
							int num = 0;
							recv(s2, string2, sizeof(string2), 0);
							login = string2;
							num = users.deleteUser(login);

							if (num) {
								users.writeInFile();
							}
							itoa(num, res, 10);
							send(s2, res, 20, 0);
							users.clear();

						} break;
						case 4: e = 0; break;
						}
					}
				}break;
				case 3: a = 0; break;
				}
			}
		}break;
		case 2: {
			int m = 1;
			while (m) {
				recv(s2, string2, sizeof(string2), 0);
				int a = atoi(string2);
				switch (a) {
				case 1: {
					recv(s2, login, sizeof(login), 0);
					recv(s2, password, sizeof(password), 0);
					result = client.check(AccountType::user, login, password);
					itoa(result, res, 10);
					send(s2, res, 20, 0);
					if (result == 0 || result == 2 || result == -1) break;
					c = 1;
					while (c) {
						recv(s2, string2, sizeof(string2), 0);
						int choise = atoi(string2);
						switch (choise) {
						case 1: {
							store.readFromFile();
							int flag = 1;
							int num, amount;
							string name;
							float area, volume, turnover;
							while (flag) {
								num = store.getSize() + 1;
								recv(s2, string2, sizeof(string2), 0);
								name = string2;
								if (store.checkNameSupplier(name)) flag = 1;
								else flag = 0;
								itoa(flag, res, 10);
								send(s2, res, 20, 0);
							}
							recv(s2, string2, sizeof(string2), 0);
							amount = atoi(string2);
							recv(s2, string2, sizeof(string2), 0);
							area = atof(string2);
							recv(s2, string2, sizeof(string2), 0);
							volume = atof(string2);
							recv(s2, string2, sizeof(string2), 0);
							turnover = atof(string2);
							Supplier supplier(num, amount, name, area, volume, turnover);
							store.addSupplier(supplier);
							store.writeInFile();
							store.clear();
						} break;
						case 2: {
							store.readFromFile();
							store.searchName(s2);
							store.clear();
						} break;
						case 3: {
							store.readFromFile();
							string name;
							recv(s2, string2, sizeof(string2), 0);
							name = string2;
							int temp = store.checkNameSupplier(name);
							itoa(temp, res, 10);
							send(s2, res, 20, 0);
							if (temp) {
								store.redactName(s2, name);
								store.writeInFile();
								store.clear();
							}
						} break;
						case 4: {
							store.readFromFile();
							string name;
							recv(s2, string2, sizeof(string2), 0);
							name = string2;
							store.writeInFileUserReport(client.getLogin(), name);
							store.clear();
						} break;
						case 5: c = 0; break;
						}
					}
				}
					  break;
				case 2: {
					recv(s2, login, sizeof(login), 0);
					recv(s2, password, sizeof(password), 0);
					result = client.registr(AccountType::user, login, password);
					itoa(result, res, 10);
					send(s2, res, 20, 0); }
					  break;
				case 3: m = 0; break;
				}
			}
		} break;
		case 3: {
			b = 0;
		} break;
		}
	}
	closesocket(s2);
	return 0;

}

void main() {
	int clientNumb = 0;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	int ip;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(1280);
	local_addr.sin_addr.s_addr = 0;
	local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(s, (sockaddr*)&local_addr, sizeof(local_addr));
	int c = listen(s, 5);
	SOCKET client_socket;
	sockaddr_in client_addr;

	int client_addr_size = sizeof(client_addr);
	cout << "Сервер включен\n";
	cout << "Сокет: " << MY_SOCKET << endl;
	cout << "IP адрес: " <<  inet_ntoa(local_addr.sin_addr)<< endl;
	while ((client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))) {
		clientNumb++;
		serverInfo(clientNumb);
		DWORD thID;
		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID);
	}
}
