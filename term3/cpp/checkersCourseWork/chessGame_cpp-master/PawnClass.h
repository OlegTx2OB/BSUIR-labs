#pragma once
#include "FigureClass.h"

class PawnClass: public FigureClass {

public:
    PawnClass(BoardPosition position, isWhite turn, Figure type, QString imagePath);

    bool canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition);
};
