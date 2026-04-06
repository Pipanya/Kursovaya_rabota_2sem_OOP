#if 0
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
	int get_id() { return id; }
	int get_capacity() { return capacity; }
	State get_state() { return state; }

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
		cin >> ws;
		cin.getline(name, 50);
	}
	void print() const {
		cout << "\nID сервера: " << server_id <<
			"\nID пользователя: " << user_id <<
			"\nИмя пользователя: " << name << endl;
	}
	int get_server_id() { return server_id; }
	int get_user_id() { return user_id; }
};

//узел-сервер
struct NodeServer {
	Server data;
	NodeServer* next;
};

//узел-пользователь
struct NodeUser {
	User data;
	NodeUser* next;
};

//список серверов
class ServerList {
private:
	NodeServer* head;
public:
	ServerList() {
		head = NULL;
	}
};

//список пользователей
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

	void print() {
		if (head == NULL) {
			cout << "Список пуст.\n";
			return;
		}

		NodeUser* current = head;

		while (current != NULL) {
			current->data.print();
			current = current->next;
		}
	}

	void del() {
		int pos;
		cout << "Выбериет эл-т для удаления: \n";
		cin >> pos;

		if (head == NULL) {
			cout << "Список пуст.\n";
			return;
		}

		NodeUser* current = head;
		while (current->data.get_server_id() != pos)
			current = current->next;

	}
};

//меню
void print_menu() {
	cout << "----------------------------------СЕРВЕРА------------------------------------\n";
	cout << ":: 1. Добавить сервер\n";
	cout << ":: 2. Удалить сервер\n";
	cout << ":: 3. Вывод серверов\n";
	cout << "--------------------------------ПОЛЬЗОВАТЕЛИ---------------------------------\n";
	cout << ":: 4. Добавить пользователя\n";
	cout << ":: 5. Удалить пользователя\n";
	cout << ":: 6. Вывод пользователей\n";
	cout << "---------------------------------------\n";
}

int main() {
	system("chcp 1251>nul");

	ServerList Servers;
	UserList Users;
	int cmd = 0;

	while (cmd != 10) {
		print_menu();
		cin >> cmd;
		system("cls");

		switch (cmd) {
		case 4:
			Users.add();
			system("pause");
			system("cls");
			break;
		case 5:
			Users.del();
			system("pause");
			system("cls");
			break;
		case 6:
			Users.print();
			system("pause");
			system("cls");
			break;
		}
	}

	return 0;
}
#endif