#include <winsock2.h>
#include <Windows.h>
#include "Header.h"
#include <conio.h>
#include "Check.h"


void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }
	char strTemp[50];
	while (true)
	{
		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in dest_addr;
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(1280);
		dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		if (connect(s, (sockaddr*)&dest_addr, sizeof(dest_addr)) == NULL) {
			cout << "Сервер подключен" << endl;
		}
		else {
			cout << "Подключиться к серверу не удалось" << endl;
			exit(-1);
		}
		int choice = 0;
		char res[20];
		int result;
		string password;
		while (1)
		{
			cout << "Главное меню\n" << endl;
			cout << "1.Вход под администратором\n2.Вход под пользователем\n3.Завершение программы\n" << endl;
			int flag;
			Check<int>::input(flag, 1);
			itoa(flag, strTemp, 10);
			send(s, strTemp, 20, 0);
			switch (flag)
			{
			case 1: {
				system("cls");

				cout << "Введите логин администратора: " << endl;
				string temp;
				temp = Check<string>::input(12);
				char* tmp = new char[temp.size() + 1];
				strcpy(tmp, temp.c_str());
				send(s, tmp, temp.size() + 1, 0);
				cout << "Введите пароль администратора: " << endl;
				int exit = 0;
				password.erase();
				for (int i = 0; i < sizeof(password) && exit == 0; i++) {
					password += _getch();
					if (password[i] == '\b' && i == 0) {
						i--; password.erase();
					}
					else {
						if (password[i] == '\b' && i != 0)
						{
							cout << "\b \b";
							i -= 2;
							password.erase(password.size() - 2);
						}
						else { if (password[i] != '\n' && password[i] != '\r') printf("*"); else { password[i] = '\0'; exit = 1; } }
					}
				}
				strcpy(tmp, password.c_str());
				send(s, tmp, temp.size() + 1, 0);
				if (recv(s, res, sizeof(res), 0) != 0)
				{
					result = atoi(res);
					if (result == 1)
					{
						int a = 1;
						while (a)
						{
							system("cls");
							cout << "Меню Администратора\n\n1.Работа с записями\n2.Работа с пользователями\n3.Выход в главное меню\n" << endl;
							int ch;
							Check<int>::input(ch, 1, 3);
							itoa(ch, strTemp, 10);
							send(s, strTemp, 20, 0);
							switch (ch) {
							case 1: {
								system("cls");
								int b = 1;
								while (b)
								{
									system("cls");
									cout << "Меню работы с записями\n\n1.Просмотр заявок\n2.Отправить заявку\n3.Редактирование заявки\n4.Удалить заявку\n5.Рассмотреть заявку\n6.Поиск и фильтрация\n7.Сортировка записей\n8.Записать список заявок в файл\n9.Рассмотреть заявку(Используя метод предпочтения)\n10.Назад" << endl;
									int x;
									Check<int>::input(x, 1, 11);
									itoa(x, strTemp, 10);
									send(s, strTemp, 20, 0);
									switch (x) {
									case 1: { system("cls"); getSuppliers(s); system("pause"); } break;
									case 2: {
										system("cls");
										int num, amount, flag = 1;
										string name;
										float area, volume, turnover;
										while (flag) {
											cout << "Введите название предприятия\n";
											name = Check<string>::input();
											send(s, (name + "\0").c_str(), name.size() + 1, 0);
											recv(s, res, sizeof(res), 0);
											flag = atoi(res);
											if (flag == 1) cout << "Заявка от такого предприятия уже существует!" << endl;
										}
										cout << "Введите объем поставки в ден.экв.$(10000-999999)\n";
										Check<float>::input(volume, 10000, 999999);
										cout << "Введите срок оборачиваемости партии в врем.экв месяц(2-18)\n";
										Check<float>::input(turnover, 2, 18);
										cout << "Введите необходимую площадь склада м.кв.(20-600)\n";
										Check<float>::input(area, 20, 600);
										cout << "Введите количество предоставляемых позициий(1-50)\n";
										Check<int>::input(amount, 1, 50);
										itoa(amount, strTemp, 10);
										send(s, strTemp, 20, 0);
										sprintf(strTemp, "%f\0", area);
										send(s, strTemp, 20, 0);
										sprintf(strTemp, "%f\0", volume);
										send(s, strTemp, 20, 0);
										sprintf(strTemp, "%f\0", turnover);
										send(s, strTemp, 20, 0);
									} break;
									case 3: {
										system("cls");
										getSuppliers(s);
										int num;
										cout << "Введите номер заявки для редактирования\n";
										Check<int>::input(num);
										itoa(num, strTemp, 10);
										send(s, strTemp, 20, 0);
										recv(s, res, sizeof(res), 0);
										num = atoi(res);
										if (num) {
											cout << "Выберите поле для редактирования:\n1.Название предприятия\n2.Площадь склада м.кв.\n3.Объем поставки в ден.экв.$\n4.Количество предоставляемых позициий\n5.Срок оборачиваемости партии в врем.экв месяц\n6.Выход\n";
											int ch;
											Check<int>::input(ch);
											itoa(ch, strTemp, 10);
											send(s, strTemp, 20, 0);
											switch (ch) {
											case 1: {

												string name;
												cout << "Введите название предприятия(если от нового имени уже существует запись - изменения не будут сохранены): ";
												name = Check<string>::input();
												strcpy_s(strTemp, sizeof(strTemp), (name + "\0").c_str());
												send(s, strTemp, 20, 0);

												break;
											}
											case 2: {

												float area;
												cout << "Введите площадь склада м.кв.(30-600)" << endl;
												Check<float>::input(area, 30, 600);
												sprintf(strTemp, "%f\0", area);
												send(s, strTemp, 20, 0);

												break;
											}
											case 3: {

												float volume;
												cout << "Введите объем оборота в ден.экв.$ в месяц(10000-999999)" << endl;
												Check<float>::input(volume, 10000, 999999);
												sprintf(strTemp, "%f\0", volume);
												send(s, strTemp, 20, 0);
												break;
											}
											case 4: {

												int amount;
												cout << "Введите количество предоставляемых позициий(3-50)" << endl;
												Check<int>::input(amount, 3, 50);
												itoa(amount, strTemp, 10);
												send(s, strTemp, 20, 0);

												break;
											}
											case 5: {

												float turnover;
												cout << "Введите срок оборачиваемости партии в врем.экв месяц(2-18)" << endl;
												Check<float>::input(turnover, 2, 18);
												sprintf(strTemp, "%f\0", turnover);
												send(s, strTemp, 20, 0);
												break;
											}
											case 6: {
												system("cls");
												break;
											}
											default:
												cout << "Нет такого пункта." << endl;
											}
											cout << "Данные записаны\n";  system("pause");
										}
										else { cout << "Заявки с таким номером не найдено!"; system("pause"); }
									} break;
									case 4: {
										system("cls");
										getSuppliers(s);
										int num;
										cout << "Введите номер заявки для удаления\n";
										Check<int>::input(num);
										itoa(num, strTemp, 10);
										send(s, strTemp, 20, 0);
										recv(s, res, sizeof(res), 0);
										num = atoi(res);
										if (num) cout << "Заявка удалена\n";
										else cout << "Записи с таким номером не найдено!\n";
										system("pause");

									} break;
									case 5: {
										system("cls");
										getSuppliers(s);
										int num;
										cout << "Введите номер заявки для рассмотрения\n";
										Check<int>::input(num);
										itoa(num, strTemp, 10);
										send(s, strTemp, 20, 0);
										recv(s, res, sizeof(res), 0);
										num = atoi(res);
										system("cls");
										if (num) {
											getSuppliers(s);
											cout << "Вы хотите рассмотреть эту заявку?\n1.Да\n2.Нет\n";
											int choi;
											Check<int>::input(choi, 1, 2);
											itoa(choi, strTemp, 10);
											send(s, strTemp, 20, 0);
											if (choi == 1) {
												cout << "1.Принять заявку\n2.Оставить в обработке\n3.Отказать\n";
												Check<int>::input(choi, 1, 3);
												itoa(choi, strTemp, 10);
												send(s, strTemp, 20, 0);
												cout << "Данные записаны\n";
											}
										}
										else cout << "Заявка с таким номером не найдена или была уже рассмотрена!\n";
										system("pause");
									} break;
									case 6: {
										system("cls");
										cout << "Поиск по:\n1.Номеру заявки\n2.Названию предприятия\n3.Площадь склада м.кв.\n4.Объему поставки в ден.экв.$\n5.Сроку оборачиваемости партии в врем.экв месяц\n6.Количеству предоставляемых позициий\n7.Статусу заявки\n8.Выход\n";
										int ch;
										Check<int>::input(ch, 1, 7);
										itoa(ch, strTemp, 10);
										send(s, strTemp, 20, 0);
										switch (ch) {
										case 1: {
											system("cls");
											int num;
											cout << "Введите номер заявки"<< endl;
											Check<int>::input(num);
											itoa(num, strTemp, 10);
											send(s, strTemp, 20, 0);
											getSuppliers(s);
											system("pause");
											break;
										}
										case 2: {
											system("cls");
											string name;
											cout << "Введите название предприятия: " << endl;
											name = Check<string>::input();
											strcpy_s(strTemp, sizeof(strTemp), (name + "\0").c_str());
											send(s, strTemp, 20, 0);
											getSuppliers(s);
											system("pause");
											break;
										}
										case 3: {
											system("cls");
											float min, max;
											cout << "Введите диапазон значений" << endl << "От : ";
											Check<float>::input(min);
											sprintf(strTemp, "%f\0", min);
											send(s, strTemp, 20, 0);
											cout << "До :";
											Check<float>::input(max);
											sprintf(strTemp, "%f\0", max);
											send(s, strTemp, 20, 0);
											getSuppliers(s);
											system("pause");
											break;
										}
										case 4: {
											system("cls");
											float minf, maxf;
											cout << "Введите диапазон значений" << endl << "От : ";
											Check<float>::input(minf);
											sprintf(strTemp, "%f\0", minf);
											send(s, strTemp, 20, 0);
											cout << "До :";
											Check<float>::input(maxf);
											sprintf(strTemp, "%f\0", maxf);
											send(s, strTemp, 20, 0);
											getSuppliers(s);
											system("pause");
											break;
										}
										case 5: {
											system("cls");
											float mint, maxt;
											cout << "Введите диапазон значений" << endl << "От :";
											Check<float>::input(mint);
											sprintf(strTemp, "%f\0", mint);
											send(s, strTemp, 20, 0);
											cout << "До :";
											Check<float>::input(maxt);
											sprintf(strTemp, "%f\0", maxt);
											send(s, strTemp, 20, 0);
											getSuppliers(s);
											system("pause");
											break;
										}
										case 6: {
											system("cls");
											int min, max;
											cout << "Введите диапазон значений" << endl << "От :";
											Check<int>::input(min);
											itoa(min, strTemp, 10);
											send(s, strTemp, 20, 0);
											cout << "До :";
											Check<int>::input(max);
											itoa(max, strTemp, 10);
											send(s, strTemp, 20, 0);
											getSuppliers(s);
											system("pause");
											break;
										}
										case 7: {
											system("cls");
											int ch;
											cout << "Выберите статус заявки\n1.Принято\n2.В обработке\n3.Отказано" << endl;
											Check<int>::input(ch, 1, 3);
											itoa(ch, strTemp, 10);
											send(s, strTemp, 20, 0);
											getSuppliers(s);
											system("pause");
											break;
										}
										case 8: {
											system("cls");
											break;
										}
										default:
											cout << "Нет такого пункта." << endl;
										}} break;
									case 7: {
										system("cls");
										cout << "Тип сортровки:\n1.Название по алфавиту(а->я)\n2.Название по алфавиту(я->а)\n3.Количеству позициий(от большего к меньшему)\n4.Количеству позициий(от меньшего к большему)\n5.Объем поставки в ден.экв.$(от большего к меньшему)\n6.объем поставки в ден.экв.$(от меньшего к большему)\n7.Выход\n";
										int ch;
										Check<int>::input(ch, 1, 8);
										itoa(ch, strTemp, 10);
										send(s, strTemp, 20, 0);
										switch (ch) {
										case 1: {
											system("cls");
											cout << "Записи отсортированы" << endl;
											system("pause");
											break;
										}
										case 2: {
											system("cls");
											cout << "Записи отсортированы" << endl;
											system("pause");
											break;
										}
										case 3: {
											system("cls");
											cout << "Записи отсортированы" << endl;
											system("pause");
											break;
										}
										case 4: {
											system("cls");
											cout << "Записи отсортированы" << endl;
											system("pause");
											break;
										}
										case 5: {
											system("cls");
											cout << "Записи отсортированы" << endl;
											system("pause");
											break;
										}
										case 6: {
											system("cls");
											cout << "Записи отсортированы" << endl;
											system("pause");
											break;
										}
										case 7: {
											system("cls");
											break;
										}
										default:
											cout << "Нет такого пункта." << endl;
										}

									} break;
									case 8: {
										system("cls");
										cout << "Отчет сохранен!" << endl;
										system("pause");
									} break;
									case 9: {
										system("cls");
										getSuppliers(s);
										int m = getSuppliersAmount(s);
										int n, elem, choice;
										itoa(m, strTemp, 10);
										send(s, strTemp, 20, 0);
										cout << "Введите число экспертов" << endl;
										Check<int>::input(n, 1);
										itoa(n, strTemp, 10);
										send(s, strTemp, 20, 0);
										cout << "1.Ввести оценки вручную\n2.Заполнить автоматичекси" << endl;
										Check<int>::input(choice, 1, 2);
										switch (choice) {
										case 1: {
											for (int i = 0; i < n; i++) {
												cout << "Оценки эксперта №" << i + 1 << endl;
												for (int j = 0; j < m; j++) {
													cout << "Оценка заявки №" << j + 1 << endl;
													Check<int>::input(elem, 0, m);
													itoa(elem, strTemp, 10);
													send(s, strTemp, 20, 0);
												}
												cout << endl;
											}
										}break;
										case 2: {
											for (int i = 0; i < n; i++) {
												for (int j = 0; j < m; j++) {
													elem = rand() % m + 1;
													itoa(elem, strTemp, 10);
													send(s, strTemp, 20, 0);
												}
												cout << endl;
											}
										}break;
										}
										char stroka[100];
										int k = m, flag = 0;
										cout << "Исходная матрица предпочтений:" << endl;
										cout << "Zi/Эj";
										for (int i = 0; i < m; i++) {
											cout.width(3);
											cout << "Z" << i;
										}
										for (int i = 0; i < n * m; i++) {
											if (k == m) {
												flag++;
												cout << "\n  Э" << flag;
												k = 0;
											}
											recv(s, stroka, sizeof(stroka), 0);
											elem = atoi(stroka);
											cout.width(4);
											cout << elem;
											k++;
										}
										cout << endl;
										k = m, flag = 0;
										cout << "Модифицированная матрица предпочтения:" << endl;
										cout << "Zi/Эj";
										for (int i = 0; i < m; i++) {
											cout.width(3);
											cout << "Z" << i + 1;
										}
										for (int i = 0; i < n * m; i++) {
											if (k == m) {
												flag++;
												cout << "\n  Э" << flag;
												k = 0;
											}
											recv(s, stroka, sizeof(stroka), 0);
											elem = atoi(stroka);
											cout.width(4);
											cout << elem;
											k++;
										}
										cout << "\nСуммарные оценки предпочтения:" << endl;
										for (int i = 0; i < m; i++) {
											recv(s, stroka, sizeof(stroka), 0);
											elem = atoi(stroka);
											cout << " K" << i + 1 << " = " << elem;
										}
										float weight;
										cout << "\nИскомые веса заявок:" << endl;
										for (int i = 0; i < m; i++) {
											recv(s, stroka, sizeof(stroka), 0);
											weight = atof(stroka);
											cout << " W" << i + 1 << " = " << weight;
										}
										cout << endl;
										recv(s, stroka, sizeof(stroka), 0);
										elem = atoi(stroka);
										cout << "Наиболее эффективная и выгодняа заявка - " << elem;
										cout << endl;
										system("pause");
									} break;
									case 10: b = 0; break;
									}
								}
							}break;
							case 2: {
								system("cls");
								int c = 1;
								while (c) {
									system("cls");
									cout << "Меню работы с пользователями\n\n1.Просмотр пользователей\n2.Добавить пользователей\n3.Удалить пользователя\n4.Назад\n" << endl;
									int k;
									Check<int>::input(k, 1, 4);
									itoa(k, strTemp, 10);
									send(s, strTemp, 20, 0);
									switch (k) {
									case 1: { system("cls"); getUsers(s); system("pause"); } break;
									case 2: {
										system("cls");
										cout << "Введите логин: " << endl;
										string temp;
										temp = Check<string>::input(12);
										char* tmp = new char[temp.size() + 1];
										strcpy(tmp, temp.c_str());
										send(s, tmp, temp.size() + 1, 0);
										cout << "Введите пароль: " << endl;
										int exit = 0;
										password.erase();
										for (int i = 0; i < sizeof(password) && exit == 0; i++) {
											password += _getch();
											if (password[i] == '\b' && i == 0) {
												i--; password.erase();
											}
											else {
												if (password[i] == '\b' && i != 0)
												{
													cout << "\b \b";
													i -= 2;
													password.erase(password.size() - 2);
												}
												else { if (password[i] != '\n' && password[i] != '\r') printf("*"); else { password[i] = '\0'; exit = 1; } }
											}
										}
										strcpy(tmp, password.c_str());
										send(s, tmp, temp.size() + 1, 0);
										if (recv(s, res, sizeof(res), 0) != 0) {
											result = atoi(res);
											if (result == 0) {
												cout << "\nРегистрация прошла успешно." << endl;
											}
											else if (result == 1)
												cout << "\nТакой логин уже используется." << endl;
											else if (result == 2)
												cout << "\nНеверный ввод" << endl;
										}
										system("pause");
									}break;
									case 3: {
										system("cls");
										string login;
										int num = 0;
										cout << "Введите логин пользователся для удаления\n";
										getline(cin, login);
										getline(cin, login);
										send(s, (login + "\0").c_str(), login.size() + 1, 0);
										recv(s, res, sizeof(res), 0);
										num = atoi(res);
										if (num) cout << "Пользователь удален\n";
										else cout << "Пользователь не найден!\n";
										system("pause");
									}break;
									case 4: c = 0; break;
									}
								}
							}break;
							case 3: a = 0; break;
							}
							
						}
					}
					else if (result == 2)
						cout << "Ошибка ввода" << endl;
					else
						cout << "Неверный ввод." << endl;
				}
				system("cls");
				break;
			}
			case 2: {
				system("cls");
				int t = 1;
				while (t) {
					system("cls");
					cout << "1.Вход\n2.Регистрация\n3.Выход в главное меню\n";
					Check<int>::input(choice);
					itoa(choice, strTemp, 10);
					send(s, strTemp, 20, 0);
					switch (choice) {
					case 1: {
						system("cls");
						cout << "Введите логин: " << endl;
						string temp;
						temp = Check<string>::input(12);
						char* tmp = new char[temp.size() + 1];
						strcpy(tmp, temp.c_str());
						send(s, tmp, temp.size() + 1, 0);
						cout << "Введите пароль: " << endl;
						int exit = 0;
						password.erase();
						for (int i = 0; i < sizeof(password) && exit == 0; i++) {
							password += _getch();
							if (password[i] == '\b' && i == 0) {
								i--; password.erase();
							}
							else {
								if (password[i] == '\b' && i != 0)
								{
									cout << "\b \b";
									i -= 2;
									password.erase(password.size() - 2);
								}
								else { if (password[i] != '\n' && password[i] != '\r') printf("*"); else { password[i] = '\0'; exit = 1; } }
							}
						}
						strcpy(tmp, password.c_str());
						send(s, tmp, temp.size() + 1, 0);
						if (recv(s, res, sizeof(res), 0) != 0) {
							result = atoi(res);
							if (result == 1) {
								system("cls");

								int u = 1;
								while (u) {
									system("cls");
									cout << "Меню пользователя\n\n1.Создать заявку\n2.Просмотреть заявку\n3.Изменить заявку\n4.Напечать заявку\n5.Назад" << endl;
									int x;
									Check<int>::input(x, 1, 5);
									itoa(x, strTemp, 10);
									send(s, strTemp, 20, 0);
									switch (x) {
									case 1: {
										system("cls");
										int num, amount, flag = 1;
										string name;
										float area, volume, turnover;
										while (flag) {
											cout << "Введите название предприятия\n";
											name = Check<string>::input();
											send(s, (name + "\0").c_str(), name.size() + 1, 0);
											recv(s, res, sizeof(res), 0);
											flag = atoi(res);
											if (flag == 1) cout << "Заявка от такого предприятия уже существует!" << endl;
										}
										cout << "Введите объем поставки в ден.экв.$(10000-999999)\n";
										Check<float>::input(volume, 10000, 999999);
										cout << "Введите срок оборачиваемости партии в врем.экв месяц(2-18)\n";
										Check<float>::input(turnover, 2, 18);
										cout << "Введите необходимую площадь склада м.кв.(20-600)\n";
										Check<float>::input(area, 20, 600);
										cout << "Введите количество предоставляемых позициий(1-50)\n";
										Check<int>::input(amount, 1, 50);
										itoa(amount, strTemp, 10);
										send(s, strTemp, 20, 0);
										sprintf(strTemp, "%f\0", area);
										send(s, strTemp, 20, 0);
										sprintf(strTemp, "%f\0", volume);
										send(s, strTemp, 20, 0);
										sprintf(strTemp, "%f\0", turnover);
										send(s, strTemp, 20, 0);
										break;
									}
									case 2: {
										system("cls");
										cout << "Введите название предприятия для просмотра заявки\n";
										string name;
										name = Check<string>::input();
										send(s, (name + "\0").c_str(), name.size() + 1, 0);
										getSuppliers(s);
										system("pause");
										break;
									}
									case 3: {
										system("cls");
										string name;
										int num;
										cout << "Введите название предприятия для редактирования заявки\n";
										name = Check<string>::input();
										strcpy_s(strTemp, sizeof(strTemp), (name + "\0").c_str());
										send(s, strTemp, 20, 0);
										recv(s, res, sizeof(res), 0);
										num = atoi(res);
										if (num) {
											cout << "Выберите поле для редактирования:\n1.Название предприятия\n2.Площадь склада м.кв.\n3.Объем поставки в ден.экв.$\n4.Количество предоставляемых позициий\n5.Срок оборачиваемости партии в врем.экв месяц\n6.Выход\n";
											int ch;
											Check<int>::input(ch);
											itoa(ch, strTemp, 10);
											send(s, strTemp, 20, 0);
											switch (ch) {
											case 1: {
												system("cls");
												string newName;
												cout << "Введите название предприятияВведите название предприятия(если от нового имени уже существует запись - изменения не будут сохранены): ";
												name = Check<string>::input();
												strcpy_s(strTemp, sizeof(strTemp), (newName + "\0").c_str());
												send(s, strTemp, 20, 0);

												break;
											}
											case 2: {
												system("cls");
												float area;
												cout << "Введите площадь склада м.кв.(30-600)" << endl;
												Check<float>::input(area, 30, 600);
												sprintf(strTemp, "%f\0", area);
												send(s, strTemp, 20, 0);

												break;
											}
											case 3: {
												system("cls");
												float volume;
												cout << "Введите объем оборота в ден.экв.$ в месяц(10000-999999)" << endl;
												Check<float>::input(volume, 10000, 999999);
												sprintf(strTemp, "%f\0", volume);
												send(s, strTemp, 20, 0);
												break;
											}
											case 4: {
												system("cls");
												int amount;
												cout << "Введите количество предоставляемых позициий(3-50)" << endl;
												Check<int>::input(amount, 3, 50);
												itoa(amount, strTemp, 10);
												send(s, strTemp, 20, 0);

												break;
											}
											case 5: {
												system("cls");
												float turnover;
												cout << "Введите срок оборачиваемости партии в врем.экв месяц(2-18)" << endl;
												Check<float>::input(turnover, 2, 18);
												sprintf(strTemp, "%f\0", turnover);
												send(s, strTemp, 20, 0);
												break;
											}
											case 6: {
												system("cls");
												break;
											}
											default:
												cout << "Нет такого пункта." << endl;
											}
											cout << "\nДанные записаны" << endl;  system("pause");
										}
										else { cout << "Заявки от такого предприятия не найдено!"; system("pause"); }
										break;
									}
									case 4: {
										system("cls");
										string name;
										cout << "Введите название предприятия для редактирования заявки\n";
										name = Check<string>::input();
										strcpy_s(strTemp, sizeof(strTemp), (name + "\0").c_str());
										send(s, strTemp, 20, 0);
										cout << "Отчет сохранен!" << endl;
										system("pause");
										break;
									}
									case 5: u = 0; break;
									}
								}
							}
							else if (result == 0)
								cout << "Неверно! Повторите ввод!." << endl;
							else if (result == 2)
								cout << "Ошибка ввода" << endl;
							else if (result == -1)
								cout << "Нет зарегистрированных пользователей." << endl;

						}
						system("pause");
						break;
					}
					case 2: {
						system("cls");
						cout << "Введите логин: " << endl;
						string temp;
						temp = Check<string>::input(12);
						char* tmp = new char[temp.size() + 1];
						strcpy(tmp, temp.c_str());
						send(s, tmp, temp.size() + 1, 0);
						cout << "Введите пароль: " << endl;
						int exit = 0;
						password.erase();
						for (int i = 0; i < sizeof(password) && exit == 0; i++) {
							password += _getch();
							if (password[i] == '\b' && i == 0) {
								i--; password.erase();
							}
							else {
								if (password[i] == '\b' && i != 0)
								{
									cout << "\b \b";
									i -= 2;
									password.erase(password.size() - 2);
								}
								else { if (password[i] != '\n' && password[i] != '\r') printf("*"); else { password[i] = '\0'; exit = 1; } }
							}
						}
						strcpy(tmp, password.c_str());
						send(s, tmp, temp.size() + 1, 0);
						if (recv(s, res, sizeof(res), 0) != 0) {
							result = atoi(res);
							if (result == 0) {
								cout << "\nРегистрация прошла успешно." << endl;
							}
							else if (result == 1)
								cout << "\nТакой логин уже используется." << endl;
							else if (result == 2)
								cout << "\nНеверный ввод" << endl;
						}

						system("pause");
						break;
					}
					case 3:
						t = 0;
						break;
					default:
						system("cls");
						cout << "Неверный ввод. Введите другое число\n";
						system("pause");
					}
				}
				system("cls");
				break;
			}
			case 3: return;
			default: {
				cout << "Неверный выбор" << endl;
				break;
			}
			}
		}
		closesocket(s);
	}
	WSACleanup();
}

