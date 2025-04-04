#include <iostream>
#include <vector>
#include "Crawler.h"
#include "Board.h"
#include <fstream>
#include <map>
#include <sstream>
#include <ctime>

Board bugBoard;

void parse(string line, int &id, int &x, int &y, int &direction, int &size)
{
    string temp;
    stringstream ss(line);
    // parse id
    getline(ss, temp, ',');
    id = stoi(temp);
    // parse x coordinate
    getline(ss, temp, ',');
    x = stoi(temp);
    // parse y coordinate
    getline(ss, temp, ',');
    y = stoi(temp);
    // parse direction
    getline(ss, temp, ',');
    direction = stoi(temp);
    // parse size
    getline(ss, temp, ',');
    size = stoi(temp);
}

void populateCrawlers(vector<Crawler *> &crawlers)
{
    ifstream fin("../crawler-bugs.txt");

    if (fin)
    {
        string line;
        while (!fin.eof())
        {
            if (line.empty()) continue; // skip blank lines

            string bugType;
            int id;
            int x;
            int y;
            int direction;
            int size;

            getline(fin, line);
            parse(line, id, x, y, direction, size);
            Position p = {x, y}; // or p.x = x, p.y = y;
            Crawler *c1 = new Crawler(id, p, static_cast<Direction>(direction), size, true, {p});
            crawlers.push_back(c1);
        }
        cout << "Crawlers loaded successfully!" << endl;
    }
    else
    {
        cout << "Error reading from file" << endl;
    }
}

void displayMenu()
{
    cout << endl
         << string(60, '-') << endl;
    cout << "Menu" << endl;
    cout << string(60, '-') << endl;
    cout << "1. Initialize Bug Board (load data from file)" << endl;
    cout << "2. Display all Bugs" << endl;
    cout << "3. Find a Bug (given an id)" << endl;
    cout << "4. Tap the Bug Board (cause all to move, then fight/eat)" << endl;
    cout << "5. Display Life History of all Bugs (path taken)" << endl;
    cout << "6. Display all Cells listing their Bugs" << endl;
    cout << "7. Run simulation (generates a Tap every tenth of a second)" << endl;
    cout << "8. Exit (write Life History of all Bugs to file)" << endl;
    cout << string(60, '-') << endl;
}

void initializeBugBoard(vector<Crawler *> &crawlers)
{
    // free each object's memory
    for (Crawler* crawler : crawlers)
    {
        delete crawler;
    }
    crawlers.clear();
    populateCrawlers(crawlers);
    bugBoard.addCrawlersToBoard(crawlers);
}

void findBugByID(int searchID, const vector<Crawler *> &crawlers)
{
    bool found = false;
    for (Crawler *crawler : crawlers)
    {
        if (searchID == crawler->getBugID())
        {
            found = true;
            cout << crawler->getBugDetails();
        }
    }
    if (!found)
    {
        cout << "Bug " << searchID << " not found." << endl;
    }
}

void displayAllBugs(const vector<Crawler *> &crawlers)
{
    if (crawlers.empty())
    {
        cout << "No bugs to display." << endl;
        return;
    }

    for (const Crawler *crawler : crawlers)
    {
        cout << crawler->getBugDetails() << endl;
    }
}

void checkAndHandleFights(vector<Crawler*>& crawlers)
{
    // map to group crawlers by their position
    map<pair<int, int>, vector<Crawler*>> crawlersByPosition;

    // group crawlers (alive only) by their position
    for (Crawler* crawler : crawlers)
    {
        if (crawler->isAlive())
        {
            Position pos = crawler->getPosition();
            crawlersByPosition[{pos.x, pos.y}].push_back(crawler);
        }
    }

    // check each cell for multiple bugs and make them fight
    for (auto& [position, cellCrawlers] : crawlersByPosition)
    {
        if (cellCrawlers.size() > 1)
        {
            // if there are multiple bugs in a cell, make them fight
            cellCrawlers[0]->fight(cellCrawlers);
        }
    }
}

void tapBugBoard(vector<Crawler *> &crawlers)
{
    for (Crawler *crawler : crawlers)
    {
        if (crawler->isAlive()) // only move bugs that are alive
        {
            crawler->move();
        }
    }

    // update the board with new crawler positions
    bugBoard.addCrawlersToBoard(crawlers);

    // check and handle fights in cells with multiple bugs
    checkAndHandleFights(crawlers);

    cout << "All crawlers moved!" << endl;
}

void displayLifeHistory(const vector<Crawler *>& crawlers) {
    if (crawlers.empty()) {
        cout << "No bugs to display." << endl;
        return;
    }

    for (const Crawler* crawler : crawlers) {
        cout << crawler->getLifeHistory() << endl;
    }
}

void saveLifeHistoryToFile(const vector<Crawler*>& crawlers)
{
    // https://www.w3schools.com/cpp/trycpp.asp?filename=demo_date_strftime
    time_t timestamp = time(NULL);
    tm datetime = *localtime(&timestamp);

    char dateAndTime[50];
    strftime(dateAndTime, 50, "%Y-%m-%d_%H:%M:%S", &datetime);

    stringstream filename;
    filename << "../bugs_life_history_" << dateAndTime << ".txt";

    ofstream outFile(filename.str());
    if (!outFile)
    {
        cout << "Error: Could not create file!" << endl;
        return;
    }

    outFile << dateAndTime << endl;
    for (const Crawler* crawler : crawlers)
    {
        outFile << crawler->getLifeHistory() << endl;
    }

    cout << "Life history saved to " << filename.str() << endl;
}

void selectChoice(vector<Crawler *> &crawlers)
{
    int choice = 0;

    while (true)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            initializeBugBoard(crawlers);
            break;
        }
        case 2:
        {
            displayAllBugs(crawlers);
            break;
        }
        case 3:
        {
            int searchID;
            cout << "Enter bug ID to be found: ";
            cin >> searchID;
            findBugByID(searchID, crawlers);
            break;
        }
        case 4:
        {
            tapBugBoard(crawlers);
            break;
        }
        case 5:
        {
            displayLifeHistory(crawlers);
            break;
        }
        case 6:
        {
            bugBoard.displayAllCells();
            break;
        }
        case 7:
        {
            break;
        }
        case 8:
            saveLifeHistoryToFile(crawlers);
            cout << "Exiting..." << endl;
            return;
        default:
            cout << "Invalid choice selected." << endl;
        }
    }
}

int main()
{
    vector<Crawler *> crawlers;
    selectChoice(crawlers);
}