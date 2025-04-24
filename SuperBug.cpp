#include "SuperBug.h"

SuperBug::SuperBug(unsigned int id, Position startPos, Direction direction, unsigned int size,
                   bool alive, list<Position> path, int eatenByID)
    : Bug(id, startPos, direction, size, alive, path, eatenByID)
{
}

void SuperBug::handleKeyboardInput(sf::Keyboard::Key key)
{
    keyPressed = true;

    switch (key)
    {
    case sf::Keyboard::Left:
        direction = Direction::West;
        break;
    case sf::Keyboard::Right:
        direction = Direction::East;
        break;
    case sf::Keyboard::Up:
        direction = Direction::North;
        break;
    case sf::Keyboard::Down:
        direction = Direction::South;
        break;
    default:
        keyPressed = false;
        break;
    }
}

void SuperBug::move()
{
    if (!keyPressed) return;

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

    if (newP.x >= 0 && newP.x < 10 && newP.y >= 0 && newP.y < 10)
    {
        position = newP;
        path.push_back(position);
    }

    keyPressed = false;
}

string SuperBug::getBugDetails() const
{
    return "ID: " + to_string(getBugID())
        + ", Type: Crawler"
        + ", Position(x, y): (" + to_string(getPosition().x) + ", " + to_string(getPosition().y) + "), "
        + "Size: " + to_string(getSize())
        + ", Direction: " + getDirectionString()
        + ", Status: " + (isAlive() ? "Alive" : "Dead");
}