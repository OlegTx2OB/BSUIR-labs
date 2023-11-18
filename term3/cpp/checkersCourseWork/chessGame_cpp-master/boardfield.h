#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <BoardPosition.h>

class BoardField: public QGraphicsRectItem
{
private:
    BoardPosition position;
public:
    static int defaultWidthHeight;

    BoardField(QColor backgroundColor,
               BoardPosition position,
               QGraphicsItem *parent = nullptr);


    BoardPosition getPosition();
};
