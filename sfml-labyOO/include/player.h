#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "map.h"
#include "assetsmanager.h"
#include "entity.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <string>

class Map;
class AssetsManager;

class Player: public Entity{
	public:
	//Constructor and destructor
	Player(Map& maze, AssetsManager &assetsManager);
	~Player();

	//Initialization
	virtual void init();

	//Getter exit
	bool getHasExited() const;

	//Update position
	virtual void update(sf::Time dt);

	//Reset sound memory for each level
	void resetSounds();

	//Draw
	virtual void draw(sf::RenderTarget& target);

	private:

	//Sounds
	sf::Sound sound;
	sf::Sound hurtSound;
	sf::Sound unlockSound;
	bool unlockEnabled;

	sf::Sound exitLevelSound;
	bool nextLevelEnabled;
	bool trapEnabled;

	bool exit;
};

#endif //PLAYER_H