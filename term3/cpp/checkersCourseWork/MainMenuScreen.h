#pragma once
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "CreateView.h"
#include "Consts.h"
#include "ActionButton.h"
#include "GameScreen.h"

class MainMenuScreen: public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene* scene;
public:

    MainMenuScreen(QGraphicsScene* &scene) : scene(scene) {}

private slots:
    void playButtonPressed();
    void quitButtonPressed();

public:
    void displayMainMenuScreen();
private:
    void displayBackground();
    void displayStartQuitButtons();

    void displayCheckersTitle();
    void displayCreatorTitle();
};
