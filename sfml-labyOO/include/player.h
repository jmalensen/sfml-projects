#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "map.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <array>

class Map;

class Player{
	public:
	//Constructor and destructor
	Player(Map& maze);
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
	bool getExited() const;

	//Update position
	void update(sf::Time dt);

	//Reset sound memory for each level
	void resetSounds();

	//Draw
	void draw(sf::RenderTarget& target);

	private:
	//Player position
	int playerX;
	int playerY;

	//Sounds
	sf::SoundBuffer buffer;
	sf::Sound sound;

	sf::SoundBuffer bufferHurt;
	sf::Sound hurtSound;

	sf::SoundBuffer buffer2;
	sf::Sound unlockSound;
	bool unlockSoundPlayed;

	sf::SoundBuffer buffer3;
	sf::Sound exitLevelSound;
	bool nextLevelPlayed;

	// sf::SoundBuffer buffer4;
	// sf::Sound winSound;
	bool exit;

	//Texture for the player
	sf::Texture texturePlayer;
	sf::IntRect rectSourceSpritePlayer;
	sf::Sprite player;

	//Map
	Map& maze;
};

#endif //PLAYER_H