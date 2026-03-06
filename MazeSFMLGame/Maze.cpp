#include "Maze.h"
#include <stack>
#include <random>
#include <iostream>

Maze::Maze(int size, int  sizeTwo, int cellSize)
{
    this->size = size;
    this->sizeTwo = sizeTwo;
    this->cellSize = cellSize;
    maze = std::vector<std::vector<int>>(size, std::vector<int>(sizeTwo, 0));
    generateMazeDFS(maze);
    buildColliders(maze, cellSize);
    createWinPosition();
};
void Maze::createWinPosition()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distX(sizeTwo / 2, sizeTwo - 1);
    std::uniform_int_distribution<int> distY(size / 2, size - 1);
    int x = distX(rng), y = distY(rng);
    while (maze[y][x] == 0) {
        x = distX(rng);
        y = distY(rng);
    }

    winPosition.x = x;
    winPosition.y = y;
    winRect = sf::FloatRect(x * cellSize, y * cellSize, cellSize, cellSize);
}

void Maze::drawWinPosition(sf::RenderWindow& window)
{
    sf::Texture gateTexture;
    if (!gateTexture.loadFromFile("assets/gate.png")) {
        std::cout << "error loading wall or path texture !!" << std::endl;
    }
    sf::Sprite gateSprite(gateTexture);
    gateSprite.setPosition(sf::Vector2f(winPosition.x * cellSize, winPosition.y * cellSize));
    window.draw(gateSprite);
}

void Maze::buildColliders(const std::vector<std::vector<int>>& maze, int tileSize)
{
    wallColliders.clear();

    for (int y = 0; y < maze.size(); y++)
    {
        for (int x = 0; x < maze[y].size(); x++)
        {
            if (maze[y][x] == 0)
            {
                wallColliders.emplace_back(x * tileSize, y * tileSize, tileSize, tileSize);
            }
        }
    }
}

void Maze::generateMazeDFS(std::vector<std::vector<int>>& maze)
{
    int dir[4][2] = { {-2,0}, {2,0}, {0,-2} , {0,2} };

    std::stack<std::pair<int, int>> s;
    s.push({ 1, 1 });

    maze[1][1] = 1;

    std::random_device rd;
    std::mt19937 rng(rd());
    while (!s.empty())
    {
        std::shuffle(std::begin(dir), std::end(dir), rng);
        auto [nx, ny] = s.top();
        bool moved = false;
        for (int i = 0; i < 4; i++)
        {
            int newX = nx + dir[i][0];
            int newY = ny + dir[i][1];
            if (newX < maze[0].size() - 1 && newY < maze.size() - 1 && newX > 0 && newY > 0 && maze[newY][newX] == 0)
            {
                maze[ny + dir[i][1] / 2][nx + dir[i][0] / 2] = 1;
                maze[newY][newX] = 1;
                s.push({ newX , newY });
                moved = true;
                break;
            }
        }
        if (!moved)
            s.pop();
    }

}

bool Maze::checkCollided(sf::FloatRect object)
{
    for (auto& wall : wallColliders)
    {
        if (object.intersects(wall))
        {
            return true;

        }
    }
    return false;
}

void Maze::mazeDraw(sf::RenderWindow& window, sf::Sprite& wallSprite, sf::Sprite& pathSprite)
{
    for (int y = 0; y < maze.size(); y++)
    {
        for (int x = 0; x < maze[y].size(); ++x)
        {
            sf::Sprite sprite = (maze[y][x] == 0) ? wallSprite : pathSprite;
            sprite.setPosition(x * cellSize, y * cellSize);
            window.draw(sprite);
        }
    }
}

bool Maze::isWin(sf::FloatRect object)
{
    if (object.intersects(winRect))
    {
        return true;

    }
}