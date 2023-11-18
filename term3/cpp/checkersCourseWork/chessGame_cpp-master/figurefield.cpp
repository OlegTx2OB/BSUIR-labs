#include "figurefield.h"
#include <QGraphicsProxyWidget>
#include "boardfield.h"
#include "BoardPosition.h"
#include "GameView.h"
#include "utils.h"

extern GameView *game;

FigureField::FigureField(BoardPosition position,
                     QString imagePath,
                     QGraphicsItem *parent): QGraphicsRectItem(parent) {
    this->position = position;
    imageLabel = new QLabel();
    image = QPixmap(imagePath);
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(this);

    imageLabel->setPixmap(image);
    imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    pMyProxy->setWidget(imageLabel);

    setPen(Qt::NoPen);
}

void FigureField::setPosition(BoardPosition position) {
    this->position = position;
}

void FigureField::setImage(QString imagePath) {
    image.load(imagePath);
    imageLabel->clear();
    imageLabel->setPixmap(image);
}

BoardPosition FigureField::getPosition() {
    return position;
}
