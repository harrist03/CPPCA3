// BugRenderer.cpp
#include "BugRenderer.h"
#include "Hopper.h"
#include "Crawler.h"

BugRenderer::BugRenderer(int width, int height)
    : window(sf::VideoMode(width, height), "Bug Simulation"), cellSize(width / 10.0f)
{
    // Load textures and font
    if (!font.loadFromFile("resources/arial.TTF"))
    {
        std::cerr << "Error loading font" << std::endl;
    }
    if (!crawlerTexture.loadFromFile("resources/crawler.png")) 
    {
        std::cerr << "Error loading crawler texture" << std::endl;
    } 

    if (!hopperTexture.loadFromFile("resources/hopper.png"))
    {
        std::cerr << "Error loading hopper texture" << std::endl;
    }
}

BugRenderer::~BugRenderer()
{
    if (window.isOpen())
    {
        window.close();
    }
}

void BugRenderer::drawGrid()
{
    // Draw checkerboard pattern cells
    bool isBlack = false;

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(x * cellSize, y * cellSize);

            // Alternate colors for chess pattern
            if (isBlack)
            {
                cell.setFillColor(sf::Color(50, 50, 50)); // Dark gray
            }
            else
            {
                cell.setFillColor(sf::Color(200, 200, 200)); // Light gray
            }

            // Draw the cell
            window.draw(cell);

            // Toggle for next cell in row
            isBlack = !isBlack;
        }
        // Toggle again at the end of row to maintain pattern
        isBlack = !isBlack;
    }
}

void BugRenderer::drawBugs(const std::vector<Bug *> &bugs)
{
    for (const Bug *bug : bugs)
    {
        if (!bug->isAlive())
            continue;

        Position pos = bug->getPosition();

        // Configure based on bug type
        if (dynamic_cast<const Crawler *>(bug))
        {
            // Create sprite for crawler
            sf::Sprite crawlerSprite;
            crawlerSprite.setTexture(crawlerTexture);
            
            // Scale the sprite to fit the cell (adjust these values as needed)
            float scaleX = (cellSize * 0.7f) / crawlerTexture.getSize().x;
            float scaleY = (cellSize * 0.7f) / crawlerTexture.getSize().y;
            crawlerSprite.setScale(scaleX, scaleY);
            
            // Center the sprite in the cell
            crawlerSprite.setPosition(
                pos.x * cellSize + (cellSize - crawlerSprite.getGlobalBounds().width) / 2,
                pos.y * cellSize + (cellSize - crawlerSprite.getGlobalBounds().height) / 2
            );
            
            // Draw the sprite
            window.draw(crawlerSprite);
        }
        else if (dynamic_cast<const Hopper *>(bug))
        {
            // create sprite for hopper
            sf::Sprite hopperSprite;
            hopperSprite.setTexture(hopperTexture);

            // Scale the sprite to fit the cell (adjust these values as needed)
            float scaleX = (cellSize * 0.7f) / hopperTexture.getSize().x;
            float scaleY = (cellSize * 0.7f) / hopperTexture.getSize().y;
            hopperSprite.setScale(scaleX, scaleY);

            // Center the sprite in the cell
            hopperSprite.setPosition(
                pos.x * cellSize + (cellSize - hopperSprite.getGlobalBounds().width) / 2,
                pos.y * cellSize + (cellSize - hopperSprite.getGlobalBounds().height) / 2
            );

            // Draw the sprite
            window.draw(hopperSprite);
        }

        // Draw the bug's size
        sf::Text idText;
        idText.setFont(font);
        idText.setString(std::to_string(bug->getSize()));
        idText.setCharacterSize(cellSize * 0.3f);
        idText.setPosition(pos.x * cellSize + cellSize * 0.4f, pos.y * cellSize + cellSize * 0.4f);
        
        // Make text more visible
        idText.setFillColor(sf::Color::White);
        idText.setOutlineColor(sf::Color::Black);
        idText.setOutlineThickness(1.0f);
        
        window.draw(idText);
    }
}

void BugRenderer::render(const Board &board, const std::vector<Bug *> &bugs)
{
    window.clear(sf::Color(30, 30, 30));

    drawGrid();
    drawBugs(bugs);

    window.display();
}

bool BugRenderer::isOpen() const
{
    return window.isOpen();
}

void BugRenderer::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // check if user clicked the close button
        if (event.type == sf::Event::Closed)
            window.close();
    }
}