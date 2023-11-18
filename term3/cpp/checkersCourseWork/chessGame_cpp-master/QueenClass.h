#pragma once
#include "FigureClass.h"

class QueenClass: public FigureClass {

public:
    QueenClass(BoardPosition position, isWhite turn, Figure type, QString imagePath);

    bool canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition);
};
