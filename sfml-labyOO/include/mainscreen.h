#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include "screen.h"
#include "assetsmanager.h"
#include "map.h"
#include "player.h"
#include "enemy.h"

class AssetsManager;
class Map;
class Player;
class Enemy;

class MainScreen: public Screen{
	public:
	//Constructor and destructor
	MainScreen(AssetsManager &assetsManager);
	~MainScreen();

	//Initialization
	void init();

	//Handling events
	void handleEvents(sf::Event event);

	//Update the main screen
	void update(sf::Time TimePerFrame);

	//Draw
	void draw(sf::RenderWindow& window);

	private:
	//The assets manager
	AssetsManager &assetsManager;

	//The map
	Map map;

	//The player
	Player player;
	std::vector< std::shared_ptr<Enemy>> enemies;
};

#endif //MAINSCREEN_H