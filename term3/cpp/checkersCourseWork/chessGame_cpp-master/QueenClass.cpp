#include "QueenClass.h"

QueenClass::QueenClass(BoardPosition position, isWhite owner, Figure type, QString imagePath): FigureClass (position, owner, type, imagePath) {}

bool QueenClass::canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->turn == this->turn) {
        return false;
    }

    if (validateDiagonalMove(positionToMove, pawnOnPositionToMove)) {
        return true;
    }

    return validateVerticalOrHorizontalMove(positionToMove, pawnOnPositionToMove);
}
