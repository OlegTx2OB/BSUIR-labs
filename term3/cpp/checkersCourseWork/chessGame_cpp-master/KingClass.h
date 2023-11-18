#pragma once
#include "FigureClass.h"

class KingClass: public FigureClass {

public:
    KingClass(BoardPosition position, isWhite turn, Figure type, QString imagePath);

    bool canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition);
};
