#include "Crawler.h"
#include <sstream>

// allows non default values for Crawler
Crawler::Crawler(unsigned int id, Position position, Direction direction, unsigned int size, bool alive, list<Position> path)
    : id(id), position(position), direction(direction), size(size), alive(alive), path(path)
{
}

string Crawler::getBugDetails() const
{
    return "Bug ID: " + to_string(id) 
        + ", Position(x, y): (" + to_string(position.x) + ", " + to_string(position.y) + "), " 
        + "Size: " + to_string(size) 
        + ", Direction: " + getDirectionString() 
        + ", Status: " + (alive ? "Alive" : "Dead");
}

string Crawler::getDirectionString() const
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

unsigned int Crawler::getBugID() const
{
    return id;
}

Position Crawler::getPosition() const
{
    return position;
}

bool Crawler::isWayBlocked(Position newP)
{
    return !(newP.x >= 0 || newP.x < 10 || newP.y >= 0 || newP.y < 10);
}

void Crawler::move()
{
    bool moved = false;
    while (!moved)
    {
        Position newP = position;
        switch (direction)
        {
        case Direction::North:
            newP.y -= 1;
            break;
        case Direction::East:
            newP.x += 1;
            break;
        case Direction::South:
            newP.y += 1;
            break;
        case Direction::West:
            newP.x -= 1;
            break;
        default:
            break;
        }

        if (isWayBlocked(newP))
        {
            srand(time(0));
            // generate between 1 and 4
            int newDirection = 1 + rand() % 4;
            // new direction for crawler
            direction = static_cast<Direction>(newDirection);
        }
        else
        {
            // update new position
            position = newP;
            // added the new position to path list
            path.push_back(position);
            moved = true;
        }
    }
}

string Crawler::getLifeHistory() const {
    stringstream history;
    history << id << " Crawler Path: ";

    if (path.empty()) {
        history << "No movement recorded";
    } else {
        for (auto it = path.begin(); it != path.end(); ++it) {
            history << "(" << it->x << "," << it->y << ")";
            if (next(it) != path.end()) history << ",";
        }
    }
    /// TODO change this to show life status (alive or dead) once kill function is implemented
    history << " Still Alive";

    return history.str();
}