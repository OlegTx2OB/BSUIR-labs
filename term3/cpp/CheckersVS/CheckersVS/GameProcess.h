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

        while (true)
        {
            board.printBoard();

            if (isWhiteTurn) cout << "White player's turn" << endl;
            else cout << "Black player's turn" << endl;

            int* startXY = board.coordinatesInput();
            int* endXY = board.coordinatesInput();//todo удалить всё delete[]

            Figure* figure = board.getFigure(startXY);

            if (board.isValidStartCoordinates(startXY, isWhiteTurn)
                && board.isValidEndCoordinates(startXY, endXY, isWhiteTurn)
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
    }
};

