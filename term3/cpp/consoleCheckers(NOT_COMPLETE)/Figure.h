#pragma once
#include <iostream>
#include <vector>

using namespace std;
class Figure
{
private:
    bool isWhite;

public:
    Figure(bool isWhite) : isWhite(isWhite) {}

    virtual bool canMove(vector<vector<Figure*>>& board, int* startXY, int* endXY) = 0;

    bool getIsWhite() const { return isWhite; }
    void setIsWhite(bool isWhite) { this->isWhite = isWhite; }
};

class Checker : public Figure
{
public:
    Checker(bool isWhite) : Figure(isWhite) {}

    bool canMove(vector<vector<Figure*>>& board, int* sXY, int* eXY) override
    {
        Checker checker = board[sXY[0]][sXY[1]];
        if(abs(eXY[0] - sXY[0]) == abs(eXY[1] - sXY[1]))
        {
            if(checker.getIsWhite())
            {
                if(eXY[1] - sXY[1] == -1) return true;
                else if(eXY[1] - sXY[1] == -2
                && board[(eXY[0] + sXY[0]) / 2][eXY[1] + 1] != nullptr
                && !board[(eXY[0] + sXY[0]) / 2][eXY[1] + 1]->getIsWhite()) return true;
            }
            else
            {
                if(eXY[1] - sXY[1] == 1) return true;
                else if(eXY[1] - sXY[1] == 2
                        && board[(eXY[0] + sXY[0]) / 2][eXY[1] + 1] != nullptr
                        && board[(eXY[0] + sXY[0]) / 2][eXY[1] + 1]->getIsWhite()) return true;
            }
        }
        return false;
    }
};

class King : public Figure
{
public:
    King(bool isWhite) : Figure(isWhite) {}

    bool canMove(vector<vector<Figure*>>& board, int* sXY, int* eXY) override
    {
      if(abs(eXY[0] - sXY[0]) == abs(eXY[1] - sXY[1]))
      {
          
      }
      return false;
    }
};