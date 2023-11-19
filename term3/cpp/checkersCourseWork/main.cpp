#include <QApplication>
#include "MainMenuScreen.h"

MainMenuScreen* mainMenu;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainMenu = new MainMenuScreen();
    mainMenu->show();
    mainMenu->displayMainMenu();
    return a.exec();
}
