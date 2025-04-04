#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Crawler.h"

using namespace std;

struct Cell
{
    int x, y;
    vector<string> crawlerIDs;
};

class Board
{
private:
    // 2d vector {(0,0), (1,0),..}
    vector<std::vector<Cell>> cells;

public:
    Board();
    Cell getCell(int x, int y) const;
    void addCrawlersToBoard(const vector<Crawler*> &crawlers);
    void displayAllCells();
};

#endif // BOARD_H
