#ifndef BUG_RENDERER_H
#define BUG_RENDERER_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Bug.h"
#include "SuperBug.h"
#include <vector>

class BugRenderer {
private:
    sf::RenderWindow window;
    sf::Font font;
    float cellSize;
    
    // Bug textures/sprites
    sf::Texture crawlerTexture;
    sf::Texture hopperTexture;
    sf::Texture superBugTexture;
    
    void drawGrid();
    void drawBugs(const std::vector<Bug*>& bugs);
public:
    BugRenderer(int width = 800, int height = 800);
    ~BugRenderer();
    
    void render(const Board& board, const std::vector<Bug*>& bugs);
    bool isOpen() const;
    void processEvents(SuperBug* superBug, vector<Bug*>& bugs);
};

#endif