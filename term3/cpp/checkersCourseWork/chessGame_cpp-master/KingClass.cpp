#include "KingClass.h"

KingClass::KingClass(BoardPosition position, isWhite owner, Figure type, QString imagePath): FigureClass(position, owner, type, imagePath) {}

bool KingClass::canMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove, BoardPosition *requestedActivePawnPosition) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->turn == this->turn) {
        return false;
    }

    return pawnWantsToMoveByOneField(positionToMove);
}
