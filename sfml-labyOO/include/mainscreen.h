#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "stdHeader.h"
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

	bool getIsPlayerDead() const;

	private:
	//The assets manager
	AssetsManager &assetsManager;

	bool isPlayerDead;

	//The map
	Map map;

	//The player
	Player player;
	std::vector< std::shared_ptr<Enemy>> enemies;
};

#endif //MAINSCREEN_H