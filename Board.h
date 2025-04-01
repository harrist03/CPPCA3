#ifndef BOARD_H
#define BOARD_H

#include <vector>

using namespace std;

struct Cell
{
    int row, col;
};

class Board
{
private:
    // 2d vector {(0,0), (1,0),..}
    vector<std::vector<Cell>> cells;
public:
    // initializes the 10x10 grid
    Board() {
        cells.resize(10);
        for (int row = 0; row < 10; row++) {
            cells[row].resize(10);
            for (int col = 0; col < 10; col++) {
                cells[row][col] = {row, col};
            }
        }
    }
    Cell getCell(int row, int col)
    {
        return cells[row][col];
    }
};

#endif // BOARD_H

