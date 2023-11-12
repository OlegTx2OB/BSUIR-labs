#include <iostream>
#include <vector>
#include "Board.h"
#include "GameProcess.h"

using namespace std;

int main()
{
    Board board;
    board.initializeFigures();
    GameProcess::gameProcess(board);

    return 0;
}