#include "Board.h"
#include "Crawler.h"

Board::Board()
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

Cell Board::getCell(int x, int y) const
{
    return cells[y][x];
}

void Board::addCrawlersToBoard(const vector<Crawler*> &crawlers)
{
    for (Crawler* crawler : crawlers)
    {
        Position p = crawler->getPosition();
        string crawlerID = to_string(crawler->getBugID());
        
        cells[p.y][p.x].crawlerIDs.push_back(crawlerID);
    }
}
