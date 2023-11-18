#pragma once
#include "FigureClass.h"

class KnightClass: public FigureClass
{

public:
    KnightClass(BoardPosition position, isWhite turn, Figure type, QString imagePath);

    bool canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition);
};
