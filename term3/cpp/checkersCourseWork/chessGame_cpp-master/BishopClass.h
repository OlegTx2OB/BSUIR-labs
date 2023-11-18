#pragma once
#include "FigureClass.h"

class BishopClass: public FigureClass
{
public:
    BishopClass(BoardPosition position, isWhite turn, Figure type, QString imagePath);

    bool canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition);
};
