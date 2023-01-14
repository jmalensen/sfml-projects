#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "map.h"

class Map;

class Player{
	public:
	//Constructor
	Player(Map& maze);

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

	//Draw
	void draw(sf::RenderTarget& target);

	private:
	//Player position
	int playerX;
	int playerY;

	//Sounds
	sf::SoundBuffer buffer;
	sf::Sound sound;

	sf::SoundBuffer buffer2;
	sf::Sound unlockSound;
	bool unlockSoundPlayed;

	sf::SoundBuffer buffer3;
	sf::Sound winSound;
	bool exit;

	//Texture for the player
	sf::Texture texturePlayer;
	sf::IntRect rectSourceSpritePlayer;
	sf::Sprite player;

	//Map
	Map& maze;
};

#endif //PLAYER_H