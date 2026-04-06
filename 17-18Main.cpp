#define _CRT_SECURE_NO_WARNINGS
#include <iostream>	
#include <cstdlib>
#include <iomanip>
#include <cstring>

using namespace std;

//состояния
enum class State {
	FREE = 1,
	FULL,
	PARTIAL_FULL,
	RESERVED,
	PARTIAL_RESERVED,
	DISC_ERROR
};

//класс-сервер
class Server {
private:
	int id;
	int capacity;
	State state;
public:
	void input() {
		cout << "ID: ";
		cin >> id;

		cout << "Объем: ";
		cin >> capacity;

		cout << "Статус (1-6): ";
		int s;
		cin >> s;
		state = (State)s;
	}

	void print() const {
		cout << left
			<< setw(8) << id
			<< setw(10) << capacity
			<< setw(10) << (int)state;
	}

	int get_id() { return id; }
	int get_capacity() { return capacity; }
	State get_state() { return state; }

	void set(int i, int c, State s) {
		id = i;
		capacity = c;
		state = s;
	}
};

//класс-пользователь
class User {
private:
	int server_id;
	int user_id;
	char name[50];
public:
	void input() {
		cout << "ID сервера: ";
		cin >> server_id;

		cout << "ID пользователя: ";
		cin >> user_id;

		cout << "Имя: ";
		cin >> ws;
		cin.getline(name, 50);
	}

	void print() const {
		cout << left
			<< setw(20) << name
			<< setw(12) << user_id
			<< setw(10) << server_id;
	}

	int get_server_id() { return server_id; }
	int get_user_id() { return user_id; }
	const char* get_name() { return name; }

	void set(int sid, int uid, const char* n) {
		server_id = sid;
		user_id = uid;
		strcpy(name, n);
	}
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
	ServerList() { head = NULL; }

	Server* findByID(int id) {
		NodeServer* cur = head;

		while (cur) {
			if (cur->data.get_id() == id)
				return &cur->data;

			cur = cur->next;
		}

		return NULL;
	}

	//добавление
	void add() {
		NodeServer* n = new NodeServer;
		n->data.input();
		n->next = NULL;

		if (!head) head = n;
		else {
			NodeServer* cur = head;
			while (cur->next) cur = cur->next;
			cur->next = n;
		}
	}

	//вывод
	void print() {
		if (!head) {
			cout << "Список серверов пуст\n";
			return;
		}

		cout << "\n========== СЕРВЕРА ==========\n";
		cout << left
			<< setw(8) << "ID"
			<< setw(10) << "Объем"
			<< setw(10) << "Статус" << endl;
		cout << "-----------------------------\n";

		NodeServer* cur = head;
		while (cur) {
			cur->data.print();
			cout << endl;
			cur = cur->next;
		}
	}

	//удаление
	void del() {
		int id;
		cout << "ID сервера: ";
		cin >> id;

		NodeServer* cur = head;
		NodeServer* prev = NULL;

		while (cur) {
			if (cur->data.get_id() == id) {
				if (!prev) head = cur->next;
				else prev->next = cur->next;

				delete cur;
				cout << "Удалено\n";
				return;
			}
			prev = cur;
			cur = cur->next;
		}
		cout << "Не найдено\n";
	}

	//очистка
	void clear() {
		NodeServer* cur = head;

		while (cur != NULL) {
			NodeServer* t = cur;
			cur = cur->next;
			delete t;
		}

		head = NULL;
		cout << "Список серверов очищен\n";
	}

	//изменение
	void edit() {
		int id;
		cout << "ID сервера: ";
		cin >> id;

		NodeServer* cur = head;
		while (cur) {
			if (cur->data.get_id() == id) {
				cout << "Новые данные:\n";
				cur->data.input();
				return;
			}
			cur = cur->next;
		}
		cout << "Не найдено\n";
	}

	//сортировка
	void sort() {
		int mode;
		cout << "Сортировка серверов:\n";
		cout << "1 - по ID\n2 - по объему\n";
		cin >> mode;

		for (NodeServer* i = head; i; i = i->next)
			for (NodeServer* j = i->next; j; j = j->next) {

				bool cond = false;

				if (mode == 1)
					cond = i->data.get_id() > j->data.get_id();

				else if (mode == 2)
					cond = i->data.get_capacity() > j->data.get_capacity();

				if (cond) {
					Server t = i->data;
					i->data = j->data;
					j->data = t;
				}
			}
	}

	//сохранение
	void save() {
		FILE* f = fopen("servers.txt", "w");

		NodeServer* cur = head;
		while (cur) {
			fprintf(f, "%d;%d;%d\n",
				cur->data.get_id(),
				cur->data.get_capacity(),
				(int)cur->data.get_state());

			cur = cur->next;
		}

		fclose(f);
		cout << "Серверы сохранены\n";
	}

	//загрузка
	void load() {
		FILE* f = fopen("servers.txt", "r");
		if (!f) {
			cout << "Файл серверов не найден\n";
			return;
		}

		clear(); 

		int id, cap, st;

		while (fscanf(f, "%d;%d;%d\n", &id, &cap, &st) == 3) {
			NodeServer* n = new NodeServer;
			n->data.set(id, cap, (State)st);
			n->next = head;
			head = n;
		}

		fclose(f);
		cout << "Серверы загружены\n";
	}
};

//список пользователей
class UserList {
private:
	NodeUser* head;
public:
	UserList() { head = NULL; }

	//связь с серверами
	void print_with_servers(ServerList& Servers) {
		if (!head) {
			cout << "Список пользователей пуст\n";
			return;
		}

		cout << "\n====== ПОЛЬЗОВАТЕЛИ С СЕРВЕРАМИ ======\n";

		cout << left
			<< setw(20) << "Имя"
			<< setw(10) << "UserID"
			<< setw(10) << "ServID"
			<< setw(10) << "Объем"
			<< setw(10) << "Статус" << endl;

		cout << "------------------------------------------------------------\n";

		NodeUser* cur = head;

		while (cur) {
			Server* s = Servers.findByID(cur->data.get_server_id());

			cur->data.print();

			if (s) {
				cout << setw(10) << s->get_capacity()
					<< setw(10) << (int)s->get_state();
			}
			else {
				cout << setw(10) << "?"
					<< setw(10) << "нет";
			}

			cout << endl;
			cur = cur->next;
		}
	}

	//добавление
	void add(ServerList& Servers) {
		NodeUser* n = new NodeUser;
		n->data.input();

		if (Servers.findByID(n->data.get_server_id()) == NULL) {
			cout << "Такого сервера нет!\n";
			delete n;
			return;
		}

		n->next = NULL;

		if (!head) head = n;
		else {
			NodeUser* cur = head;
			while (cur->next) cur = cur->next;
			cur->next = n;
		}
	}

	//вывод
	void print() {
		if (!head) {
			cout << "Список пользователей пуст\n";
			return;
		}

		cout << "\n========== ПОЛЬЗОВАТЕЛИ ==========\n";
		cout << left
			<< setw(20) << "Имя"
			<< setw(12) << "UserID"
			<< setw(10) << "ServerID" << endl;
		cout << "------------------------------------------\n";

		NodeUser* cur = head;
		while (cur) {
			cur->data.print();
			cout << endl;
			cur = cur->next;
		}
	}

	//удаление
	void del() {
		int id;
		cout << "ID пользователя: ";
		cin >> id;

		NodeUser* cur = head;
		NodeUser* prev = NULL;

		while (cur) {
			if (cur->data.get_user_id() == id) {
				if (!prev) head = cur->next;
				else prev->next = cur->next;

				delete cur;
				cout << "Удалено\n";
				return;
			}
			prev = cur;
			cur = cur->next;
		}
		cout << "Не найдено\n";
	}

	//очистка
	void clear() {
		NodeUser* cur = head;

		while (cur != NULL) {
			NodeUser* t = cur;
			cur = cur->next;
			delete t;
		}

		head = NULL;
		cout << "Список пользователей очищен\n";
	}

	//изменение
	void edit() {
		int id;
		cout << "ID пользователя: ";
		cin >> id;

		NodeUser* cur = head;
		while (cur) {
			if (cur->data.get_user_id() == id) {
				cur->data.input();
				return;
			}
			cur = cur->next;
		}
	}

	//сортировка
	void sort() {
		int mode;
		cout << "Сортировка пользователей:\n";
		cout << "1 - по имени\n2 - по ID\n3 - по серверу\n";
		cin >> mode;

		for (NodeUser* i = head; i; i = i->next)
			for (NodeUser* j = i->next; j; j = j->next) {

				bool cond = false;

				if (mode == 1)
					cond = strcmp(i->data.get_name(), j->data.get_name()) > 0;

				else if (mode == 2)
					cond = i->data.get_user_id() > j->data.get_user_id();

				else if (mode == 3)
					cond = i->data.get_server_id() > j->data.get_server_id();

				if (cond) {
					User t = i->data;
					i->data = j->data;
					j->data = t;
				}
			}
	}

	//сохранение
	void save() {
		FILE* f = fopen("users.txt", "w");

		NodeUser* cur = head;
		while (cur) {
			fprintf(f, "%s;%d;%d\n",
				cur->data.get_name(),
				cur->data.get_user_id(),
				cur->data.get_server_id());

			cur = cur->next;
		}

		fclose(f);
		cout << "Пользователи сохранены\n";
	}

	//загрузка
	void load() {
		FILE* f = fopen("users.txt", "r");
		if (!f) {
			cout << "Файл пользователей не найден\n";
			return;
		}

		clear(); 

		char name[50];
		int uid, sid;

		while (fscanf(f, "%[^;];%d;%d\n", name, &uid, &sid) == 3) {
			NodeUser* n = new NodeUser;
			n->data.set(sid, uid, name);
			n->next = head;
			head = n;
		}

		fclose(f);
		cout << "Пользователи загружены\n";
	}
};

//меню
void print_menu() {
	cout << "\n------------- СЕРВЕРА -------------\n";
	cout << "1. Добавить\n2. Удалить\n3. Вывод\n4. Редактировать\n5. Сортировать\n";

	cout << "\n----------- ПОЛЬЗОВАТЕЛИ ----------\n";
	cout << "6. Добавить\n7. Удалить\n8. Вывод\n9. Редактировать\n10. Сортировать\n";

	cout << "\n11. Сохранить\n12. Загрузить\n13. Пользователи с серверами\n0. Выход\n";

	cout << "\n--------- ОЧИСТКА ---------\n";
	cout << "14. Очистить серверы\n15. Очистить пользователей\n";

	cout << "\n---------- ФАЙЛЫ ----------\n";
	cout << "16. Сохранить серверы\n17. Загрузить серверы\n18. Сохранить пользователей\n19. Загрузить пользователей\n";
}

int main() {
	system("chcp 1251>nul");

	ServerList Servers;
	UserList Users;

	int cmd = 0;

	while (cmd !=20) {
		print_menu();
		cin >> cmd;
		system("cls");

		switch (cmd) {
		case 1: Servers.add(); break;
		case 2: Servers.del(); break;
		case 3: Servers.print(); break;
		case 4: Servers.edit(); break;
		case 5: Servers.sort(); break;

		case 6: Users.add(Servers); break;
		case 7: Users.del(); break;
		case 8: Users.print(); break;
		case 9: Users.edit(); break;
		case 10: Users.sort(); break;

		case 11: Servers.save(); Users.save(); break;
		case 12: Servers.load(); Users.load(); break;
		case 13: Users.print_with_servers(Servers); break;

		case 14: Servers.clear(); break;
		case 15: Users.clear(); break;

		case 16: Servers.save(); break;
		case 17: Servers.load(); break;

		case 18: Users.save(); break;
		case 19: Users.load(); break;
		}

		system("pause");
		system("cls");
	}

	return 0;
}