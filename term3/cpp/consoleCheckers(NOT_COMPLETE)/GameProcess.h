#pragma once
#include <iostream>
#include "Board.h"

using namespace std;
class GameProcess
{
public:
    static void gameProcess(Board& board)
    {
        bool isWhiteTurn = true;
        int* startXY;
        int* endXY;
        while (true)
        {
            board.printBoard();

            if (isWhiteTurn) cout << "White player's turn" << endl;
            else cout << "Black player's turn" << endl;

            startXY = board.coordinatesInput();
            endXY = board.coordinatesInput();

            Figure* figure = board.getFigure(startXY);

            if (board.isValidStartCoordinates(startXY, isWhiteTurn)
                && board.isValidEndCoordinates(endXY, isWhiteTurn)
                && figure->canMove(board.squares, startXY, endXY))
            {
                board.setFigure(startXY, nullptr);
                if (dynamic_cast<Checker*>(figure) && (endXY[1] == 0 || endXY[1] == 7))
                    board.setFigure(endXY, new King(figure->getIsWhite()));
                else board.setFigure(endXY, new Checker(figure->getIsWhite()));

                isWhiteTurn = !isWhiteTurn;
            }
            else cout << "Invalid move. Try again" << endl;
        }
        delete[] startXY;
        delete[] endXY;
    }
};

