#include <iostream>
#include <memory>
#include "Menu.h"

using namespace std;

int main()
{
    Menu* menu = new Menu();
    menu->MainMenu();
    delete menu;
}

