#include <iostream>
#include "Menu.h"
#define MAX_ARRAY_SIZE 1000

int main()
{
    Menu *menu = new Menu();
    cin >> *menu;
    delete menu;



    cout << "PEREGRUZKA OPERATOROV CHEEECK\n";

    Cell* cell1 = new Cell("user1", "lyosha", 10, nullptr, nullptr);
    Cell* cell2 = new Cell("user2", "pasha", 20, nullptr, nullptr);

    Cell* cell3 = &(*cell1 + *cell2);
    cout << "Cell3 login: " << cell3->getLogin() << endl;
    cout << "Cell3 name: " << cell3->getName() << endl;
    cout << "Cell3 age: " << cell3->getAge() << endl << endl;

    Cell* cell4 = &(*cell1 - *cell2);
    cout << "Cell4 login: " << cell4->getLogin() << endl;
    cout << "Cell4 name: " << cell4->getName() << endl;
    cout << "Cell4 age: " << cell4->getAge() << endl << endl;

    *cell1 += *cell2;
    cout << "Cell1 login: " << cell1->getLogin() << endl;
    cout << "Cell1 name: " << cell1->getName() << endl;
    cout << "Cell1 age: " << cell1->getAge() << endl << endl;



}