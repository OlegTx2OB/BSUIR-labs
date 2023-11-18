#pragma once
#include <QGraphicsRectItem>
#include "FigureClass.h"

class CongratulationsView: public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    CongratulationsView(isWhite winner);
};
