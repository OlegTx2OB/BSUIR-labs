#include <iostream>
#include "Menu.h"
#include <memory>
#define MAX_ARRAY_SIZE 1000

int main()
{
    std::unique_ptr<Menu> menu = std::make_unique<Menu>();
    cin >> *menu;



    cout << "PEREGRUZKA OPERATOROV CHEEECK\n";

    std::unique_ptr<Cell> cell1(new Cell("user1", "lyosha", 10, nullptr, nullptr));
    std::unique_ptr<Cell> cell2(new Cell("user2", "pasha", 20, nullptr, nullptr));

    std::unique_ptr<Cell> cell3(new Cell((*cell1) + (*cell2)));
    std::cout << "Cell3 login: " << cell3->getLogin() << std::endl;
    std::cout << "Cell3 name: " << cell3->getName() << std::endl;
    std::cout << "Cell3 age: " << cell3->getAge() << std::endl << std::endl;

    std::unique_ptr<Cell> cell4(new Cell((*cell1) - (*cell2)));
    std::cout << "Cell4 login: " << cell4->getLogin() << std::endl;
    std::cout << "Cell4 name: " << cell4->getName() << std::endl;
    std::cout << "Cell4 age: " << cell4->getAge() << std::endl << std::endl;

    (*cell1) += (*cell2);
    std::cout << "Cell1 login: " << cell1->getLogin() << std::endl;
    std::cout << "Cell1 name: " << cell1->getName() << std::endl;
    std::cout << "Cell1 age: " << cell1->getAge() << std::endl;

}