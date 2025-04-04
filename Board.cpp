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
    // Clear all existing crawler IDs from the board
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            cells[y][x].crawlerIDs.clear(); // Reset all cells before updating
        }
    }

    // Add crawlers to their latest positions
    for (Crawler* crawler : crawlers)
    {
        Position p = crawler->getPosition();
        string crawlerID = to_string(crawler->getBugID());

        cells[p.y][p.x].crawlerIDs.push_back(crawlerID);
    }
}

void Board::displayAllCells()
{

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            const vector<string>& crawlersInCell = cells[y][x].crawlerIDs;
            cout << "(" << x << ", " << y << "): ";
            if (crawlersInCell.empty())
            {
                cout << "empty" << endl;
            }
            else if (crawlersInCell.size() > 0)
            {
                for (int i = 0; i < crawlersInCell.size(); i++)
                {
                    if (i > 0)
                        cout << ", ";
                    cout << "Crawler " <<  crawlersInCell[i];
                }
                cout << endl;
            }
        }
        cout << endl;
    }
}
