#include "Board.h"
#include "Bug.h"

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

void Board::addBugsToBoard(const vector<Bug*> &bugs)
{
    // Clear all existing bug IDs from the board
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            cells[y][x].bugIDs.clear(); // Reset all cells before updating
        }
    }

    // Add bugs to their latest positions
    for (Bug* bug : bugs)
    {
        Position p = bug->getPosition();
        string bugID = to_string(bug->getBugID());

        cells[p.y][p.x].bugIDs.push_back(bugID);
    }
}

void Board::displayAllCells()
{
    cout << "\nDisplaying cells by row x column (y,x)" << endl;
    cout << string(60, '-') << endl;
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            const vector<string>& bugsInCell = cells[y][x].bugIDs;
            cout << "(" << y << ", " << x << "): ";
            if (bugsInCell.empty())
            {
                cout << "empty" << endl;
            }
            else if (bugsInCell.size() > 0)
            {
                for (int i = 0; i < bugsInCell.size(); i++)
                {
                    if (i > 0)
                        cout << ", ";
                        cout << "Bug " <<  bugsInCell[i];
                }
                cout << endl;
            }
        }
        cout << endl;
    }
}
