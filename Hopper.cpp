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

void Hopper::move()
{
    bool moved = false;
    while (!moved)
    {
        Position newP = position;
        int maxHop;

        switch (direction)
        {
            case Direction::North:
                if (position.y == 0) break;
                maxHop = min(hopLength, position.y);
                newP.y -= maxHop;
                break;

            case Direction::East:
                if (position.x == 9) break;
                maxHop = min(hopLength, 9 - position.x);
                newP.x += maxHop;
                break;

            case Direction::South:
                if (position.y == 9) break;
                maxHop = min(hopLength, 9 - position.y);
                newP.y += maxHop;
                break;

            case Direction::West:
                if (position.x == 0) break;
                maxHop = min(hopLength, position.x);
                newP.x -= maxHop;
                break;

            default:
                break;
        }

        // if move is still not valid (path blocked), pick new direction
        if (newP.x == position.x && newP.y == position.y)
        {
            srand(time(0));
            int newDirection = 1 + rand() % 4;
            direction = static_cast<Direction>(newDirection);
        }
        else
        {
            position = newP;
            path.push_back(position);
            moved = true;
        }
    }
}

string Hopper::getBugDetails() const
{
    return "ID: " + to_string(getBugID())
        + ", Type: Hopper"
        + ", Position(x, y): (" + to_string(getPosition().x) + ", " + to_string(getPosition().y) + "), "
        + "Size: " + to_string(getSize())
        + ", Direction: " + getDirectionString()
        + ", Hop Length: " + to_string(hopLength)
        + ", Status: " + (isAlive() ? "Alive" : "Dead");
}