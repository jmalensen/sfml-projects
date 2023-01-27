#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <array>

#include "../include/game.h"

int main() {

	// auto window = sf::RenderWindow{ { SCREEN_WIDTH, SCREEN_HEIGHT }, "SFML Labyrinth" };
	// window.setFramerateLimit(60);

	Game game;
	game.run();

	return 0;
}

//Game owns the ScreenManager
//Game make the screen changes
//When player exit, we need to change the screen from Game