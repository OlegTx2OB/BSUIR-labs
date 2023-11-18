#include "RookClass.h"

RookClass::RookClass(BoardPosition position, isWhite owner, Figure type, QString imagePath): FigureClass (position, owner, type, imagePath) {}

bool RookClass::canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->turn == this->turn) {
        return false;
    }

    return validateVerticalOrHorizontalMove(positionToMove, pawnOnPositionToMove);
}
