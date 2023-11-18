#pragma once
#include <QString>
#include "FigureClass.h"

class PawnViewModel
{

public:

    PawnViewModel();

    QString getImagePath(Figure type, isWhite owner);
    Figure getTypeForInitialPosition(BoardPosition position);
};
