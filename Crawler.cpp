#include "Crawler.h"

Crawler::Crawler(unsigned int id, Position position, Direction direction, unsigned int size,
                 bool alive, list<Position> path, int eatenByID)
    : Bug(id, position, direction, size, alive, path, eatenByID)
{
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