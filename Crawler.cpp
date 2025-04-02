#include "Crawler.h"

// allows non default values for Crawler
Crawler::Crawler(unsigned int id, Position position, Direction direction, unsigned int size, bool alive, list<Position> path)
    :id(id), position(position), direction(direction), size(size), alive(alive), path(path)
{}

string Crawler::getBugDetails() const
{
    return "Bug ID: " + to_string(id) 
        + ", Position(x, y): (" + to_string(position.x)
        + ", " + to_string(position.y) + "), " 
        + "Size: " + to_string(size) 
        + ", Direction: " + getDirectionString()
        + ", Status: " + (alive ? "Alive" : "Dead");
}

string Crawler::getDirectionString() const {
    switch (direction) {
        case Direction::North: return "North";
        case Direction::East:  return "East";
        case Direction::South: return "South";
        case Direction::West:  return "West";
        default:               return "Unknown";
    }
}

unsigned int Crawler::getBugID() const
{
    return id;
}