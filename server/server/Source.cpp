#include "Header.h"

void serverInfo(int clientNumb) {
	if (clientNumb) {
		cout << clientNumb << " клиент подключен." << endl;
		char tmpbuf[128];
		_tzset();
		_strtime_s(tmpbuf, 128);
		printf("Время:\t\t\t\t%s\n", tmpbuf);
	}
	else
		cout << "Нет подключенных клиентов." << endl;
}
int Account::check(AccountType type, char* login, char* password) {
	int tmp = 0;
	int result = 0;
	char res[20];
	ifstream fin;
	if (type == AccountType::admin)
		fin.open("Admin.txt", ios_base::in);
	else if (type == AccountType::user)
		fin.open("User.txt", ios_base::in);
	else return 0;
	if (!fin) {
		result = -1;
	}

	if (fin) {
		while (!fin.eof()) {
			getline(fin, this->login);
			getline(fin, this->password);
			if (strcmp(login, this->login.c_str()) == 0 && strcmp(password, this->password.c_str()) == 0) {
				result = 1;
			}
		}
		fin.close();
	}
	return result;
}
int Account::registr(AccountType type, char* login, char* password) {
	int tm = 0;
	int r = 0;
	char t[20];
	ofstream fout;
	ifstream fin;
	if (type == AccountType::admin) {
		fin.open("Admin.txt", ios_base::in);
		fout.open("Admin.txt", ios_base::app);
	}
	else if (type == AccountType::user) {
		fin.open("User.txt", ios_base::in);
		fout.open("User.txt", ios_base::app);
	}
	else return 0;
	if (!fout.is_open()) {
		r = -1;
	}
	for (int i = 0; login[i]; i++)
		this->login = login;
	while (!fin.eof()) {
		fin >> login;
		if (strcmp(login, this->login.c_str()) == 0) {
			r = 1;
			fin.close();
		}
	}
	if (r == 0) {
		this->password = password;
		fout << this->login << endl;
		fout << this->password << endl;
		fout.close();
	}
	return r;
}
Account::Account()
{
}
Account::Account(string login, string password)
{
	this->login = login;
}
void Account::setLogin(string login)
{
	this->login = login;
}
string Account::getLogin()
{
	return this->login;
}
void Account::setPassword(string password)
{
	this->password = password;
}
string Account::getPassword()
{
	return this->password;
}
ostream& operator<<(ostream& os, const Account& account)
{
	os << account.login << endl << account.password << endl;
	return  os;
}
istream& operator>>(istream& is, Account& account)
{
	string temp;
	getline(is, account.login);
	getline(is, account.password);
	return is;
}

User::User()
{
}
void User::readFromFile()
{
	clear();
	string nameOfFile = "User.txt";
	ifstream ifs(nameOfFile, ios::in);
	if (ifs.is_open()) {
		cout << "Файл " << nameOfFile << " открыт" << endl;
		while (!ifs.eof()) {
			Account temp;
			ifs >> temp;
			users.push_back(temp);
		}
		users.pop_back();
		ifs.close();
	}
	else {
		cout << "Ошибка открытия файла.Создан новый файл." << "User.txt" << endl;
		ofstream oFile(nameOfFile);
	}
}
void User::showUsersServ(const SOCKET& sock)
{
	char buffer[100];
	sprintf_s(buffer, "%d", users.size());
	send(sock, buffer, sizeof(buffer), 0);
	string login, password;
	for (auto it = users.begin(); it != users.end(); ++it) {
		login = it->getLogin();
		sprintf_s(buffer, "%s\0", login.c_str());
		send(sock, buffer, sizeof(buffer), 0);
		password = it->getPassword();
		sprintf_s(buffer, "%s\0", password.c_str());
		send(sock, buffer, sizeof(buffer), 0);
	}
}
void User::writeInFile()
{
	int i = 0;
	string nameOfFile = "User.txt";
	ofstream ofs(nameOfFile, ios::out);
	if (ofs.is_open()) {
		cout << "Файл " << nameOfFile << " открыт" << endl;
		for (vector<Account>::iterator it = users.begin(); it != users.end(); ++it) {
			ofs << *it;
		}
		ofs.close();
	}
	else {
		cout << "Ошибка открытия файла " << "User.txt" << endl;
	}
}
int User::deleteUser(string login)
{
	int flag = 0, i = 0;
	for (auto it = users.begin(); it != users.end(); it++) {
		if (it->getLogin() == login) { users.erase(it); flag = 1; break; }
	}
	return flag;
}
void User::clear()
{
	users.clear();
}

void Matrix::operator = (Matrix matr) {
	this->n = matr.n;
	this->m = matr.m;
	Create();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			Matr[i][j] = matr.Matr[i][j];
}
Matrix::Matrix() {
	n = 0; m = 0; Matr = NULL;
}
Matrix::Matrix(int i) : n(i), m(i) {
	Create();
}
Matrix::Matrix(int i, int j) : n(i), m(j) {
	Create();
}
void Matrix::Create()
{
	this->Matr = new int* [this->n];
	for (int z = 0; z < this->n; z++)
		Matr[z] = new int[this->m];
}
void Matrix::Create(int n, int m)
{
	this->n = n;
	this->m = m;
	this->Matr = new int* [n];
	for (int z = 0; z < n; z++)
		Matr[z] = new int[m];
}
int& Matrix::getElement(int i, int j)
{
	if (i < n && j < m)
		return Matr[i][j];
}
void Matrix::setElement(int i, int j, int el)
{
	if (i < n && j < m)
		Matr[i][j] = el;
}
void Matrix::output(const SOCKET& sock)
{
	char buffer[100];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			sprintf_s(buffer, "%d", Matr[i][j]);
			send(sock, buffer, sizeof(buffer), 0);
		}
	}
}
int Matrix::getN() {
	return n;
}
int Matrix::getM() {
	return m;
}

PreferenceMatrix::PreferenceMatrix() {

}
PreferenceMatrix::PreferenceMatrix(Matrix basic) {
	this->basic = basic;
}
void PreferenceMatrix::method1(const SOCKET& sock) {
	char buffer[100];
	modified.Create(basic.getN(), basic.getM());
	int n = basic.getN();
	int m = basic.getM();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {

			modified.setElement(i, j, m - basic.getElement(i, j));
		}
	}
	modified.output(sock);
	int* mass = new int[basic.getM()];
	for (int i = 0; i < m; i++) {
		mass[i] = 0;
		for (int j = 0; j < n; j++) {
			mass[i] = mass[i] + modified.getElement(j, i);
		}
	}
	for (int i = 0; i < m; i++) {
		sprintf_s(buffer, "%d", mass[i]);
		send(sock, buffer, sizeof(buffer), 0);
	}
	float* resMass = new float[basic.getM()];
	float sum = 0;
	for (int i = 0; i < m; i++) {
		sum = sum + mass[i];
	}
	for (int i = 0; i < m; i++) {
		resMass[i] = mass[i] / sum;
	}
	for (int i = 0; i < m; i++) {
		sprintf_s(buffer, "%f", resMass[i]);
		send(sock, buffer, sizeof(buffer), 0);
	}
	float max = resMass[0];
	int maxI = 0;
	for (int i = 0; i < m; i++) {
		if (max < resMass[i]) {
			max = resMass[i];
			maxI = i;

		}
	}
	sprintf_s(buffer, "%d", maxI + 1);
	send(sock, buffer, sizeof(buffer), 0);
}

string Supplier::getStatus() {
	return status;
}
void Supplier::setStatus(string status) {
	this->status = status;
}
bool Supplier::operator>(Supplier ob) {
	if (name > ob.name) return true;
	return false;
}
bool Supplier::operator<(Supplier ob) {
	if (name < ob.name) return true;
	return false;
}
Supplier::Supplier() {
	num = 0;
	amount = 0;
	area = 0;
	volume = 0;
	turnover = 0;
	status = "На рассотрении";
}
Supplier::Supplier(int num, int amount, string name, float area, float volume, float turnover) {
	this->num = num;
	this->amount = amount;
	this->name = name;
	this->area = area;
	this->volume = volume;
	this->turnover = turnover;
	status = "В обработке";
}
void Supplier::setName(string name)
{
	this->name = name;
}
void Supplier::setNum(int num) {
	this->num = num;
}
void Supplier::setVolume(float volume) {
	this->volume = volume;
}
void Supplier::setTurnover(float turnover) {
	this->turnover = turnover;
}
void Supplier::setAmount(int amount) {
	this->amount = amount;
}
int Supplier::getNum() {
	return num;
}
float Supplier::getVolume() {
	return volume;
}
float Supplier::getTurnover() {
	return turnover;
}
int Supplier::getAmount() {
	return amount;
}
string Supplier::getName() {
	return this->name;
}
void Supplier::setarea(float area) {
	this->area = area;
}
float Supplier::getarea() {
	return this->area;
}
ostream& operator<<(ostream& os, const Supplier& supplier) {
	os << supplier.num << endl << supplier.name << endl << supplier.area << endl << supplier.volume << endl << supplier.turnover << endl << supplier.amount << endl << supplier.status << endl;
	return  os;
}
istream& operator>>(istream& is, Supplier& supplier) {
	string temp;
	is >> supplier.num;
	getline(is, supplier.name);
	getline(is, supplier.name);
	is >> supplier.area;
	is >> supplier.volume;
	is >> supplier.turnover;
	is >> supplier.amount;
	getline(is, supplier.status);
	getline(is, supplier.status);
	return is;
}

void Store::showSuppliersServ(const SOCKET& sock) {
	char buffer[100];
	sprintf_s(buffer, "%d", suppliers.size());
	send(sock, buffer, sizeof(buffer), 0);
	int num, amount;
	string name;
	float area, volume, turnover;
	string status;
	for (auto it = suppliers.begin(); it != suppliers.end(); ++it) {
		num = it->getNum();
		sprintf_s(buffer, "%d", num);
		send(sock, buffer, sizeof(buffer), 0);
		amount = it->getAmount();
		sprintf_s(buffer, "%d", amount);
		send(sock, buffer, sizeof(buffer), 0);
		name = it->getName();
		sprintf_s(buffer, "%s\0", name.c_str());
		send(sock, buffer, sizeof(buffer), 0);
		area = it->getarea();
		sprintf_s(buffer, "%f", area);
		send(sock, buffer, sizeof(buffer), 0);
		volume = it->getVolume();
		sprintf_s(buffer, "%f", volume);
		send(sock, buffer, sizeof(buffer), 0);
		turnover = it->getTurnover();
		sprintf_s(buffer, "%f", turnover);
		send(sock, buffer, sizeof(buffer), 0);
		status = it->getStatus();
		sprintf_s(buffer, "%s\0", status.c_str());
		send(sock, buffer, sizeof(buffer), 0);
	}
}
int Store::checkNumSupplier(int num) {
	int flag = 0;
	for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
		if (it->getNum() == num) { flag = 1; }
	}
	return flag;
}
int Store::checkNameSupplier(string name)
{
	int flag = 0;
	for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
		if (it->getName() == name) { flag = 1; }
	}
	return flag;
}
int Store::checkStatSupplier(int num) {
	int flag = 0;
	for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
		if (it->getNum() == num && it->getStatus() == "В обработке") { flag = 1; }
	}
	return flag;
}
void Store::redact(const SOCKET& sock, int num) {
	char string2[50];
	recv(sock, string2, sizeof(string2), 0);
	int ch = atoi(string2);
	switch (ch) {
	case 1: { recv(sock, string2, sizeof(string2), 0);
		string name = string2;
		if (checkNameSupplier(name));
		else {
			for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
				if (it->getNum() == num) { it->setName(name); }
			}
		}
	} break;
	case 2: { recv(sock, string2, sizeof(string2), 0);
		float area = atof(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getNum() == num) { it->setarea(area); }
		}
	}break;
	case 3: { recv(sock, string2, sizeof(string2), 0);
		float volume = atof(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getNum() == num) { it->setVolume(volume); }
		}
	}break;
	case 4: {
		recv(sock, string2, sizeof(string2), 0);
		int amount = atoi(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getNum() == num) { it->setAmount(amount); }
		}
	}break;
	case 5: { recv(sock, string2, sizeof(string2), 0);
		float turnover = atof(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getNum() == num) { it->setTurnover(turnover); }
		}
	}break;
	}
}
void Store::redactName(const SOCKET& sock, string name)
{
	char string2[50];
	recv(sock, string2, sizeof(string2), 0);
	int ch = atoi(string2);
	switch (ch) {
	case 1: { recv(sock, string2, sizeof(string2), 0);
		string newName = string2;
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getName() == name) { it->setName(newName); }
		}
	} break;
	case 2: { recv(sock, string2, sizeof(string2), 0);
		float area = atof(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getName() == name) { it->setarea(area); }
		}
	}break;
	case 3: { recv(sock, string2, sizeof(string2), 0);
		float volume = atof(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getName() == name) { it->setVolume(volume); }
		}
	}break;
	case 4: {
		recv(sock, string2, sizeof(string2), 0);
		int amount = atoi(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getName() == name) { it->setAmount(amount); }
		}
	}break;
	case 5: { recv(sock, string2, sizeof(string2), 0);
		float turnover = atof(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getName() == name) { it->setTurnover(turnover); }
		}
	}break;
	}
}
void Store::clear() {
	suppliers.clear();
}
void Store::consider(const SOCKET& sock, int num) {
	for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
		if (it->getNum() == num) {
			int amount;
			string name;
			float area, volume, turnover;
			string status;
			char buffer[100];
			sprintf_s(buffer, "%d", 1);
			send(sock, buffer, sizeof(buffer), 0);
			num = it->getNum();
			sprintf_s(buffer, "%d", num);
			send(sock, buffer, sizeof(buffer), 0);
			amount = it->getAmount();
			sprintf_s(buffer, "%d", amount);
			send(sock, buffer, sizeof(buffer), 0);
			name = it->getName();
			sprintf_s(buffer, "%s\0", name.c_str());
			send(sock, buffer, sizeof(buffer), 0);
			area = it->getarea();
			sprintf_s(buffer, "%f", area);
			send(sock, buffer, sizeof(buffer), 0);
			volume = it->getVolume();
			sprintf_s(buffer, "%f", volume);
			send(sock, buffer, sizeof(buffer), 0);
			turnover = it->getTurnover();
			sprintf_s(buffer, "%f", turnover);
			send(sock, buffer, sizeof(buffer), 0);
			status = it->getStatus();
			sprintf_s(buffer, "%s\0", status.c_str());
			send(sock, buffer, sizeof(buffer), 0);
			char string2[50];
			recv(sock, string2, sizeof(string2), 0);
			int ch = atoi(string2);
			if (ch == 1) {
				recv(sock, string2, sizeof(string2), 0);
				ch = atoi(string2);
				switch (ch) {
				case 1: it->setStatus("Принято");  break;
				case 2: break;
				case 3: it->setStatus("Отказано"); break;
				}
			}
			break;
		}
	}


}
Store::Store() {
	name = "Wholesale Store";
	reportName = "Offer List";
};
void Store::setName(string name) {
	this->name = name;
}
void Store::setReportName(string reportName)
{
	this->reportName = reportName;
}
void Store::showSuppliers() {
	int i = 0;
	for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it, ++i) {
		cout << setw(4) << left << i + 1 << setw(70) << it->getNum() << it->getName() << it->getarea() << it->getVolume() << it->getTurnover() << it->getAmount() << endl;
	}
}
void Store::addSupplier() {
	Supplier temp;
	cin >> temp;
	suppliers.push_back(temp);
}
void Store::addSupplier(Supplier supplier) {
	suppliers.push_back(supplier);
}
void Store::writeInFile() {
	int i = 0;
	string nameOfFile = this->name + ".txt";
	ofstream ofs(nameOfFile, ios::out);
	for (auto it = suppliers.begin(); it != suppliers.end(); it++) {
		i++;
		it->setNum(i);
	}
	if (ofs.is_open()) {
		cout << "Файл " << nameOfFile << " открыт" << endl;
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			ofs << *it;
		}
		ofs.close();
	}
	else {
		cout << "Ошибка открытия файла " << this->name << endl;
	}
}
void Store::writeInFileReport()
{
	string nameOfFile = this->reportName + ".txt";
	ofstream ofs(nameOfFile, ios::out);
	time_t now = time(0);
	char* dt = ctime(&now);
	if (ofs.is_open()) {
		cout << "Файл " << nameOfFile << " открыт" << endl;
		ofs << setw(55) << "ОТЧЁТ " << dt;
		ofs << "|------------------------------------------------------------------------------------------------------------------------------------------|\n";
		ofs << "| № заявки  |         Название ИП          | Количество поз | Объем поставки в | Требуемая площадь | Оборачиваемость       |     Статус    |\n";
		ofs << "|           |                              |                | ден.экв.$        | склада            | в временном экв.месяц |               |\n";
		ofs << "|------------------------------------------------------------------------------------------------------------------------------------------|\n";
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			ofs << "|" << setw(11) << it->getNum() << "|" << setw(30) << it->getName() << "|" << setw(16) << it->getAmount() << "|" << setw(17) << it->getVolume() << "$" << "|" << setw(17) << it->getarea() << "м2" << "|" << setw(21) << it->getTurnover() << "м." << "|" << setw(15) << it->getStatus() << "|" << endl;
			ofs << "|------------------------------------------------------------------------------------------------------------------------------------------|\n";
		}
		ofs.close();
	}
	else {
		cout << "Ошибка открытия файла " << this->name << endl;
	}
}
void Store::writeInFileUserReport(string userName, string name)
{
	string nameOfFile = "UserReport.txt";
	ofstream ofs(nameOfFile, ios::out);
	time_t now = time(0);
	char* dt = ctime(&now);
	int num;
	for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
		if (it->getName() == name) {
			num = it->getNum();
		}
	}
	if (ofs.is_open()) {
		cout << "Файл " << nameOfFile << " открыт" << endl;
		ofs << "ОТЧЁТ по заявке №" << num << endl;
		ofs << "Имя пользователя: " << userName << endl;
		ofs << "Дата создания отчёта: " << dt << endl;
		ofs << "|------------------------------------------------------------------------------------------------------------------------------------------|\n";
		ofs << "| № заявки  |         Название ИП          | Количество поз | Объем поставки в | Требуемая площадь | Оборачиваемость       |     Статус    |\n";
		ofs << "|           |                              |                | ден.экв.$        | склада            | в временном экв.месяц |               |\n";
		ofs << "|------------------------------------------------------------------------------------------------------------------------------------------|\n";
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getName() == name) {
				ofs << "|" << setw(11) << it->getNum() << "|" << setw(30) << it->getName() << "|" << setw(16) << it->getAmount() << "|" << setw(17) << it->getVolume() << "$" << "|" << setw(17) << it->getarea() << "м2" << "|" << setw(21) << it->getTurnover() << "м." << "|" << setw(15) << it->getStatus() << "|" << endl;
				ofs << "|------------------------------------------------------------------------------------------------------------------------------------------|\n.\n.\n.";
			}
		}
		ofs.close();
	}
	else {
		cout << "Ошибка открытия файла " << this->name << endl;
	}
}
void Store::readFromFile() {
	clear();
	string nameOfFile = this->name + ".txt";
	ifstream ifs(nameOfFile, ios::in);
	int i = 0;
	if (ifs.is_open()) {
		cout << "Файл " << nameOfFile << " открыт" << endl;
		while (!ifs.eof()) {
			Supplier temp;
			i++;
			ifs >> temp;
			temp.setNum(i);
			suppliers.push_back(temp);
		}
		suppliers.pop_back();
		ifs.close();
	}
	else {
		cout << "Ошибка открытия файла.Создан новый файл." << this->name << endl;
		ofstream oFile(nameOfFile);
	}
}
void Store::search(const SOCKET& sock) {
	char string2[50];
	vector<Supplier> temp;
	recv(sock, string2, sizeof(string2), 0);
	int ch = atoi(string2);
	switch (ch) {
	case 1: {

		int num;

		recv(sock, string2, sizeof(string2), 0);
		num = atoi(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (num == it->getNum())
				temp.push_back(*it);
		}

		break;
	}
	case 2: {

		string name;
		recv(sock, string2, sizeof(string2), 0);
		name = string2;
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (name == it->getName())
				temp.push_back(*it);
		}

		break;
	}
	case 3: {

		int min, max;
		recv(sock, string2, sizeof(string2), 0);
		min = atoi(string2);
		recv(sock, string2, sizeof(string2), 0);
		max = atoi(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getarea() >= min && it->getarea() <= max)
				temp.push_back(*it);
		}

		break;
	}
	case 4: {

		int minf, maxf;
		recv(sock, string2, sizeof(string2), 0);
		minf = atof(string2);
		recv(sock, string2, sizeof(string2), 0);
		maxf = atof(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getVolume() >= minf && it->getVolume() <= maxf)
				temp.push_back(*it);
		}

		break;
	}
	case 5: {

		int minf, maxf;
		recv(sock, string2, sizeof(string2), 0);
		minf = atof(string2);
		recv(sock, string2, sizeof(string2), 0);
		maxf = atof(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getTurnover() >= minf && it->getTurnover() <= maxf)
				temp.push_back(*it);
		}

		break;
	}
	case 6: {

		int min, max;
		recv(sock, string2, sizeof(string2), 0);
		min = atoi(string2);
		recv(sock, string2, sizeof(string2), 0);
		max = atoi(string2);
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getAmount() >= min && it->getAmount() <= max)
				temp.push_back(*it);
		}

		break;
	}
	case 7: {
		int ch;
		recv(sock, string2, sizeof(string2), 0);
		ch = atoi(string2);
		string status;
		switch (ch) {
		case 1: status = "Принято"; break;
		case 2: status = "В обработке"; break;
		case 3: status = "Отказано"; break;
		}
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			if (it->getStatus() == status)
				temp.push_back(*it);
		}

	}break;
	case 8: {
		return;
	}
	}
	char buffer[100];
	sprintf_s(buffer, "%d", temp.size());
	send(sock, buffer, sizeof(buffer), 0);
	int num, amount;
	string name;
	float area, volume, turnover;
	string status;
	for (auto it = temp.begin(); it != temp.end(); ++it) {
		num = it->getNum();
		sprintf_s(buffer, "%d", num);
		send(sock, buffer, sizeof(buffer), 0);
		amount = it->getAmount();
		sprintf_s(buffer, "%d", amount);
		send(sock, buffer, sizeof(buffer), 0);
		name = it->getName();
		sprintf_s(buffer, "%s\0", name.c_str());
		send(sock, buffer, sizeof(buffer), 0);
		area = it->getarea();
		sprintf_s(buffer, "%f", area);
		send(sock, buffer, sizeof(buffer), 0);
		volume = it->getVolume();
		sprintf_s(buffer, "%f", volume);
		send(sock, buffer, sizeof(buffer), 0);
		turnover = it->getTurnover();
		sprintf_s(buffer, "%f", turnover);
		send(sock, buffer, sizeof(buffer), 0);
		status = it->getStatus();
		sprintf_s(buffer, "%s\0", status.c_str());
		send(sock, buffer, sizeof(buffer), 0);
	}
}
void Store::sorting(const SOCKET& sock)
{
	char string2[50];
	recv(sock, string2, sizeof(string2), 0);
	int ch = atoi(string2);
	switch (ch) {
	case 1: {
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			int i = 0;
			vector<Supplier>::iterator itPrevious = suppliers.begin();
			vector<Supplier>::iterator itCurrent = itPrevious;
			while (itPrevious != suppliers.end())
			{
				if (itPrevious != suppliers.end() - 1) itCurrent++;
				i++;
				if (itPrevious->getName() > itCurrent->getName())
				{
					swap(suppliers[i - 1], suppliers[i]);
				}
				itPrevious++;

			}
		}
		break;
	}
	case 2: {
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			int i = 0;
			vector<Supplier>::iterator itPrevious = suppliers.begin();
			vector<Supplier>::iterator itCurrent = itPrevious;
			while (itPrevious != suppliers.end())
			{
				if (itPrevious != suppliers.end() - 1) itCurrent++;
				i++;
				if (itCurrent->getName() > itPrevious->getName())
				{
					swap(suppliers[i - 1], suppliers[i]);
				}
				itPrevious++;

			}
		}
		break;
	}
	case 3: {
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			int i = 0;
			vector<Supplier>::iterator itPrevious = suppliers.begin();
			vector<Supplier>::iterator itCurrent = itPrevious;
			while (itPrevious != suppliers.end())
			{
				if (itPrevious != suppliers.end() - 1) itCurrent++;
				i++;
				if (itPrevious->getAmount() < itCurrent->getAmount())
				{
					swap(suppliers[i - 1], suppliers[i]);
				}
				itPrevious++;
			}
		}
		break;
	}
	case 4: {
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			int i = 0;
			vector<Supplier>::iterator itPrevious = suppliers.begin();
			vector<Supplier>::iterator itCurrent = itPrevious;
			while (itPrevious != suppliers.end())
			{
				if (itPrevious != suppliers.end() - 1) itCurrent++;
				i++;
				if (itPrevious->getAmount() > itCurrent->getAmount())
				{
					swap(suppliers[i - 1], suppliers[i]);
				}
				itPrevious++;
			}
		}
		break;
	}
	case 5: {
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			int i = 0;
			vector<Supplier>::iterator itPrevious = suppliers.begin();
			vector<Supplier>::iterator itCurrent = itPrevious;
			while (itPrevious != suppliers.end())
			{
				if (itPrevious != suppliers.end() - 1) itCurrent++;
				i++;
				if (itPrevious->getVolume() < itCurrent->getVolume())
				{
					swap(suppliers[i - 1], suppliers[i]);
				}
				itPrevious++;
			}
		}
		break;
	}
	case 6: {
		for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
			int i = 0;
			vector<Supplier>::iterator itPrevious = suppliers.begin();
			vector<Supplier>::iterator itCurrent = itPrevious;
			while (itPrevious != suppliers.end())
			{
				if (itPrevious != suppliers.end() - 1) itCurrent++;
				i++;
				if (itPrevious->getVolume() > itCurrent->getVolume())
				{
					swap(suppliers[i - 1], suppliers[i]);
				}
				itPrevious++;
			}
		}
		break;
	}
	case 7: {
		return;
	}
	}

}
int Store::deleteSupplier(int num) {
	int flag = 0, i = 0;
	for (auto it = suppliers.begin(); it != suppliers.end(); it++) {
		if (it->getNum() == num) { suppliers.erase(it); flag = 1; break; }
	}
	for (auto it = suppliers.begin(); it != suppliers.end(); it++) {
		i++;
		it->setNum(i);
	}
	return flag;
}
void Store::searchName(const SOCKET& sock) {

	char string2[50];

	vector<Supplier> temp;
	recv(sock, string2, sizeof(string2), 0);
	string name;
	name = string2;
	for (vector<Supplier>::iterator it = suppliers.begin(); it != suppliers.end(); ++it) {
		if (name == it->getName())
			temp.push_back(*it);
	}

	char buffer[100];
	sprintf_s(buffer, "%d", temp.size());
	send(sock, buffer, sizeof(buffer), 0);
	int num, amount;
	float area, volume, turnover;
	string status;
	for (auto it = temp.begin(); it != temp.end(); ++it) {
		num = it->getNum();
		sprintf_s(buffer, "%d", num);
		send(sock, buffer, sizeof(buffer), 0);
		amount = it->getAmount();
		sprintf_s(buffer, "%d", amount);
		send(sock, buffer, sizeof(buffer), 0);
		name = it->getName();
		sprintf_s(buffer, "%s\0", name.c_str());
		send(sock, buffer, sizeof(buffer), 0);
		area = it->getarea();
		sprintf_s(buffer, "%f", area);
		send(sock, buffer, sizeof(buffer), 0);
		volume = it->getVolume();
		sprintf_s(buffer, "%f", volume);
		send(sock, buffer, sizeof(buffer), 0);
		turnover = it->getTurnover();
		sprintf_s(buffer, "%f", turnover);
		send(sock, buffer, sizeof(buffer), 0);
		status = it->getStatus();
		sprintf_s(buffer, "%s\0", status.c_str());
		send(sock, buffer, sizeof(buffer), 0);
	}
}
ostream& operator<<(ostream& os, const Store& store) {
	os << store.name << endl;
	return os;
}
int Store::getSize() {
	return suppliers.size();
}
void Store::PreferenceMethod(const SOCKET& sock, int m)
{
	int elem;
	char string2[50];
	recv(sock, string2, sizeof(string2), 0);
	int n = atoi(string2);
	Matrix matr(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			recv(sock, string2, sizeof(string2), 0);
			elem = atoi(string2);
			matr.setElement(i, j, elem);
		}
	}
	matr.output(sock);
	PreferenceMatrix pref(matr);
	pref.method1(sock);
}

