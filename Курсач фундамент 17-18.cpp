#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

//статусы
enum Status {
    FREE,
    FULL,
    PARTIAL,
    RESERVED,
    PARTIAL_RESERVED,
    ERROR_DISK
};

//сервер
class Server {
private:
    int id;
    int capacity; // 1, 5, 10 ТБ
    Status status;

    char user[50];
    int userID;

public:
    Server() {
        id = 0;
        capacity = 0;
        status = FREE;
        user[0] = '\0';
        userID = 0;
    }

    void input() {
        cout << "ID сервера: ";
        cin >> id;

        cout << "Объем (1/5/10): ";
        cin >> capacity;

        cout << "Статус (0-FREE 1-FULL 2-PARTIAL 3-RESERVED 4-PARTIAL_RES 5-ERROR): ";
        int s;
        cin >> s;
        status = (Status)s;

        cout << "Имя пользователя: ";
        cin >> user;

        cout << "ID пользователя: ";
        cin >> userID;
    }

    void print() const {
        cout << "ID: " << id
            << " | " << capacity << "TB"
            << " | Status: " << status
            << " | User: " << user
            << " | UID: " << userID << endl;
    }

    int getID() const { return id; }
    int getCapacity() const { return capacity; }
    Status getStatus() const { return status; }
    const char* getUser() const { return user; }
    int getUserID() const { return userID; }

    void setStatus(Status s) { status = s; }
};

//узел списка
struct Node {
    Server data;
    Node* next;
};

//список
class List {
private:
    Node* head;

public:
    List() {
        head = NULL;
    }

    //добавление
    void add() {
        Node* temp = new Node;
        temp->data.input();
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
        }
        else {
            Node* p = head;
            while (p->next != NULL)
                p = p->next;
            p->next = temp;
        }
    }

    //вывод
    void print() const {
        Node* p = head;
        while (p != NULL) {
            p->data.print();
            p = p->next;
        }
    }

   //удаление
    void remove() {
        int id;
        cout << "Введите ID сервера: ";
        cin >> id;

        Node* p = head;
        Node* prev = NULL;

        while (p != NULL) {
            if (p->data.getID() == id) {
                if (prev == NULL)
                    head = p->next;
                else
                    prev->next = p->next;

                delete p;
                cout << "Удалено\n";
                return;
            }
            prev = p;
            p = p->next;
        }
        cout << "Не найдено\n";
    }

  
    //поиск по пользователю
    void findByUser() const {
        char name[50];
        cout << "Введите имя: ";
        cin >> name;

        Node* p = head;
        while (p != NULL) {
            if (strcmp(p->data.getUser(), name) == 0) {
                p->data.print();
            }
            p = p->next;
        }
    }

    //поиск по серверу
    void findUsersByServer() const {
        int id;
        cout << "ID сервера: ";
        cin >> id;

        Node* p = head;
        while (p != NULL) {
            if (p->data.getID() == id) {
                cout << p->data.getUser() << endl;
            }
            p = p->next;
        }
    }

    //свободные сервера
    void freeServers() const {
        Node* p = head;
        while (p != NULL) {
            if (p->data.getStatus() == FREE ||
                p->data.getStatus() == PARTIAL) {
                p->data.print();
            }
            p = p->next;
        }
    }

    //сортировка
    void sortByID() {
        for (Node* i = head; i != NULL; i = i->next) {
            for (Node* j = i->next; j != NULL; j = j->next) {
                if (i->data.getID() > j->data.getID()) {
                    Server tmp = i->data;
                    i->data = j->data;
                    j->data = tmp;
                }
            }
        }
    }

    //сохранение
    void save() {
        FILE* f = fopen("servers.txt", "w");

        Node* p = head;
        while (p != NULL) {
            fprintf(f, "%d;%d;%d;%s;%d\n",
                p->data.getID(),
                p->data.getCapacity(),
                p->data.getStatus(),
                p->data.getUser(),
                p->data.getUserID());

            p = p->next;
        }

        fclose(f);
        cout << "Сохранено\n";
    }

    //загрузка
    void load() {
        FILE* f = fopen("servers.txt", "r");

        if (!f) return;

        while (!feof(f)) {
            Node* temp = new Node;

            if (fscanf(f, "%d;%d;%d;%[^;];%d\n",
                &temp->data,
                &temp->data,
                &temp->data,
                temp->data,
                &temp->data) != 5) break;

            temp->next = head;
            head = temp;
        }

        fclose(f);
        cout << "Загружено\n";
    }
};

//меню
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

    List list;
    int cmd = 0;

    while (cmd != 10) {
        menu();
        cin >> cmd;
        system("cls");

        switch (cmd) {
        case 1: list.add(); break;
        case 2: list.print(); break;
        case 3: list.remove(); break;
        case 4: list.findByUser(); break;
        case 5: list.findUsersByServer(); break;
        case 6: list.freeServers(); break;
        case 7: list.sortByID(); break;
        case 8: list.save(); break;
        case 9: list.load(); break;
        }
    }
}
#endif