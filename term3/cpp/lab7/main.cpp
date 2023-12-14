#include <iostream>
#include "MenuClass.h"

int main()
{
    MenuClass* menu = new MenuClass;
    menu->menu();
    delete menu;
    return 0;
}
