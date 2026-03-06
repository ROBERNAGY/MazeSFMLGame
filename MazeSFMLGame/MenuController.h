#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Maze.h"
#include "InputHandler.h"
#include "PlayerCommand.h"
#include <iostream>

class MenuController
{
public:
	MenuController();
	bool WinWindow();
	bool gameplayWindow();

};