#pragma once
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QFont>
#include "SetParams.h"
#include "Consts.h"
#include "CreateView.h"

class ActionButton: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    ActionButton(QString title, int width, int height);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void buttonPressed();
};

