#include "Bug.h"

#include <random>
#include <sstream>

Bug::Bug(unsigned int id, Position position, Direction direction, unsigned int size, bool alive, list<Position> path, int eatenByID)
    : id(id), position(position), direction(direction), size(size), alive(alive), path(path), eatenByID(eatenByID)
{
}

unsigned int Bug::getSize() const
{
    return size;
}

void Bug::setSize(unsigned int newSize)
{
    size = newSize;
}

bool Bug::isAlive() const
{
    return alive;
}

void Bug::setAlive(bool status)
{
    alive = status;
}

int Bug::getEatenByID() const
{
    return eatenByID;
}

void Bug::setEatenByID(int eaterID)
{
    eatenByID = eaterID;
}

string Bug::getBugDetails() const
{
    return "Bug ID: " + to_string(id) 
        + ", Position(x, y): (" + to_string(position.x) + ", " + to_string(position.y) + "), " 
        + "Size: " + to_string(size) 
        + ", Direction: " + getDirectionString() 
        + ", Status: " + (alive ? "Alive" : "Dead");
}

string Bug::getDirectionString() const
{
    switch (direction)
    {
    case Direction::North:
        return "North";
    case Direction::East:
        return "East";
    case Direction::South:
        return "South";
    case Direction::West:
        return "West";
    default:
        return "Unknown";
    }
}

unsigned int Bug::getBugID() const
{
    return id;
}

Position Bug::getPosition() const
{
    return position;
}

bool Bug::isWayBlocked(Position newP)
{
    return !(newP.x >= 0 && newP.x < 10 && newP.y >= 0 && newP.y < 10);
}

void Bug::fight(vector<Bug*>& bugsInCell)
{
    if (bugsInCell.size() < 2) return; // no fight happens if bugs < 2

    // sort bugs by size in descending order
    sort(bugsInCell.begin(), bugsInCell.end(),
        [](Bug* a, Bug* b) { return a->getSize() > b->getSize(); });

    // find the largest size
    unsigned int maxSize = bugsInCell[0]->getSize();
    vector<Bug*> biggestBugs;

    // find all bugs with the largest size
    for (Bug* bug : bugsInCell)
    {
        if (bug->getSize() == maxSize)
        {
            biggestBugs.push_back(bug);
        }
        else
        {
            break; // stop the loop when it reaches smaller bugs (works because the vector is sorted)
        }
    }

    // determine the winner
    Bug* winner;
    if (biggestBugs.size() > 1) // if multiple bugs have the max size, pick one randomly
    {
        srand(time(NULL));
        int randomIndex = rand() % biggestBugs.size();
        winner = biggestBugs[randomIndex];
    }
    else
    {
        winner = biggestBugs[0];
    }

    // display fight results
    cout << "Crawler " << winner->getBugID() << " wins the fight at ("
         << winner->getPosition().x << ", " << winner->getPosition().y << ")\n";

    // winner eats all other bugs
    for (Bug* bug : bugsInCell) {
        if (bug != winner && bug->isAlive()) {
            cout << "Crawler " << bug->getBugID() << " is eaten by Crawler " << winner->getBugID() << "\n\n";
            winner->setSize(winner->getSize() + bug->getSize()); // increase winner's size by loser's size
            bug->setAlive(false); // mark the eaten bug as dead
            bug->setEatenByID(winner->getBugID()); // record who ate the losing bug
        }
    }
}

string Bug::getLifeHistory() const
{
    stringstream history;
    history << id << " Crawler Path: ";

    if (path.empty())
    {
        history << "No movement recorded";
    }
    else
    {
        for (auto it = path.begin(); it != path.end(); ++it) {
            history << "(" << it->x << "," << it->y << ")";
            if (next(it) != path.end()) history << " -> ";
        }
    }

    if (isAlive())
    {
        history << " Alive";
    }
    else
    {
        history << " Eaten by " << to_string(getEatenByID());
    }
    return history.str();
}