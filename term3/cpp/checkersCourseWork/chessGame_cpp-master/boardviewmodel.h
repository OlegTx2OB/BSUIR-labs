#pragma once
#include <QPoint>
#include "BoardPosition.h"
#include "figurefield.h"
#include "FigureClass.h"
#include "pawnviewmodel.h"

class BoardViewModel {

public:
    BoardViewModel();

    bool isEnPassantAvailable;

    QList<FigureClass*> getBlackPawns();
    QList<FigureClass*> getWhitePawns();
    FigureClass* getActivePawn();
    isWhite getWhosTurn();
    isWhite* getWinner();
    void setActivePawnForField(FigureField *pawn);
    void setNewPositionForActivePawn(BoardPosition position);
    void discardActivePawn();
    BoardPosition getBoardPositionForMousePosition(QPoint position);
    bool validatePawnPalcementForMousePosition(QPoint position);
    bool validatePawnMove(BoardPosition positionToMove, FigureClass *pawnToValidate = nullptr, BoardPosition *requestedActivePawnPosition = nullptr);
    bool didRemoveEnemyOnBoardPosition(BoardPosition boardPosition);
    bool isKingInCheck(isWhite owner, bool isCheckingActivePlayer, BoardPosition positionToMoveActivePlayer);
    bool didPromoteActivePawn();
    void switchRound();

private:
    FigureClass *activePawn;
    isWhite whosTurn;
    QList<FigureClass*> blackPawns;
    QList<FigureClass*> whitePawns;
    PawnViewModel pawnViewModel;
    isWhite *winner;

    void initializePawns();
    void initializePawnsForRow(int rowNumber, isWhite owner);
    FigureClass* getPawnOnBoardPosition(BoardPosition baordPosition);
    bool validateAnotherPawnIntersection(BoardPosition positionToMove, FigureClass *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);
    bool validateKingsCheckForPawns(QList<FigureClass*> pawns, bool isCheckingActivePlayer, FigureClass *king, BoardPosition positionToMoveActivePlayer);
};
