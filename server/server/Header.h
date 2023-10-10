
#pragma once
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm> 
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;
enum class AccountType { admin, user };
void serverInfo(int clientNumb);

class Account {
	string login, password;
public:
	Account();
	Account(string login, string password);
	int check(AccountType type, char* login, char* password);
	int registr(AccountType type, char* login, char* password);
	void setLogin(string login);
	string getLogin();
	void setPassword(string password);
	string getPassword();
	friend ostream& operator<<(ostream& os, const Account& account);
	friend istream& operator>>(istream& is, Account& account);
};

class User: public Account {
	vector<Account> users;
public:
	User();
	~User() {};
	void readFromFile();
	void showUsersServ(const SOCKET& sock);
	void writeInFile();
	int deleteUser(string login);
	void clear();
};

class Matrix {
private:
	int** Matr;
	int n;
	int m;
	

public:
	void operator = (Matrix matr);
	Matrix();

	Matrix(int i);

	Matrix(int i, int j);


	void Create();

	void Create(int n, int m);

	int& getElement(int i, int j);
	void setElement(int i, int j, int el);
	void output(const SOCKET& sock);

	void input();
	int getN();
	int getM();
};

class PreferenceMatrix: public Matrix {
	Matrix basic;
	Matrix modified;
public:
	PreferenceMatrix();
	PreferenceMatrix(Matrix basic);
	void method1(const SOCKET& sock);
};

class Supplier {
	int num, amount;
	string name;
	float area, volume, turnover;
	string status, payment;
public:
	Supplier();
	Supplier(int num, int amount, string name, float area, float volume, float turnover);
	void setName(string name);
	string getName();
	void setarea(float area);
	float getarea();
	void setNum(int num);
	void setVolume(float volume);
	void setTurnover(float turnover);
	void setAmount(int amount);
	int getNum();
	float getVolume();
	float getTurnover();
	int getAmount();
	friend ostream& operator<<(ostream& os, const Supplier& supplier);
	friend istream& operator>>(istream& is, Supplier& supplier);
	string getStatus();
	void setStatus(string status);
	bool operator>(Supplier ob);
	bool operator<(Supplier ob);
};

class Store: public Supplier {
	string name, reportName;
	vector<Supplier> suppliers;
public:
	Store();
	Store(string name);
	~Store() {};
	void setName(string name);
	void setReportName(string name);
	void showSuppliers();
	void addSupplier();
	void addSupplier(Supplier supplier);
	void writeInFile();
	void writeInFileReport();
	void writeInFileUserReport(string userName, string name);
	void readFromFile();
	void search(const SOCKET& sock);
	void sorting(const SOCKET& sock);
	void searchName(const SOCKET& sock);
	int deleteSupplier(int);
	friend ostream& operator<<(ostream& os, const Store& store);
	void showSuppliersServ(const SOCKET& sock);
	int checkNumSupplier(int num);
	int checkNameSupplier(string name);
	int checkStatSupplier(int num);
	void redact(const SOCKET& sock, int num);
	void redactName(const SOCKET& sock, string name);
	void clear();
	void consider(const SOCKET& sock, int num);
	int getSize();
	void PreferenceMethod(const SOCKET& sock, int m);
};