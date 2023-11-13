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

    bool canMove(vector<vector<Figure*>>& board, int* startXY, int* endXY) override
    {
        // TODO: Implement checker's movement logic
        return true;
    }
};

class King : public Figure
{
public:
    King(bool isWhite) : Figure(isWhite) {}

    bool canMove(vector<vector<Figure*>>& board, int* startXY, int* endXY) override
    {
        // TODO: Implement king's movement logic
        return true;
    }
};