#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "map.h"
#include "player.h"
#include <iostream>
#include <chrono>
#include <thread>

class Map;
class Player;

class Game{
	public:
	//Constructor
	Game();

	//Run the game
	void run();

	private:
	//Handle events
	void handleEvents();

	//Update the game
	void update(sf::Time TimePerFrame);

	//Draw
	void draw();

	//The windows for the render
	sf::RenderWindow window;

	//The map
	Map map;

	//The player
	Player player;
};

#endif //GAME_H