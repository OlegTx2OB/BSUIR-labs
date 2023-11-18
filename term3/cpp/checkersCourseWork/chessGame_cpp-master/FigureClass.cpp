#include "FigureClass.h"

FigureClass::FigureClass(BoardPosition position, isWhite turn, Figure type, QString imagePath) {
    this->position = position;
    this->turn = turn;
    this->type = type;
    this->imagePath = imagePath;
    didTakeFirstMove = false;
}

bool FigureClass::pawnWantsToMoveByOneField(BoardPosition positionToMove) {
    int xDiference = positionToMove.x - this->position.x;
    int yDiference = positionToMove.y - this->position.y;
    int numbeOfFieldsToMove = std::max(abs(xDiference), abs(yDiference));

    return (numbeOfFieldsToMove == 1);
}

bool FigureClass::validateDiagonalMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->turn == this->turn) {
        return false;
    }

    int xDiference = positionToMove.x - this->position.x;
    int yDiference = positionToMove.y - this->position.y;

    if (abs(xDiference) != abs(yDiference)) {
        return false;
    }

    return true;
}

bool FigureClass::validateVerticalOrHorizontalMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove) {
    if (pawnOnPositionToMove && pawnOnPositionToMove->turn == this->turn) {
        return false;
    }

    if ((positionToMove.x != this->position.x && positionToMove.y != this->position.y)) {
        return false;
    }

    return true;
}
