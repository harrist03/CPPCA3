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
    list<Position> path;
public:
    Crawler(int id, Position position, Direction direction, int size, list<Position> path);
    void move();
    bool isWayBlocked();
};

#endif // CRAWLER_H
