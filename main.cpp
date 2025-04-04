#include <iostream>
#include <vector>
#include "Crawler.h"
#include "Board.h"
#include <fstream>
#include <sstream>

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
    populateCrawlers(crawlers);

    Board bugBoard;
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

void tapBugBoard(vector<Crawler *> &crawlers)
{
    for (Crawler *crawler : crawlers)
    {
        crawler->move();
    }
    cout << "All crawlers moved!" << endl;
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
            cout << "Enter bug ID to be found: " << endl;
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
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            break;
        }
        case 8:

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