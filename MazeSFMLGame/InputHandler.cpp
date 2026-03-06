#include <SFML/Graphics.hpp>
#include "InputHandler.h"

PlayerCommand InputHandler::getCommand()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return PlayerCommand::moveLeft;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return PlayerCommand::moveRight;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return PlayerCommand::moveUp;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return PlayerCommand::moveDown;

    return PlayerCommand::idle;
}