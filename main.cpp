#include <iostream>
#include <vector>
#include "Bug.h"
#include "Hopper.h"
#include "Crawler.h"
#include "Board.h"
#include <fstream>
#include <map>
#include <sstream>
#include <ctime>

Board bugBoard;

void parse(string line, int &id, int &x, int &y, int &direction, int &size, string &bugType, int &hopLength)
{
    string temp;
    stringstream ss(line);
    // parse bug type
    getline(ss, temp, ',');
    bugType = temp;
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
    // parse hop length (only for Hopper)
    if (bugType == "Hopper" && getline(ss, temp, ',')) {
        hopLength = stoi(temp);
    }
}

void populateBugs(vector<Bug*> &bugs)
{
    ifstream fin("../bugs.txt");

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
            int hopLength = 0;

            getline(fin, line);
            parse(line, id, x, y, direction, size, bugType, hopLength);
            Position p = {x, y}; // or p.x = x, p.y = y;

            Bug* newBug = nullptr;
            if (bugType == "Crawler") {
                newBug = new Crawler(id, p, static_cast<Direction>(direction), size, true, {p});
            } else if (bugType == "Hopper") {
                newBug = new Hopper(id, p, static_cast<Direction>(direction), size, hopLength, true, {p});
            }

            if (newBug) {
                bugs.push_back(newBug);
            }
        }
        cout << "Bugs loaded successfully!" << endl;
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

void initializeBugBoard(vector<Bug *> &bugs)
{
    // free each object's memory
    for (Bug* bug : bugs)
    {
        delete bug;
    }
    bugs.clear();
    populateBugs(bugs);
    bugBoard.addBugsToBoard(bugs);
}

void findBugByID(int searchID, const vector<Bug *> &bugs)
{
    bool found = false;
    for (Bug *bug : bugs)
    {
        if (searchID == bug->getBugID())
        {
            found = true;
            cout << bug->getBugDetails() << endl;
        }
    }
    if (!found)
    {
        cout << "Bug " << searchID << " not found." << endl;
    }
}

void displayAllBugs(const vector<Bug *> &bugs)
{
    if (bugs.empty())
    {
        cout << "No bugs to display." << endl;
        return;
    }

    for (const Bug *bug : bugs)
    {
        cout << bug->getBugDetails() << endl;
    }
}

void checkAndHandleFights(vector<Bug *>& bugs)
{
    // map to group bugs by their position
    map<pair<int, int>, vector<Bug*>> bugsByPosition;

    // group bugs (alive only) by their position
    for (Bug* bug : bugs)
    {
        if (bug->isAlive())
        {
            Position pos = bug->getPosition();
            bugsByPosition[{pos.x, pos.y}].push_back(bug);
        }
    }

    // check each cell for multiple bugs and make them fight
    for (auto& [position, cellBugs] : bugsByPosition)
    {
        if (cellBugs.size() > 1)
        {
            // if there are multiple bugs in a cell, make them fight
            cellBugs[0]->fight(cellBugs);
        }
    }
}

void tapBugBoard(vector<Bug *> &bugs)
{
    for (Bug *bug : bugs)
    {
        if (bug->isAlive()) // only move bugs that are alive
        {
            bug->move();
        }
    }

    // update the board with new bug positions
    bugBoard.addBugsToBoard(bugs);

    // check and handle fights in cells with multiple bugs
    checkAndHandleFights(bugs);

    cout << "All bugs moved!" << endl;
}

void displayLifeHistory(const vector<Bug *>& bugs) {
    if (bugs.empty()) {
        cout << "No bugs to display." << endl;
        return;
    }

    for (const Bug* bug : bugs) {
        cout << bug->getLifeHistory() << endl;
    }
}

void saveLifeHistoryToFile(const vector<Bug *>& bugs)
{
    if (bugs.empty()) {
        cout << "No bugs available." << endl;
        return;
    }

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
    for (const Bug* bug : bugs)
    {
        outFile << bug->getLifeHistory() << endl;
    }

    cout << "Life history saved to " << filename.str() << endl;
}

void runSimulation(vector<Bug*>& bugs)
{
    cout << "\nStarting simulation..." << endl;
    cout << "Tapping the board every 0.1 seconds" << endl;

    int tapCount = 0;
    bool simulationComplete = false;
    int aliveCount = 0;
    Bug* lastBugStanding = nullptr;

    while (!simulationComplete)
    {
        // https://stackoverflow.com/questions/50136540/calling-a-function-every-1-second-precisely
        clock_t startTime = clock();
        while (clock() - startTime < CLOCKS_PER_SEC / 10); // 1/10 of a second

        // tap the board and increment counter
        tapCount++;
        cout << "\nTap #" << tapCount << endl;
        cout << string(60, '-') << endl;
        // move all alive bugs
        for (Bug* bug : bugs)
        {
            if (bug->isAlive())
            {
                bug->move();
            }
        }

        // update the board with new bug positions
        bugBoard.addBugsToBoard(bugs);
        // trigger fights
        checkAndHandleFights(bugs);

        // count alive bugs and display positions
        aliveCount = 0;
        lastBugStanding = nullptr; // reset last bug standing each round
        cout << "Bug locations:" << endl;
        for (Bug* bug : bugs)
        {
            if (bug->isAlive())
            {
                Position pos = bug->getPosition();
                cout << "Bug " << bug->getBugID() << ": (" << pos.x << ", " << pos.y
                     << "), Size: " << bug->getSize() << endl;
                aliveCount++;
                lastBugStanding = bug;  // keep track of the last standing bug
            }
        }
        cout << "\nAlive bugs: " << aliveCount << "/" << bugs.size() << endl;

        // end simulation if only 1 bug remains alive
        if (aliveCount <= 1)
        {
            simulationComplete = true;
            cout << "Simulation complete! " << endl;
            if (lastBugStanding)
            {
                cout << "Last bug standing: Bug " << lastBugStanding->getBugID() << endl;
            }
        }

        // maximum tap count to prevent infinite loop
        if (tapCount >= 300)
        {
            simulationComplete = true;
            cout << "Simulation stopped after " << tapCount << " taps." << endl;
        }
    }

    // Display final state
    cout << "\nFinal state after " << tapCount << " taps:" << endl;
    displayAllBugs(bugs);

    // Save results to file
    saveLifeHistoryToFile(bugs);
}

void selectChoice(vector<Bug *> &bugs)
{
    int choice = 0;

    while (true)
    {
        srand(time(NULL));
        displayMenu();

        cout << "Enter your choice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            initializeBugBoard(bugs);
            break;
        }
        case 2:
        {
            displayAllBugs(bugs);
            break;
        }
        case 3:
        {
            int searchID;
            cout << "\nEnter bug ID to be found: ";
            cin >> searchID;
            findBugByID(searchID, bugs);
            break;
        }
        case 4:
        {
            tapBugBoard(bugs);
            break;
        }
        case 5:
        {
            displayLifeHistory(bugs);
            break;
        }
        case 6:
        {
            bugBoard.displayAllCells();
            break;
        }
        case 7:
        {
            if (bugs.empty())
            {
                cout << "Please initialize the bug board first (option 1)." << endl;
            }
            else
            {
                runSimulation(bugs);
            }
            break;
        }
        case 8:
            saveLifeHistoryToFile(bugs);
            cout << "Exiting..." << endl;
            return;
        default:
            cout << "Invalid choice selected. Please choose between 1 and 8." << endl;
        }
    }
}

int main()
{
    vector<Bug*> bug_vector;
    selectChoice(bug_vector);
}