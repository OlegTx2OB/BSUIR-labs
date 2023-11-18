#pragma once
#include <QGraphicsRectItem>

class BoardFrameField: public QGraphicsRectItem
{
public:
    BoardFrameField(QGraphicsItem *parent = nullptr);

    void setTitle(QString title);
};
