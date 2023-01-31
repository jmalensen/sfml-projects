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
	~Player() final;

	//Initialization
	void init() override;

	//Getter exit
	bool getHasExited() const;

	//Set death status
	void justDie(bool newStatus);

	//Check if player is dead
	bool isDead() const;

	//Update position
	void update(sf::Time dt) override;

	//Reset sound memory for each level
	void resetSounds();

	//Draw
	void draw(sf::RenderTarget& target) override;

	private:

	//Sounds
	sf::Sound sound;
	sf::Sound hurtSound;
	sf::Sound unlockSound;
	bool unlockEnabled;

	sf::Sound exitLevelSound;
	bool nextLevelEnabled;
	bool trapEnabled;

	bool dead;
	bool exit;
};

#endif //PLAYER_H