#include "Hopper.h"

Hopper::Hopper(unsigned int id, Position position, Direction direction, unsigned int size,
                int hopLength, bool alive, list<Position> path, int eatenByID)
    : Bug(id, position, direction, size, alive, path, eatenByID), hopLength(hopLength)
{
    // Validate hopLength is between 2-4
    if (hopLength < 2 || hopLength > 4)
    {
        this->hopLength = 2; // Default value if invalid
    }
}

int Hopper::getHopLength() const
{
    return hopLength;
}

void Hopper::setHopLength(int newHopLength)
{
    hopLength = newHopLength;
}

void Hopper::move() override
{
    bool moved = false;
    while (!moved)
    {
        Position newP = position;
        switch (direction)
        {
            case Direction::North:
                newP.y -= hopLength;
            break;
            case Direction::East:
                newP.x += hopLength;
            break;
            case Direction::South:
                newP.y += hopLength;
            break;
            case Direction::West:
                newP.x -= hopLength;
            break;
            default:
                break;
        }

        if (isWayBlocked(newP))
        {
            srand(time(0));
            // generate between 1 and 4
            int newDirection = 1 + rand() % 4;
            // new direction for hopper
            direction = static_cast<Direction>(newDirection);
        }
        else
        {
            // check if it needs to adjust for hitting an edge
            if (newP.x < 0) newP.x = 0;
            if (newP.x >= 10) newP.x = 9;
            if (newP.y < 0) newP.y = 0;
            if (newP.y >= 10) newP.y = 9;

            // update new position
            position = newP;
            // added the new position to path list
            path.push_back(position);
            moved = true;
        }
    }
}

string Hopper::getBugDetails() const override
{
    return "ID: " + to_string(getBugID())
        + ", Type: Hopper"
        + ", Position(x, y): (" + to_string(getPosition().x) + ", " + to_string(getPosition().y) + "), "
        + "Size: " + to_string(getSize())
        + ", Direction: " + getDirectionString()
        + ", Hop Length: " + to_string(hopLength)
        + ", Status: " + (isAlive() ? "Alive" : "Dead");
}