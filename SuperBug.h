#include "Bug.h"
#include <SFML/Window/Keyboard.hpp>


#ifndef SUPERBUG_H
#define SUPERBUG_H

class SuperBug : public Bug {
    private:
        bool keyPressed = false;

    public:
        SuperBug(unsigned int id = 999, Position startPos = {4, 4}, Direction direction = Direction::North,
            unsigned int size = 20, bool alive = true, list<Position> path = {}, int eatenByID = -1);
        void handleKeyboardInput(sf::Keyboard::Key key);
        void move() override;
        string getBugDetails() const override;
};

#endif // SUPERBUG_H