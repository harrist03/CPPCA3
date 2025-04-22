#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"

class Hopper : public Bug
{
private:
    int hopLength;  // Distance the hopper can move (2-4 squares)

public:
    Hopper(unsigned int id, Position position, Direction direction, unsigned int size, int hopLength,
        bool alive = true, list<Position> path = {}, int eatenByID = -1);

    // Getters and setters
    int getHopLength() const;
    void setHopLength(int hopLength);

    // Override virtual function from Bug
    void move() override;
};

#endif // HOPPER_H