#pragma once
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

class MainMenuScreen: public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene *scene = new QGraphicsScene();
    MainMenuScreen() {}
public slots:
    void playButtonPressed();
    void quitButtonPressed();


public:
    void displayMainMenu();
    void displayBackground();
    void displayStartQuitButtons();

    void displayCheckersTitle();
    void displayCreatorTitle();
};
