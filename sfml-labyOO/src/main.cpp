#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

#include "../include/game.h"

int main()
{

	std::cout << "Start? " << std::endl;

	Game game;
	game.run();

	return 0;
}