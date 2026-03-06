#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Maze
{
    int size;
    int sizeTwo;
    int cellSize;
    std::vector<std::vector<int>> maze;
    std::vector<sf::FloatRect> wallColliders;
    sf::Vector2f winPosition;
    sf::FloatRect winRect;
public:

    Maze(int size, int  sizeTwo, int cellSize);
    void generateMazeDFS(std::vector<std::vector<int>>& maze);
    void buildColliders(const std::vector<std::vector<int>>& maze, int cellSize);
    bool checkCollided(sf::FloatRect object);
    void mazeDraw(sf::RenderWindow& window, sf::Sprite& wallSprite, sf::Sprite& pathSprite);
    void createWinPosition();
    void drawWinPosition(sf::RenderWindow& window);
    bool isWin(sf::FloatRect object);
};