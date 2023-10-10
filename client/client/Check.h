#pragma once
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Check {
public:
	static void input(T& data, int min = 0) {
		cin.seekg(0, ios::end);
		cin.clear();
		while (true) {
			try {
				cin.unsetf(ios::skipws);
				cin >> data;
				if (data < min) cin.clear(ios::failbit);
				if (cin.good()) {
					break;
				}
				cin.clear();
				cin.ignore(10, '\n');
				throw exception("Неверный ввод!");
			}
			catch (exception& ex) {
				cout << ex.what() << endl;
			}
			catch (...) {
				cout << "Прозошла неизвестная ошибка:(" << endl;
			}
		}
	}
	static void input(T& data, int min, int max) {
		cin.seekg(0, ios::end);
		cin.clear();
		while (true) {
			try {
				cin.unsetf(ios::skipws);
				cin >> data;
				if (data < min || data > max) cin.clear(ios::failbit);
				if (cin.good()) {
					break;
				}
				cin.clear();
				cin.ignore(10, '\n');
				throw exception("Неверный ввод!");
			}
			catch (exception& ex) {
				cout << ex.what() << endl;
			}
			catch (...) {
				cout << "Прозошла неизвестная ошибка:(" << endl;
			}
		}
	}
};

template<>
class Check<string> {
public:
	static string input() {
		string str;
		int s = 1;
		while (s) {
			try {
				s = 0;
				cin.seekg(0, ios::end);
				cin.clear();
				getline(cin, str);
				if (str.size() > 30) {
					s = 1;
					throw exception("Неверный ввод!");
				}
			}
			catch (exception& ex) {
				cout << ex.what() << endl;
			}
			catch (...) {
				cout << "Прозошла неизвестная ошибка:(" << endl;
			}
		}
		return str;
	}
	static string input(int max) {
		string str;
		int s = 1;
		while (s) {
			try {
				s = 0;
				cin.seekg(0, ios::end);
				cin.clear();
				getline(cin, str);
				if (str.size() > max) {
					s = 1;
					throw exception("Неверный ввод!");
				}
			}
			catch (exception& ex) {
				cout << ex.what() << endl;
			}
			catch (...) {
				cout << "Прозошла неизвестная ошибка:(" << endl;
			}
			
		}
		return str;
	}
};
