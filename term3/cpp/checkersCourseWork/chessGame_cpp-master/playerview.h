#pragma once
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include "FigureClass.h"

class PlayerView: public QGraphicsRectItem
{
private:
    QGraphicsTextItem *checkTextItem;

public:
    PlayerView(QGraphicsItem *parent = nullptr);

    static int defaultWidthHeight;

    void setPlayer(isWhite owner);
    void setActive(bool active);
    void setIsInCheck(bool isCheck);
};
