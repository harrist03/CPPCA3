#ifndef BOARD_H
#define BOARD_H

#include <vector>

using namespace std;

struct Cell
{
    int x, y;
};

class Board
{
private:
    // 2d vector {(0,0), (1,0),..}
    vector<std::vector<Cell>> cells;

public:
    // initializes the 10x10 grid
    Board() 
    {
        cells.resize(10);
        for (int y = 0; y < 10; y++) 
        {
            cells[y].resize(10);
            for (int x = 0; x < 10; x++) 
            {
                // e.g. cells[2][1] contains (1,2) coordinates 
                cells[y][x] = {x, y};  
            }
        }
    }
    Cell getCell(int x, int y) 
    {
        return cells[y][x];
    }
};

#endif // BOARD_H
