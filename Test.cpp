#define _CRT_SECURE_NO_WARNINGS
#include <iostream>	
#include <cstdlib>
#include <iomanip>
#include <cstring>

using namespace std;

enum class State {
	FREE = 1,
	FULL = 2,
	PARTIAL_FULL = 3,
	RESERVED = 4,
	PARTIAL_RESERVED = 5,
	DISC_ERROR = 6
};

//сервер
class Server {		//айди;объем;состояние;
private:
	int id;
	int capacity;
	State state;
public:
	void input() {
		cout << "Введите ID сервера: \n";
		cin >> id;
		cout << "Введите объём: \n";
		cin >> capacity;
		cout << "Введите состояние сервера из привиденных ниже: \n1. Свободен\n2. Полный\n3. Частично заполнен\n4. Зарезервирован\n5. Частично зарезервирован\n6. Ошибка диска!\n";
		int state_code;
		cin >> state_code;
		state = (State)state_code;
	}
	void print() const {
		cout << "ID: " << id <<
			"Объём: " << capacity << "Тб" << 
			"Состояние: " << (int)state << endl;
	}
	void get_id(){}

};

//пользователь
class User {		//айди_сервера;айди_пользователя;имя;
private:
	int server_id;
	int user_id;
	char name[50];	
public:
	void input() {
		cout << "Введите ID сервера, на котором\nбудет расположен пользователь: \n";
		cin >> server_id;
		cout << "Введите ID пользователя: \n";
		cin >> user_id;
		cout << "Введите имя пользователя: \n";
		cin >> name;
	}
	void print(){
		cout << "\nID сервера: " << server_id <<
			"\nID пользователя: " << user_id <<
			"\nИмя пользователя: " << name << endl;
	}
	void get_id(){}
};

struct NodeServer {
	Server data;
	NodeServer* next;
};

struct NodeUser {
	User data;
	NodeUser* next;
};

class ServerList {
private:
	NodeServer* head;
};

class UserList {
private:
	NodeUser* head;
public:
	UserList() {
		head = NULL;
	}

	void add() {
		NodeUser* node_user_ptr = new NodeUser;
		node_user_ptr->data.input();
		node_user_ptr->next = NULL;

		if (head == NULL) {
			head = node_user_ptr;
		}
		else {
			NodeUser* current = head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = node_user_ptr;
		}
	}
};

void menu() {

	cout << "\n1. Добавить\n";
	cout << "2. Вывод\n";
	cout << "3. Удалить\n";
	cout << "4. Поиск по пользователю\n";
	cout << "5. Пользователи сервера\n";
	cout << "6. Свободные сервера\n";
	cout << "7. Сортировка\n";
	cout << "8. Сохранить\n";
	cout << "9. Загрузить\n";
	cout << "10. Выход\n";
}

int main() {
	system("chcp 1251>nul");

	ServerList Servers;
	UserList Users;
	int cmd = 0;

	while (cmd != 10) {
		menu();
		cin >> cmd;
		system("cls");

		switch (cmd) {
		case 1: Users.add(); break;
		//case 2: list.print(); break;
		//case 3: list.remove(); break;
		//case 4: list.findByUser(); break;
		//case 5: list.findUsersByServer(); break;
		//case 6: list.freeServers(); break;
		//case 7: list.sortByID(); break;
		//case 8: list.save(); break;
		//case 9: list.load(); break;
		}
	}

	return 0;
}