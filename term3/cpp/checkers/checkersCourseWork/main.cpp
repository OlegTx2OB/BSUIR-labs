#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    MainWindow* mainMenu = new MainWindow(scene);
    mainMenu->show();
    mainMenu->displayMainMenuScreen();

    return a.exec();
}
