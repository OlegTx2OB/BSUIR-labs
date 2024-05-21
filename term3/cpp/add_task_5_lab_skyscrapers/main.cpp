#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int BOARD_SIZE = 6;
struct Position
{
    int y, x;                    // current coordinates
    vector<vector<int>> posBoard;// current posBoard
    set<int> variants;           // variants for current cell

    Position(int y_, int x_, vector<vector<int>> posBoard_, set<int> variants_) :
            y(y_), x(x_), posBoard(posBoard_), variants(variants_) {};
};
void fillSquaresWhereHintIs1OrBOARD_SIZE(vector<vector<int>> &board, const vector<int> &clues);
void setPossibleVariantsBasedOnTips(vector<vector<set<int>>> &possible, const vector<int> &clues);
bool findMove(Position &pos, const vector<vector<set<int>>> &possible);
void makeMoveTry(Position& pos);
bool isMoveOK(Position pos, const std::vector<int> clues);

std::vector<vector<int>> SolvePuzzle(const vector<int> &clues)
{

    stack<Position> positionStack;
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    vector<vector<set<int>>> possibleVariantsBoard(BOARD_SIZE, vector<set<int>>(BOARD_SIZE, set<int>{}));

    // делать первоначальные предположения на основе подсказок
    fillSquaresWhereHintIs1OrBOARD_SIZE(board, clues);

    //найти только возможные варианты перемещения
    setPossibleVariantsBasedOnTips(possibleVariantsBoard, clues);

    // координаты стартовой позиции и возможные варианты старта
    Position pos(0, 0, board, {});

    // найдите первую ячейку и оставьте для нее только возможные варианты
    if (findMove(pos, possibleVariantsBoard)) positionStack.push(pos);
    // помещать варианты в стек и обрабатывать их методом DFS
    while (pos.y != BOARD_SIZE || pos.x != BOARD_SIZE)
    {
        // удалить шаги, у которых не осталось вариантов
        while (positionStack.top().variants.empty())
            positionStack.pop();
        // возьмите следующий вариант и вставьте его в доску
        makeMoveTry(positionStack.top());

        pos = positionStack.top();
        if (!isMoveOK(pos, clues)) continue;
        if (findMove(pos, possibleVariantsBoard))  positionStack.push(pos);
    }

    return pos.posBoard;
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// заполнить доску начальными догадками (когда подсказка равна 1 или BOARD_SIZE)
void fillSquaresWhereHintIs1OrBOARD_SIZE(vector<vector<int>>& board, const vector<int>& clues)
{
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        if (clues[i] == 1)
        { // если подсказка == 1, ближайшая ячейка должна быть равна BOARD_SIZE
            if ((i >= 0) && (i < BOARD_SIZE)) // верхняя сторона
                board[0][i] = BOARD_SIZE;
            if ((i > BOARD_SIZE-1) && (i < 2*BOARD_SIZE)) // правая сторона
                board[i - BOARD_SIZE][BOARD_SIZE-1] = BOARD_SIZE;
            if ((i > 2*BOARD_SIZE-1) && (i < 3*BOARD_SIZE)) // нижняя сторона
                board[BOARD_SIZE-1][BOARD_SIZE-1 - i % BOARD_SIZE] = BOARD_SIZE;
            if ((i > 3*BOARD_SIZE-1) && (i < 4*BOARD_SIZE)) // левая сторона
                board[BOARD_SIZE-1 - i % BOARD_SIZE][0] = BOARD_SIZE;
        }

        if (clues[i] == BOARD_SIZE)
        { // если подсказка == BOARD_SIZE, вся строка/столбец должны быть 1-2-3-4-..
            if ((i >= 0) && (i < BOARD_SIZE)) // верхняя сторона
                for (int j = 0; j < BOARD_SIZE; ++j)
                    board[j][i] = j+1;

            if ((i > BOARD_SIZE-1) && (i < 2*BOARD_SIZE)) // правая сторона
                for (int j = 0; j < BOARD_SIZE; ++j)
                    board[i - BOARD_SIZE][j] = BOARD_SIZE-j;

            if ((i > 2*BOARD_SIZE-1) && (i < 3*BOARD_SIZE)) // нижняя сторона
                for (int j = 0; j < BOARD_SIZE; ++j)
                    board[j][BOARD_SIZE-1 - i % BOARD_SIZE] = BOARD_SIZE-j;

            if ((i > 3*BOARD_SIZE-1) && (i < 4*BOARD_SIZE)) // левая сторона
                for (int j = 0; j < BOARD_SIZE; ++j)
                    board[BOARD_SIZE-1 - i % BOARD_SIZE][j] = j+1;
        }
    }
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void setPossibleVariantsBasedOnTips(vector<vector<set<int>>> &possible, const vector<int> &clues)
{
    for (int i = 0; i < BOARD_SIZE * 4; ++i)
    {
        int clue = clues[i];

        if (clue < 2 || clue == BOARD_SIZE) continue;
        // нет необходимости искать для clues[i] = 0, 1, BOARD_SIZE уже были заполнены в fillSquaresWhereHintIs1OrBOARD_SIZE

        // ТЕПЕРЬ создаем НЕЗМОЖНЫЕ ВАРИАНТЫ
        if ((i >= 0) && (i < BOARD_SIZE)) // верхняя сторона
        {
            for (int var = 2; var <= BOARD_SIZE; var++) // заполняем варианты от 1 до BOARD_SIZE
            {
                for (int y = 0; y < clue - 1 - BOARD_SIZE + var; y++)
                {  // проходим по столбцу
                    possible[y][i].insert(var);
                }
            }
        }
        if ((i > BOARD_SIZE-1) && (i < 2*BOARD_SIZE))
        {                   // правая сторона
            for (int var = 2; var <= BOARD_SIZE; var++)
            {                   // заполняем варианты от 1 до BOARD_SIZE
                for (int x = 1 + 2 * BOARD_SIZE - clue - var; x < BOARD_SIZE; x++)
                {  // проходим по строке <--
                    possible[i%BOARD_SIZE][x].insert(var);
                }
            }
        }
        if ((i > 2*BOARD_SIZE-1) && (i < 3*BOARD_SIZE))
        {                  // нижняя сторона
            for (int var = 2; var <= BOARD_SIZE; var++)
            {                    // заполняем варианты от 1 до BOARD_SIZE
                for (int y = 1 + 2 * BOARD_SIZE - clue-var; y < BOARD_SIZE; y++)
                {   // проходим по столбцу снизу вверх
                    possible[y][3*BOARD_SIZE - i - 1].insert(var);
                }
            }
        }
        if ((i > 3 * BOARD_SIZE - 1) && (i < 4 * BOARD_SIZE))
        {      // левая сторона
            for (int var = 2; var <= BOARD_SIZE; var++)
            {        // заполняем варианты от 1 до BOARD_SIZE
                for (int x = 0; x < clue - 1 - BOARD_SIZE + var; x++)
                {  // проходим по строке -->
                    possible[4*BOARD_SIZE - i - 1][x].insert(var);
                }
            }
        }
    }

    std::set<int> all;
    for (int i = 1; i <= BOARD_SIZE; i++) all.insert(i); // создаем все варианты

    // ТЕПЕРЬ создаем ТОЛЬКО ВОЗМОЖНЫЕ ВАРИАНТЫ
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            std::set<int> diff{};
            std::set_difference(begin(all),end(all),
                                begin(possible[y][x]),end(possible[y][x]),
                                std::inserter(diff,end(diff)));
            possible[y][x] = diff;
        }
    }
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

bool findMove(Position& pos, const vector<vector<set<int>>> &possible)
{
    bool flagExitSearch = false;
// поиск от текущего y и x первой ячейки без подсказки
// сначала ищем до конца текущей строки
    for (int xx = pos.x; xx < BOARD_SIZE; xx++)
    {
        if (pos.posBoard[pos.y][xx] == 0)
        {
            flagExitSearch = true;
            pos.x = xx;
            break;
        }
    }
// затем продолжаем поиск со следующей строки, если это не последняя
    if (!flagExitSearch && pos.y < BOARD_SIZE - 1)
    {
        pos.x = 0;
        ++pos.y;
        for (int yy = pos.y; yy < BOARD_SIZE; yy++)
        {
            for (int xx = 0; xx < BOARD_SIZE; xx++)
            {
                if (pos.posBoard[yy][xx] == 0)
                {
                    pos.y = yy;
                    pos.x = xx;
                    flagExitSearch = true;
                    break;
                }
            }
            if (flagExitSearch) break;
        }
    }

// если нет ячейки для перехода (все заполнены от 1 до BOARD_SIZE), возвращаем false и y = BOARD_SIZE; x = BOARD_SIZE, чтобы прекратить возврат
    if (!flagExitSearch)
    {
        pos.y = BOARD_SIZE;
        pos.x = BOARD_SIZE;
        return false;
    }
// берем возможные варианты для ячейки и оставляем только возможные подсказки для ячейки (если они были найдены на предыдущем этапе)
    pos.variants = possible[pos.y][pos.x];

    for (int yy = 0; yy < BOARD_SIZE; yy++)
    {
        if (pos.posBoard[yy][pos.x] != 0)
        { // удаляем posBoard[yy][x] из множества (вертикальное сканирование)
            auto it = pos.variants.find(pos.posBoard[yy][pos.x]);
            if (it != pos.variants.end()) pos.variants.erase(it);
        }
    }
    for (int xx = 0; xx < BOARD_SIZE; ++xx)
    {
        if (pos.posBoard[pos.y][xx] != 0)
        { // удаляем posBoard[y][xx] из множества (горизонтальное сканирование)
            auto it = pos.variants.find(pos.posBoard[pos.y][xx]);
            if (it != pos.variants.end()) pos.variants.erase(it);
        }
    }
    if (pos.variants.empty()) return false; // если нет вариантов (нам нужно вернуться назад)
    return true;
}

void makeMoveTry(Position& pos)
{
    pos.posBoard[pos.y][pos.x] = *pos.variants.begin(); // взять следующий вариант и вставьте следующий вариант в posBoard
    pos.variants.erase(pos.variants.begin());   // удалить использованный вариант
}


bool isMoveOK(Position pos, const std::vector<int> clues)
{
    // проверяет потенциальный ход по всем подсказкам
    int topClue = clues[pos.x];
    int bottomClue = clues[3*BOARD_SIZE - 1 - pos.x];
    int rightClue = clues[BOARD_SIZE + pos.y];
    int leftClue = clues[4*BOARD_SIZE - 1 - pos.y];


    // проверка сверху, подсказка может быть равна 0 (не нужно проверять)
    if (topClue != 0 && pos.posBoard[0][pos.x])
    {
        bool flagExit = false;
        int maxVal = pos.posBoard[0][pos.x];
        for(int yy = 1; yy < BOARD_SIZE; yy++)
        {
            if (pos.posBoard[yy][pos.x] == 0)
            {
                flagExit = true;
                break;
            }
            if (pos.posBoard[yy][pos.x] > maxVal)
            {
                maxVal = pos.posBoard[yy][pos.x];
                --topClue;
            }
        }
        if ((!flagExit && topClue != 1) || topClue < 1) return false; // предположение не подтверждено подсказкой
    }
    // проверка снизу, подсказка может быть равна 0
    if (bottomClue != 0 && pos.posBoard[BOARD_SIZE - 1][pos.x])
    {
        bool flagExit = false;
        int maxVal = pos.posBoard[BOARD_SIZE - 1][pos.x];
        for(int yy = BOARD_SIZE-2; yy >= 0 ; --yy)
        {
            if (pos.posBoard[yy][pos.x] == 0)
            {   flagExit = true;
                break;
            }
            if (pos.posBoard[yy][pos.x] > maxVal)
            {
                maxVal = pos.posBoard[yy][pos.x];
                --bottomClue;
            }
        }
        if ((!flagExit && bottomClue != 1) || bottomClue < 1) return false; // предположение не подтверждено подсказкой
    }
    // проверка справа, подсказка может быть равна 0
    if (rightClue != 0 && pos.posBoard[pos.y][BOARD_SIZE - 1])
    {
        bool flagExit = false;
        int maxVal = pos.posBoard[pos.y][BOARD_SIZE - 1];
        for(int xx = BOARD_SIZE-2; xx >= 0 ; --xx)
        {
            if (pos.posBoard[pos.y][xx] == 0)
            {
                flagExit = true;
                break;
            }
            if (pos.posBoard[pos.y][xx] > maxVal)
            {
                maxVal = pos.posBoard[pos.y][xx];
                --rightClue ;
            }
        }
        if ((!flagExit && rightClue != 1) || rightClue  < 1) return false; // предположение не подтверждено подсказкой
    }
    // проверка слева, подсказка может быть равна 0
    if (leftClue != 0 && pos.posBoard[pos.y][0])
    {
        bool flagExit = false;
        int maxVal = pos.posBoard[pos.y][0];
        for(int xx = 1; xx < BOARD_SIZE ; ++xx)
        {
            if (pos.posBoard[pos.y][xx] == 0)
            {
                flagExit = true;
                break;}
            if (pos.posBoard[pos.y][xx] > maxVal)
            {
                maxVal = pos.posBoard[pos.y][xx];
                --leftClue ;
            }
        }
        if ((!flagExit && leftClue != 1) || leftClue  < 1) return false; // предположение не подтверждено подсказкой
    }
    return true;
}
void solveOutput(std::vector<std::vector<int>> kataSolution)
{

    for(int n = 0; n < 6; n++)
    {
        for(int m = 0; m < 6; m++)
        {
            if(kataSolution[n][m] == 0)
            {
                std::cout << "NO ANSWER" << std::endl;
                return;
            }
            std::cout << kataSolution[n][m] << "  ";
        }
        std::cout << std::endl;
    }
}
int main()
{
    std::vector<int> clues =
        {
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0
        };


    std::vector<std::vector<int>> solvedPuzzle = SolvePuzzle(clues);

    solveOutput(solvedPuzzle);

    return 0;
}