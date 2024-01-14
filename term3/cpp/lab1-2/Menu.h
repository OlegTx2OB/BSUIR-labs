#pragma once
#include <iostream>
#include "HashTable.h"
#include "Cell.h"
#define MAX_ARRAY_SIZE 1000

using namespace std;

class Menu
{
public:
    Menu() {}

    void mainMenu()
    {
        HashTable hashTableArray[MAX_ARRAY_SIZE];
        for (int i = 0; i < MAX_ARRAY_SIZE; i++) hashTableArray[i] = HashTable(nullptr, nullptr);
        while (true)
        {
            cout << "\t\t\tMAIN MENU\n1.Log in  2.Register new account  3.Delete account  4.Quit: ";
            int choose = getInt(1, 4);
            if (choose == 1) logIn(hashTableArray);
            else if (choose == 2) registerNewAccount(hashTableArray);
            else if (choose == 3) deleteAccount(hashTableArray);
            else break;
        }
    }
    void userMenu(std::shared_ptr<Cell> newCell)
    {
        while (true)
        {
            cout << *newCell;

            int choose = getInt(1, 5);

            if (choose == 1)newCell->setLogin(Cell::changeLogin());

            else if (choose == 2)newCell->setName(Cell::changeName());
            else if (choose == 3)newCell->setAge(getInt(0, 100));
            else if (choose == 4)cout << "First letter of name is: " << (*newCell)[0];
            else break;
        }
        cout << endl;
    }

    friend istream &operator>>(istream &input, Menu &menu);
    void *operator new(size_t size);
    void operator delete(void *ptr);
    static HashTable* createHashTable();
    void logIn(HashTable* hashTableArray);
    void registerNewAccount(HashTable* hashTableArray);
    void deleteAccount(HashTable* hashTableArray);

    int getInt(int lowerBound, int upperBound);
    char* getLoginOrPassword();
    char* undefinedName();
};