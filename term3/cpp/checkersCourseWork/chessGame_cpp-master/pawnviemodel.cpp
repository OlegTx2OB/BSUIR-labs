#include "pawnviewmodel.h"

PawnViewModel::PawnViewModel() {}

QString PawnViewModel::getImagePath(Figure type, isWhite owner)
{
    QString imageFileName;

    switch (type) {
    case Figure::king:
        if (owner == isWhite::black) {
            imageFileName = "king_black.svg";
        } else {
            imageFileName = "king_white.svg";
        }
        break;
    case Figure::queen:
        if (owner == isWhite::black) {
            imageFileName = "queen_black.svg";
        } else {
            imageFileName = "queen_white.svg";
        }
        break;
    case Figure::rook:
        if (owner == isWhite::black) {
            imageFileName = "rook_black.svg";
        } else {
            imageFileName = "rook_white.svg";
        }
        break;
    case Figure::bishop:
        if (owner == isWhite::black) {
            imageFileName = "bishop_black.svg";
        } else {
            imageFileName = "bishop_white.svg";
        }
        break;
    case Figure::knight:
        if (owner == isWhite::black) {
            imageFileName = "knight_black.svg";
        } else {
            imageFileName = "knight_white.svg";
        }
        break;
    case Figure::pawn:
        if (owner == isWhite::black) {
            imageFileName = "pawn_black.svg";
        } else {
            imageFileName = "pawn_white.svg";
        }
        break;
    }

    return ":Images/" + imageFileName;
}

Figure PawnViewModel::getTypeForInitialPosition(BoardPosition position) {
    if (position.y == 1 || position.y == 6) {
        return Figure::pawn;
    }

    switch (position.x) {
    case 0:
    case 7:
        return Figure::rook;
    case 1:
    case 6:
        return Figure::knight;
    case 2:
    case 5:
        return Figure::bishop;
    case 3:
        return Figure::queen;
    case 4:
        return Figure::king;
    }

    return Figure::pawn;
}
