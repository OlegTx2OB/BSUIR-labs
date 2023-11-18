#include "KnightClass.h"

KnightClass::KnightClass(BoardPosition position, isWhite owner, Figure type, QString imagePath): FigureClass (position, owner, type, imagePath) {}

bool KnightClass::canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->turn == this->turn) {
        return false;
    }

    int xDiference = abs(positionToMove.x - this->position.x);
    int yDiference = abs(positionToMove.y - this->position.y);

    if (xDiference == 2 && yDiference == 1) {
        return true;
    }

    if (xDiference == 1 && yDiference == 2) {
        return true;
    }

    return false;
}
