#include "BishopClass.h"

BishopClass::BishopClass(BoardPosition position, isWhite owner, Figure type, QString imagePath): FigureClass (position, owner, type, imagePath) {}

bool BishopClass::canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->turn == this->turn) {
        return false;
    }

    return validateDiagonalMove(positionToMove, pawnOnPositionToMove);
}
