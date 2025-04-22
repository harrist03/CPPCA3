#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"

class Crawler : public Bug
{
public:
    Crawler(unsigned int id, Position position, Direction direction, unsigned int size,
            bool alive = true, list<Position> path = {}, int eatenByID = -1);

    // Override virtual function from Bug
    void move() override;
    string getBugDetails() const override;
};

#endif // CRAWLER_H
