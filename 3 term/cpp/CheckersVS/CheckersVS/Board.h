#pragma once
#include <iostream>
#include "Figure.h"

using namespace std;
class Board
{

public:
    vector<vector<Figure*>> squares;

    Board() { squares.resize(8, vector<Figure*>(8, nullptr)); }

    void initializeFigures()
    {
        for (int x = 0; x < 8; x++)
            for (int y = 0; y < 8; y++)
                if ((x + y) % 2 == 1)
                {
                    //black
                    if (y < 3)squares[x][y] = new Checker(false);
                    //white
                    else if (y > 4) squares[x][y] = new Checker(true);
                }
    }

    void printBoard() {
        cout << "_________________________________________________\n|";
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Figure* figure = squares[x][y];
                if (figure == nullptr)
                {
                    cout << "     |";
                }
                else if (dynamic_cast<Checker*>(figure))
                {
                    if (figure->getIsWhite()) cout << "  W  |";
                    else cout << "  B  |";
                }
                else if (dynamic_cast<King*>(figure))
                {
                    if (figure->getIsWhite()) cout << " WK  |";
                    else cout << " BK  |";
                }
            }
            cout << " " << y + 1;
            cout << "\n|_____|_____|_____|_____|_____|_____|_____|_____|\n|";
        }
        cout << "  A     B     C     D     E     F     G     H  |\n";
    }

    int* coordinatesInput()
    {
        string input;
        bool isInputValid = false;

        while (!isInputValid)
        {
            cout << "Enter from A1 to H8: ";
            cin >> input;
            if (input.length() == 2 &&
                (input[0] >= 'A' && input[0] <= 'H') &&
                (input[1] >= '1' && input[1] <= '8')) isInputValid = true;
            else cout << "Wrong input. Try again" << endl;
        }
        int* intInput = new int[2];
        intInput[0] = input[0] - 'A';
        intInput[1] = input[1] - '1';
        return intInput;
    }
    bool isValidStartCoordinates(int* startXY, bool isWhiteTurn)
    {
        return (getFigure(startXY) != nullptr
            && getFigure(startXY)->getIsWhite() == isWhiteTurn);
    }
    bool isValidEndCoordinates(int* startXY, int* endXY, bool isWhiteTurn)
    {
        return (getFigure(endXY) == nullptr
            && abs(endXY[0] - startXY[0]) == abs(endXY[1] - startXY[1]));
    }
    Figure* getFigure(int* xy) const { return squares[xy[0]][xy[1]]; }
    void setFigure(int* xy, Figure* figure) { squares[xy[0]][xy[1]] = figure; }
};