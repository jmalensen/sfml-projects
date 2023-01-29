#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "map.h"
#include "assetsmanager.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <string>

class Map;
class AssetsManager;

class Player{
	public:
	//Constructor and destructor
	Player(Map& maze, AssetsManager &assetsManager);
	~Player();

	//Initialization
	void init();

	//Getters
	int getPlayerX() const;
	int getPlayerY() const;

	//Setters
	void setPlayerX(int newX);
	void setPlayerY(int newY);

	//Getter exit
	bool getHasExited() const;

	//Update position
	void update(sf::Time dt);

	//Reset sound memory for each level
	void resetSounds();

	//Draw
	void draw(sf::RenderTarget& target);

	private:
	AssetsManager &assetsManager;
	
	//Player position
	int playerX;
	int playerY;

	//Sounds
	sf::Sound sound;
	sf::Sound hurtSound;
	sf::Sound unlockSound;
	bool unlockEnabled;

	sf::Sound exitLevelSound;
	bool nextLevelEnabled;
	bool trapEnabled;

	// sf::SoundBuffer buffer4;
	// sf::Sound winSound;
	bool exit;

	//Texture for the player
	sf::IntRect rectSourceSpritePlayer;
	sf::Sprite player;

	//Map
	Map& maze;
};

#endif //PLAYER_H