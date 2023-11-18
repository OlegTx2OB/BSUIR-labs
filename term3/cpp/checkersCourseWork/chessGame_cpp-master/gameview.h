#pragma once
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "boardview.h"
#include "boardviewmodel.h"
#include "figurefield.h"
#include "playerview.h"

class GameView : public QGraphicsView
{
    Q_OBJECT

private:
    BoardViewModel boardViewModel;
    bool gameStarted;
    BoardView *board;
    PlayerView *blackPlayerView;
    PlayerView *whitePlayerView;
public:
    GameView();

    QGraphicsScene *scene;

    void displayMainMenu();

public slots:
    void startGame();
    void quitGame();
    void resetGame();

    void drawBoard();
    void drawGameControlButtons();
    void drawUserPanel();
    PlayerView* drawViewForUser(isWhite player);
    void drawTitle();
    void drawTx2OBTitle();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void selectPawn(FigureField *pawn);
    void handleSelectingPointForActivePawnByMouse(QPoint point);
    void setCheckStateOnPlayerView(isWhite player, bool isInCheck);
    void moveActivePawnToSelectedPoint(QPoint point);
    void releaseActivePawn();
    void showCongratulationsScreen(isWhite winner);
};
