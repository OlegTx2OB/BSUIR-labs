#include <QApplication>
#include "MainMenuScreen.h"
#include "GameScreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    MainMenuScreen* mainMenu = new MainMenuScreen(scene);

    mainMenu->show();
    mainMenu->displayMainMenuScreen();
    return a.exec();
}
