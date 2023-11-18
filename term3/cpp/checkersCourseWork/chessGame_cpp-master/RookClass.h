#pragma once
#include "FigureClass.h"

class RookClass: public FigureClass {

public:
    RookClass(BoardPosition position, isWhite turn, Figure type, QString imagePath);

    bool canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition);
};
