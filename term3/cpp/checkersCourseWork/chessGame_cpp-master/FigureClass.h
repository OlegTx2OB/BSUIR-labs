#pragma once
#include <QString>
#include "BoardPosition.h"

enum class Figure
{
    king,
    queen,
    rook,
    bishop,
    knight,
    pawn
};

enum class isWhite
{
    black,
    white
};

class FigureClass
{
public:
    BoardPosition position;
    isWhite turn;
    Figure type;
    QString imagePath;
    bool didTakeFirstMove;

    FigureClass(BoardPosition position, isWhite turn, Figure type, QString imagePath);


    virtual bool canMove(BoardPosition positionToMove,
                              FigureClass *pawnOnPositionToMove,
                              BoardPosition *requestedActivePawnPosition) = 0;
    virtual ~FigureClass() = default;

protected:
    bool pawnWantsToMoveByOneField(BoardPosition positionToMove);
    bool validateDiagonalMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove);
    bool validateVerticalOrHorizontalMove(BoardPosition positionToMove, FigureClass *pawnOnPositionToMove);
};
