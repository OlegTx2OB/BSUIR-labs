#include "boardviewmodel.h"
#include "boardview.h"
#include "boardfield.h"
#include "KingClass.h"
#include "QueenClass.h"
#include "RookClass.h"
#include "BishopClass.h"
#include "KnightClass.h"
#include "PawnClass.h"
#include <math.h>

BoardViewModel::BoardViewModel() {
    activePawn = nullptr;
    whosTurn = isWhite::black;
    isEnPassantAvailable = false;
    pawnViewModel = PawnViewModel();
    winner = nullptr;

    initializePawns();
}

QList<FigureClass*> BoardViewModel::getBlackPawns() {
    return blackPawns;
}

QList<FigureClass*> BoardViewModel::getWhitePawns() {
    return whitePawns;
}

FigureClass* BoardViewModel::getActivePawn() {
    return activePawn;
}

isWhite BoardViewModel::getWhosTurn() {
    return whosTurn;
}

isWhite* BoardViewModel::getWinner() {
    return winner;
}

void BoardViewModel::setActivePawnForField(FigureField *pawn) {
    FigureClass* pawnModel = getPawnOnBoardPosition(pawn->getPosition());

    if (pawnModel && pawnModel->turn == whosTurn) {
        activePawn = pawnModel;
        pawn->setZValue(1);
    }
}

void BoardViewModel::setNewPositionForActivePawn(BoardPosition position) {
    activePawn->didTakeFirstMove = true;
    activePawn->position = position;
}

void BoardViewModel::discardActivePawn() {
    activePawn = nullptr;
}

FigureClass* BoardViewModel::getPawnOnBoardPosition(BoardPosition baordPosition) {
    for (int i = 0; i < blackPawns.length(); i++) {
        FigureClass *pawnModel = blackPawns[i];
        if (baordPosition.x == pawnModel->position.x &&
                baordPosition.y == pawnModel->position.y) {
            return pawnModel;
        }
    }

    for (int i = 0; i < whitePawns.length(); i++) {
        FigureClass *pawnModel = whitePawns[i];
        if (baordPosition.x == pawnModel->position.x &&
                baordPosition.y == pawnModel->position.y) {
            return pawnModel;
        }
    }

    return nullptr;
}

bool BoardViewModel::validatePawnPalcementForMousePosition(QPoint point) {
    if (point.x() > BoardView::startXPosition &&
            point.x() < (BoardView::startXPosition + BoardField::defaultWidthHeight*BoardView::numberOfRowsColumns) &&
            point.y() > BoardView::startYPosition &&
            point.y() < (BoardView::startYPosition + BoardField::defaultWidthHeight*BoardView::numberOfRowsColumns)) {
        return true;
    }
    return false;
}

bool BoardViewModel::validatePawnMove(BoardPosition positionToMove,
                                      FigureClass *pawn,
                                      BoardPosition *requestedActivePawnPosition) {
    FigureClass *pawnToValidate;
    if (pawn) {
        pawnToValidate = pawn;
    } else {
        pawnToValidate = activePawn;
    }

    FigureClass *pawnOnPositionToMove = getPawnOnBoardPosition(positionToMove);
    bool isMoveValid = pawnToValidate->canMove(positionToMove, pawnOnPositionToMove, requestedActivePawnPosition);

    switch (pawnToValidate->type) {
    case Figure::king:
    case Figure::queen:
    case Figure::rook:
    case Figure::bishop:
    case Figure::pawn:
        return isMoveValid && validateAnotherPawnIntersection(positionToMove, pawnToValidate, requestedActivePawnPosition);
    case Figure::knight:
        return isMoveValid;
    }
}

bool BoardViewModel::didRemoveEnemyOnBoardPosition(BoardPosition boardPosition) {
    FigureClass *pawn = getPawnOnBoardPosition(boardPosition);

    if (pawn && pawn->turn == whosTurn) {
        return false;
    }

    if (pawn) {
        switch (whosTurn) {
        case isWhite::black: {
            int index = whitePawns.indexOf(pawn);
            whitePawns.removeAt(index);
        }
            break;
        case isWhite::white: {
            int index = blackPawns.indexOf(pawn);
            blackPawns.removeAt(index);
        }
            break;
        }

        if (pawn->type == Figure::king) {
            winner = &whosTurn;
        }

        delete pawn;

        return true;
    }

    return false;
}

bool BoardViewModel::isKingInCheck(isWhite owner,
                                   bool isCheckingActivePlayer,
                                   BoardPosition positionToMoveActivePlayer) {
    FigureClass *king = nullptr;

    if (isCheckingActivePlayer && activePawn->type == Figure::king) {
        king = activePawn;
    } else {
        switch (owner) {
        case isWhite::black:
            for (int i = 0; i < blackPawns.length(); i++) {
                FigureClass *pawn = blackPawns[i];
                if (pawn->type == Figure::king) {
                    king = pawn;
                }
            }
            break;
        case isWhite::white:
            for (int i = 0; i < whitePawns.length(); i++) {
                FigureClass *pawn = whitePawns[i];
                if (pawn->type == Figure::king) {
                    king = pawn;
                }
            }
            break;
        }
    }

    if (king) {
        bool isInCheck = false;

        switch (owner) {
        case isWhite::black:
            isInCheck = validateKingsCheckForPawns(whitePawns, isCheckingActivePlayer, king, positionToMoveActivePlayer);
            break;
        case isWhite::white:
            isInCheck = validateKingsCheckForPawns(blackPawns, isCheckingActivePlayer, king, positionToMoveActivePlayer);
        }

        return isInCheck;
    }

    return false;
}

/*
    Promotion in chess is a rule that requires a pawn that reaches its eighth rank to be immediately
    replaced by the player's choice of a queen, knight, rook, or bishop of the same color.
    The new piece replaces the pawn, as part of the same move.
    The choice of new piece is not limited to pieces previously captured, thus promotion can result in a player owning,
    for example, two or more queens despite starting the game with one.
 */

bool BoardViewModel::didPromoteActivePawn() {
    if (!activePawn) {
        return false;
    }

    if (activePawn->type != Figure::pawn) {
        return false;
    }

    switch (activePawn->turn) {
    case isWhite::black:
        if (activePawn->position.y == 7) {
            activePawn->type = Figure::queen;
            return true;
        }
        break;
    case isWhite::white:
        if (activePawn->position.y == 0) {
            activePawn->type = Figure::queen;
            return true;
        }
        break;
    }

    return false;
}

void BoardViewModel::switchRound() {
    switch (whosTurn) {
    case isWhite::black:
        whosTurn = isWhite::white;
        break;
    case isWhite::white:
        whosTurn = isWhite::black;
        break;
    }
}

BoardPosition BoardViewModel::getBoardPositionForMousePosition(QPoint point) {
    int xPosition = static_cast<int>(floor((point.x() - BoardView::startXPosition)/BoardField::defaultWidthHeight));
    int yPosition = static_cast<int>(floor((point.y() - BoardView::startYPosition)/BoardField::defaultWidthHeight));

    return BoardPosition { xPosition, yPosition };
}

void BoardViewModel::initializePawns() {
    initializePawnsForRow(0, isWhite::black);
    initializePawnsForRow(1, isWhite::black);
    initializePawnsForRow(6, isWhite::white);
    initializePawnsForRow(7, isWhite::white);
}

void BoardViewModel::initializePawnsForRow(int rowNumber, isWhite owner) {
    for (int i = 0; i < BoardView::numberOfRowsColumns; i++) {
        BoardPosition boardPosition = { i, rowNumber };
        Figure type = pawnViewModel.getTypeForInitialPosition(boardPosition);
        QString imagePath = pawnViewModel.getImagePath(type, owner);
        FigureClass *pawn;

        switch (type) {
        case Figure::king:
            pawn = new KingClass(boardPosition, owner, type, imagePath);
            break;
        case Figure::queen:
            pawn = new QueenClass(boardPosition, owner, type, imagePath);
            break;
        case Figure::rook:
            pawn = new RookClass(boardPosition, owner, type, imagePath);
            break;
        case Figure::bishop:
            pawn = new BishopClass(boardPosition, owner, type, imagePath);
            break;
        case Figure::knight:
            pawn = new KnightClass(boardPosition, owner, type, imagePath);
            break;
        case Figure::pawn:
            pawn = new PawnClass(boardPosition, owner, type, imagePath);
            break;
        }

        switch (owner)
        {
        case isWhite::black:
            blackPawns.append(pawn);
            break;
        case isWhite::white:
            whitePawns.append(pawn);
            break;
        }
    }
}

bool BoardViewModel::validateAnotherPawnIntersection(BoardPosition positionToMove,
                                                     FigureClass *pawnToValidate,
                                                     BoardPosition *requestedActivePawnPosition) {
    int xDiference = positionToMove.x - pawnToValidate->position.x;
    int yDiference = positionToMove.y - pawnToValidate->position.y;
    int numbeOfFieldsToCheck = std::max(abs(xDiference), abs(yDiference));

    if (numbeOfFieldsToCheck == 1) {
        return true;
    }

    for (int i = 0; i < numbeOfFieldsToCheck; i++) {
        BoardPosition positionToCheck;

        if (xDiference < 0) {
            if (yDiference == 0) {
                positionToCheck = { pawnToValidate->position.x + (xDiference + i), pawnToValidate->position.y };
            } else if (yDiference < 0) {
                positionToCheck = { pawnToValidate->position.x + (xDiference + i), pawnToValidate->position.y + (yDiference + i) };
            } else {
                positionToCheck = { pawnToValidate->position.x + (xDiference + i), pawnToValidate->position.y + (yDiference - i) };
            }
        } else if (yDiference < 0) {
            if (xDiference == 0) {
                positionToCheck = { pawnToValidate->position.x, pawnToValidate->position.y + (yDiference + i) };
            } else {
                positionToCheck = { pawnToValidate->position.x + (xDiference - i), pawnToValidate->position.y + (yDiference + i) };
            }
        } else {
            if (xDiference == 0) {
                positionToCheck = { pawnToValidate->position.x, pawnToValidate->position.y + (yDiference - i) };
            } else if (yDiference == 0) {
                positionToCheck = { pawnToValidate->position.x + (xDiference - i), pawnToValidate->position.y };
            } else {
                positionToCheck = { pawnToValidate->position.x + (xDiference - i), pawnToValidate->position.y + (yDiference - i) };
            }
        }

        FigureClass *pawnToCheck = getPawnOnBoardPosition(positionToCheck);

        if (requestedActivePawnPosition &&
                positionToCheck.x != positionToMove.x &&
                positionToCheck.y != positionToMove.y &&
                positionToCheck.x == requestedActivePawnPosition->x &&
                positionToCheck.y == requestedActivePawnPosition->y) {
            return false;
        }

        // if we check for pawn that is on the position that the pawn wants to move by we need to check
        // if this position is not position that the pawm wants to move to
        if (pawnToCheck &&
                (pawnToCheck->position.x != positionToMove.x || pawnToCheck->position.y != positionToMove.y)) {
            return false;
        }
    }

    return true;
}

bool BoardViewModel::validateKingsCheckForPawns(QList<FigureClass*> pawns,
                                                bool isCheckingActivePlayer,
                                                FigureClass *king,
                                                BoardPosition positionToMoveActivePlayer) {
    bool isInCheck = false;

    // check every oppisite players pawn for kings check
    for (int i = 0; i < pawns.length(); i++) {
        FigureClass *pawn = pawns[i];
        // when checking for active player check we need to check first if the active player pawn is king,
        // if it's a king then check if position that wants to move the king to
        // is able to be taken in the next move by the opposite player
        if (isCheckingActivePlayer && activePawn->type == Figure::king) {
            if (validatePawnMove(positionToMoveActivePlayer, pawn, &positionToMoveActivePlayer)) {
                isInCheck = true;
            }
        } else if (isCheckingActivePlayer) {
            // if the active player pawn is not a king then check if active player wants to move to
            // the place of opposite player pawn that could capture active player king in the next move.
            // If he wants to move to other field then check if the field he wants to take will take active
            // player king from the check state

            if ((positionToMoveActivePlayer.x != pawn->position.x || positionToMoveActivePlayer.y != pawn->position.y) &&
                    validatePawnMove(king->position, pawn, &positionToMoveActivePlayer)) {
                isInCheck = true;
            }

        } else if (validatePawnMove(king->position, pawn)) {
            isInCheck = true;
        }
    }

    return isInCheck;
}
