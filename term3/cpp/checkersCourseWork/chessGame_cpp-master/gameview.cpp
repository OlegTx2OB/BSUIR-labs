#include "GameView.h"
#include <QGraphicsTextItem>
#include <QColor>
#include <QBrush>
#include "actionbutton.h"
#include "congratulationsview.h"
#include "constants.h"
#include "utils.h"

int viewWidth = 1200;
int viewHeight= 800;

GameView::GameView()
{

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(viewWidth, viewHeight);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, viewWidth, viewHeight);
    setScene(scene);

    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    QColor color = QColor(44, 41, 51);
    brush.setColor(color);
    scene->setBackgroundBrush(brush);

    gameStarted = false;
}


void GameView::displayMainMenu() {
    // create title label

    drawTitle();

    // create start button
    ActionButton *startButton = new ActionButton("Play");
    double buttonXPosition = this->width()/2 - startButton->boundingRect().width()/2;
    double buttonYPosition = 275;
    startButton->setPos(buttonXPosition, buttonYPosition);

    connect(startButton, SIGNAL(buttonPressed()), this, SLOT(startGame()));
    scene->addItem(startButton);

    // create quit button
    ActionButton *quitButton = new ActionButton("Quit");
    double quitXPosition = this->width()/2 - quitButton->boundingRect().width()/2;
    double quitYPosition = 350;
    quitButton->setPos(quitXPosition, quitYPosition);

    connect(quitButton, SIGNAL(buttonPressed()), this, SLOT(quitGame()));
    scene->addItem(quitButton);
}

void GameView::startGame()
{

    scene->clear();

    boardViewModel = BoardViewModel();

    drawBoard();
    drawGameControlButtons();
    drawUserPanel();
    drawTx2OBTitle();
    //gameStarted = true;
}

void GameView::quitGame() {
    close();
}

void GameView::resetGame() {
    gameStarted = false;
    scene->clear();
    startGame();
}

void GameView::drawBoard() {
    board = new BoardView();
    board->draw();
    board->initializeFiguresFields(boardViewModel.getBlackPawns());
    board->initializeFiguresFields(boardViewModel.getWhitePawns());
}

void GameView::drawGameControlButtons() {
    // create quit button
    ActionButton *resetButton = new ActionButton("Reset game");
    double resetXPosition = 580 + resetButton->boundingRect().width()/2;
    double resetYPosition = 420;
    resetButton->setPos(resetXPosition, resetYPosition);

    connect(resetButton, SIGNAL(buttonPressed()), this, SLOT(resetGame()));
    scene->addItem(resetButton);

    // create quit button
    ActionButton *quitButton = new ActionButton("Quit game");
    double quitXPosition = 580 + quitButton->boundingRect().width()/2;
    double quitYPosition = 490;
    quitButton->setPos(quitXPosition, quitYPosition);

    connect(quitButton, SIGNAL(buttonPressed()), this, SLOT(quitGame()));
    scene->addItem(quitButton);
}

void GameView::drawUserPanel()
{
    blackPlayerView = drawViewForUser(isWhite::black);
    whitePlayerView = drawViewForUser(isWhite::white);

    blackPlayerView->setActive(true);
}

PlayerView* GameView::drawViewForUser(isWhite player)
{
    PlayerView *playerView = new PlayerView();

    int xPosition = 80;
    int yPosition = BoardView::startYPosition;

    switch (player)
    {
    case isWhite::black:
        xPosition = 680;
        break;
    case isWhite::white:
        xPosition = 680 + PlayerView::defaultWidthHeight + 20;
        break;
    }

    scene->addItem(playerView);
    playerView->setRect(xPosition, yPosition, PlayerView::defaultWidthHeight, PlayerView::defaultWidthHeight);
    playerView->setPlayer(player);

    return playerView;
}

void GameView::drawTitle()
{
    int fontSize = 50;
    QGraphicsTextItem *title = Utils::createTextItem("Checkers Game", fontSize, Qt::white);
    double xPosition = this->width()/2 - title->boundingRect().width()/2;
    double yPosition = 100;
    title->setPos(xPosition, yPosition);
    scene->addItem(title);
}

void GameView::drawTx2OBTitle()
{
    int fontSize = 5;
    QGraphicsTextItem *title = Utils::createTextItem("created by Tx2OB (Oleg Poteychuk) for cpp course work", fontSize, Qt::white);
    double xPosition = this->width()/2 - title->boundingRect().width()/2;
    double yPosition = 0;
    title->setPos(xPosition, yPosition);
    scene->addItem(title);
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    if (!gameStarted) {
        QGraphicsView::mousePressEvent(event);
        return;
    }
    else if (event->button() == Qt::RightButton) releaseActivePawn();
    else if (boardViewModel.getActivePawn()) handleSelectingPointForActivePawnByMouse(event->pos());
    else
    {
        FigureField *pawn = board->getFigureAtMousePosition(event->pos());
        selectPawn(pawn);
    }

    QGraphicsView::mousePressEvent(event);
}

void GameView::mouseMoveEvent(QMouseEvent *event) {
    // if there is a pawn selected, then make it follow the mouse
    if (gameStarted && boardViewModel.getActivePawn())
        board->moveActiveFigureToMousePosition(event->pos(), boardViewModel.getActivePawn());

    QGraphicsView::mouseMoveEvent(event);
}


void GameView::selectPawn(FigureField *pawn)
{
    if (pawn == nullptr) return;

    boardViewModel.setActivePawnForField(pawn);
}

void GameView::handleSelectingPointForActivePawnByMouse(QPoint point)
{
    if (boardViewModel.getActivePawn() == nullptr) return;

    // check if mouse selected place on board
    if (!boardViewModel.validatePawnPalcementForMousePosition(point)) return;

    BoardPosition boardPosition = boardViewModel.getBoardPositionForMousePosition(point);

    // first validate Move
    if (!boardViewModel.validatePawnMove(boardPosition)) return;

    // Players cannot make any move that places their own king in check
    bool isKingInCheck = boardViewModel.isKingInCheck(boardViewModel.getActivePawn()->turn, true, boardPosition);
    board->setFigureMoveCheckWarning(isKingInCheck);
    if (isKingInCheck) return;


    // check if field was taken by opposite player and remove it from the board
    if (boardViewModel.didRemoveEnemyOnBoardPosition(boardPosition))
        board->removeFigureAtBoardPosition(boardPosition);


    // move active pawn to new position
    moveActivePawnToSelectedPoint(point);

    // check if pawn can be promoted
    if (boardViewModel.didPromoteActivePawn())
        board->promoteFigureAtBoardPosition(boardPosition);


    // check for opposite player king's check
    switch (boardViewModel.getActivePawn()->turn) {
    case isWhite::black:
        setCheckStateOnPlayerView(isWhite::white, boardViewModel.isKingInCheck(isWhite::white, false, boardPosition));
        break;
    case isWhite::white:
        setCheckStateOnPlayerView(isWhite::black, boardViewModel.isKingInCheck(isWhite::black, false, boardPosition));
        break;
    }

    // update active player check state
    setCheckStateOnPlayerView(boardViewModel.getActivePawn()->turn, isKingInCheck);

    // check if game is over
    if (boardViewModel.getWinner()) {
        showCongratulationsScreen(*boardViewModel.getWinner());
        return;
    }

    // change round owner to opposite player
    boardViewModel.discardActivePawn();
    boardViewModel.switchRound();
    blackPlayerView->setActive(boardViewModel.getWhosTurn() == isWhite::black);
    whitePlayerView->setActive(boardViewModel.getWhosTurn() == isWhite::white);
}

void GameView::setCheckStateOnPlayerView(isWhite player, bool isInCheck) {
    switch (player) {
    case isWhite::black:
        blackPlayerView->setIsInCheck(isInCheck);
        break;
    case isWhite::white:
        whitePlayerView->setIsInCheck(isInCheck);
        break;
    }
}

// update pawn field position and pawn model position
void GameView::moveActivePawnToSelectedPoint(QPoint point) {
    BoardPosition boardPosition = boardViewModel.getBoardPositionForMousePosition(point);
    board->placeActiveFigureAtBoardPosition(boardViewModel.getActivePawn(), boardPosition);
    boardViewModel.setNewPositionForActivePawn(boardPosition);
}

void GameView::releaseActivePawn()
{
    if (boardViewModel.getActivePawn() == nullptr) {
        return;
    }

    FigureClass *activePawn = boardViewModel.getActivePawn();
    board->placeActiveFigureAtBoardPosition(activePawn, activePawn->position);
    board->setFigureMoveCheckWarning(false);
    boardViewModel.discardActivePawn();
}

void GameView::showCongratulationsScreen(isWhite winner) {
    gameStarted = false;

    scene->clear();

    CongratulationsView *congratulationsView = new CongratulationsView(winner);
    congratulationsView->setRect(0, 0, viewWidth, viewHeight);
}
