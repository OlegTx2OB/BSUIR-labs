#pragma once
#include <iostream>
#include <cstring>
#include <memory>

using namespace std;

class Cell
{
private:
    char* login;
    char* name;
    int age;

    std::shared_ptr<Cell> prev;
    std::shared_ptr<Cell> next;

public:
    Cell(char* login, char* name, int age, std::shared_ptr<Cell> prev, std::shared_ptr<Cell> next) : login(login), name(name), age(age), prev(prev), next(next) {}
    Cell() {}

    static char* changeLogin();
    static char* changeName();

    friend ostream &operator<<(ostream &output, Cell &newCell)
    {
        output << "\n\t\t\tPERSON MENU\nlogin:" << newCell.getLogin()
                                         << " name:" << newCell.getName() << " age:" << newCell.getAge() << endl <<
                                         "--------------------------------------------------------------------\n" <<
                                        "1.Change login  2.Change name  3.change age 4.First letter of name 5.Log out: ";
        return output;
    }

    Cell& operator+(const Cell& other)
    {
        char* newLogin = new char[strlen(login) + strlen(other.login) + 1];
        strcpy(newLogin, login);
        strcat(newLogin, other.login);

        char* newName = new char[strlen(name) + strlen(other.name) + 1];
        strcpy(newName, name);
        strcat(newName, other.name);

        Cell* newCell = new Cell(newLogin, newName, age+other.age, nullptr, nullptr);
        return *newCell;
    }

    Cell& operator-(const Cell& other)
    {
        char* newLogin = "Cell4Login";
        char* newName = "Cell4Name";
        Cell* newCell = new Cell(newLogin, newName, age-other.age, nullptr, nullptr);
        return *newCell;
    }

    Cell& operator+=(const Cell& other)
    {
        login = "fsdfggfdg";
        name = "gdsfds";
        age = age + other.age;
        return *this;
    }

    void operator delete(void* ptr)
    {
        cout << "User has been deleted\n";
        free(ptr);
    }
    char& operator[](int index)
    {
        return name[index];
    }
    bool operator ==(char* _login);

    char* getLogin() { return login; }
    char* getName() { return name; }
    int getAge() { return age; }
    std::shared_ptr<Cell> getPrev() { return prev; }
    std::shared_ptr<Cell> getNext() { return next; }

    void setLogin(char* login) { this->login = login; }
    void setName(char* name) { this->name = name; }
    void setAge(int age) { this->age = age; }
    void setPrev(std::shared_ptr<Cell> prev) { this->prev = prev; }
    void setNext(std::shared_ptr<Cell> next) { this->next = next; }
};