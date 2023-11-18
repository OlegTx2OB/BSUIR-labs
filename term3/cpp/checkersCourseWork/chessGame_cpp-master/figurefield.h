#pragma once
#include <QGraphicsRectItem>
#include <QLabel>
#include "BoardPosition.h"
#include "FigureClass.h"

class FigureField: public QGraphicsRectItem
{
private:
    BoardPosition position;
    QLabel *imageLabel;
    QPixmap image;
public:
    FigureField(BoardPosition position,
              QString imagePath,
              QGraphicsItem *parent = nullptr);

    BoardPosition getPosition();
    void setPosition(BoardPosition position);
    void setImage(QString imagePath);
};
