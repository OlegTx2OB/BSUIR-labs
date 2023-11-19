#include "MainMenuScreen.h"


void MainMenuScreen::playButtonPressed()
{
    scene->clear();


}
void MainMenuScreen::quitButtonPressed()
{
    close();
}

void MainMenuScreen::displayMainMenuScreen()
{
    displayBackground();
    displayCheckersTitle();
    displayCreatorTitle();
    displayStartQuitButtons();
}
void MainMenuScreen::displayBackground()
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
void MainMenuScreen::displayCheckersTitle()
{
    int fontSize = 66;
    QGraphicsTextItem *title = CreateView::textView("C H E C K E R S  G A M E", fontSize, QColor(234, 186, 102), nullptr);
    double xPosition = this->width()/2 - title->boundingRect().width()/2;
    double yPosition = Consts::windowHeight * 0.1;
    title->setPos(xPosition, yPosition);
    scene->addItem(title);
}
void MainMenuScreen::displayCreatorTitle()
{
    int fontSize = 12;
    QGraphicsTextItem *title = CreateView::textView("c p p  c o u r s e  w o r k  c r e a t e d  b y  T x 2 O B  ( O l e g  P o t e y c h u k )", fontSize, QColor(234, 186, 102), nullptr);
    double xPosition = this->width()/2 - title->boundingRect().width()/2;
    double yPosition = Consts::windowHeight * 0.9;
    title->setPos(xPosition, yPosition);
    scene->addItem(title);
}

void MainMenuScreen::displayStartQuitButtons()
{
    ActionButton *startButton = new ActionButton("P\tL\tA\tY", 600, 120);
    double startXPosition = this->width()/2 - startButton->boundingRect().width()/2;
    double startYPosition = 500;
    startButton->setPos(startXPosition, startYPosition);
    connect(startButton, SIGNAL(buttonPressed()), this, SLOT(playButtonPressed()));
    scene->addItem(startButton);


    ActionButton *quitButton = new ActionButton("Q\tU\tI\tT", 600, 120);
    double quitXPosition = this->width()/2 - quitButton->boundingRect().width()/2;
    double quitYPosition = 650;
    quitButton->setPos(quitXPosition, quitYPosition);

    connect(quitButton, SIGNAL(buttonPressed()), this, SLOT(quitButtonPressed()));
    scene->addItem(quitButton);
}
