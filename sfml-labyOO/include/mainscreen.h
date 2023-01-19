#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "screen.h"
#include "map.h"
#include "player.h"

class Map;
class Player;

class MainScreen: public Screen{
	public:
	MainScreen();

	//Initialization
	void init();

	//Update the main screen
	void update(sf::Time TimePerFrame);

	//Draw
	void draw(sf::RenderWindow& target);

	private:
	//The map
	Map map;

	//The player
	Player player;
};

#endif //MAINSCREEN_H