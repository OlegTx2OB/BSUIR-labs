#pragma once
#include <QAbstractGraphicsShapeItem>
#include <QColor>
#include <QBrush>
#include <QLabel>
#include <QGraphicsProxyWidget>

class SetParams
{
public:
    static void setBackgroundColor(QColor color, QAbstractGraphicsShapeItem *item);
    static void setImage(QString imagePath, QGraphicsRectItem *item);
};
