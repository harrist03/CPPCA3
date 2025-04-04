#ifndef CRAWLER_H
#define CRAWLER_H

#include <iostream>
#include <list>

using namespace std;

struct Position
{
    int x;
    int y;
};

enum class Direction
{
    North = 1,
    East = 2,
    South = 3,
    West = 4
};

class Crawler
{
private:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    list<Position> path;

public:
    Crawler(unsigned int id, Position position, Direction direction, unsigned int size, bool alive = true, list<Position> path = {});
    void move();
    bool isWayBlocked(Position newP);
    string getBugDetails() const;
    string getDirectionString() const;
    unsigned int getBugID() const;
    Position getPosition() const;
    string getLifeHistory() const;
};

#endif // CRAWLER_H
