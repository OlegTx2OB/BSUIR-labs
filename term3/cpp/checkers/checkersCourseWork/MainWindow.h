#pragma once
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "CreateView.h"
#include "Consts.h"
#include "ActionButton.h"



#include "display.h"


class MainWindow: public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene* scene;

public:
    MainWindow(QGraphicsScene* &scene) : scene(scene) {}

private slots:
    void playButtonPressed();
    void restartButtonPressed();
    void quitButtonPressed();

public:
    void displayMainMenuScreen();
    void displayGameScreen();

private:
    void displayBackground();
    void displayPlayQuitButtons();
    void displayRestartQuitButtons();

    void displayCheckersTitle();
    void displayCreatorTitle();
};
