#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationDisplayName("cpp Course Work Tx2OB");
    QGraphicsScene *scene = new QGraphicsScene();
    MainWindow* mainWindow = new MainWindow(scene);
    mainWindow->show();
    mainWindow->displayMainMenuScreen();

    return a.exec();
}
