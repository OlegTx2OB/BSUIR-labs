#include "MainWindow.h"

void MainWindow::displayMainMenuScreen()
{
    displayBackground();
    displayCheckersTitle();
    displayCreatorTitle();
    displayPlayQuitButtons();
}
void MainWindow::displayGameScreen()
{
    displayCreatorTitle();
    displayRestartQuitButtons();
}

void MainWindow::playButtonPressed()
{
    scene->clear();
    displayGameScreen();
}
void MainWindow::restartButtonPressed()
{
    close();

}
void MainWindow::quitButtonPressed()
{
    close();
}


void MainWindow::displayBackground()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(Consts::windowWidth, Consts::windowHeight);

    scene->setSceneRect(0, 0, Consts::windowWidth, Consts::windowHeight);
    setScene(scene);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(39, 62, 58));
    scene->setBackgroundBrush(brush);
}
void MainWindow::displayCheckersTitle()
{
    int fontSize = 66;
    QGraphicsTextItem *title = CreateView::textView("C H E C K E R S  G A M E", fontSize, QColor(234, 186, 102), nullptr);
    double xPosition = this->width()/2 - title->boundingRect().width()/2;
    double yPosition = Consts::windowHeight * 0.1;
    title->setPos(xPosition, yPosition);
    scene->addItem(title);
}
void MainWindow::displayCreatorTitle()
{
    int fontSize = 12;
    QGraphicsTextItem *title = CreateView::textView("c p p  c o u r s e  w o r k  c r e a t e d  b y  T x 2 O B  ( O l e g  P o t e y c h u k )", fontSize, QColor(234, 186, 102), nullptr);
    double xPosition = this->width()/2 - title->boundingRect().width()/2;
    double yPosition = Consts::windowHeight * 0.9;
    title->setPos(xPosition, yPosition);
    scene->addItem(title);
}

void MainWindow::displayPlayQuitButtons()
{
    ActionButton *playButton = new ActionButton("P\tL\tA\tY", 600, 120);
    double playXPosition = this->width()/2 - playButton->boundingRect().width()/2;
    double playYPosition = 500;
    playButton->setPos(playXPosition, playYPosition);
    connect(playButton, SIGNAL(buttonPressed()), this, SLOT(playButtonPressed()));
    scene->addItem(playButton);


    ActionButton *quitButton = new ActionButton("Q\tU\tI\tT", 600, 120);
    double quitXPosition = this->width()/2 - quitButton->boundingRect().width()/2;
    double quitYPosition = 650;
    quitButton->setPos(quitXPosition, quitYPosition);

    connect(quitButton, SIGNAL(buttonPressed()), this, SLOT(quitButtonPressed()));
    scene->addItem(quitButton);
}
void MainWindow::displayRestartQuitButtons()
{
    ActionButton *restartButton = new ActionButton("R E S T A R T", 330, 120);
    double restartXPosition = Consts::windowWidth * 0.61;
    double restartYPosition = Consts::windowHeight * 0.75;
    restartButton->setPos(restartXPosition, restartYPosition);
    connect(restartButton, SIGNAL(buttonPressed()), this, SLOT(restartButtonPressed()));
    scene->addItem(restartButton);


    ActionButton *quitButton = new ActionButton("Q U I T", 330, 120);
    double quitXPosition = Consts::windowWidth * 0.8;
    double quitYPosition = Consts::windowHeight * 0.75;
    quitButton->setPos(quitXPosition, quitYPosition);

    connect(quitButton, SIGNAL(buttonPressed()), this, SLOT(quitButtonPressed()));
    scene->addItem(quitButton);
}
