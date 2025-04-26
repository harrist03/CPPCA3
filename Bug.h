#ifndef BUG_H
#define BUG_H

#include <iostream>
#include <list>
#include <vector>

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


class Bug
{
protected: // Changed from private to protected so derived classes can access
    unsigned int id;
    Position position;
    Direction direction;
    unsigned int size;
    bool alive;
    list<Position> path;
    int eatenByID;

public:
    Bug(unsigned int id, Position position, Direction direction, unsigned int size, bool alive = true, list<Position> path = {}, int eatenByID = -1);
    unsigned int getSize() const;
    void setSize(unsigned int newSize);
    bool isAlive() const;
    void setAlive(bool status);
    int getEatenByID() const;
    void setEatenByID(int eaterID);
    bool isWayBlocked(Position newP);
    string getDirectionString() const;
    unsigned int getBugID() const;
    Position getPosition() const;
    string getLifeHistory() const;
    void fight(vector<Bug*>& bugsInCell);

    virtual void move() = 0;
    virtual string getBugDetails() const = 0;
    virtual ~Bug() = default;
};


#endif //BUG_H
