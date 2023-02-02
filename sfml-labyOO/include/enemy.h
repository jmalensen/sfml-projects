#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "map.h"
#include "assetsmanager.h"
#include "entity.h"
#include "player.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <string>

class Map;
class AssetsManager;
class Player;

class Enemy: public Entity{
	public:
	//Constructor and destructor
	Enemy(Map& maze, AssetsManager &assetsManager);
	~Enemy() final;

	//Initialization
	void init() override;

	//Update position
	void update(sf::Time dt) override;
	void update(sf::Time dt, Player& player);

	//Draw
	void draw(sf::RenderWindow& window) override;

	//Set direction of enemy
	void setBehaviour(int directionMovement, int min, int max);

	static constexpr int HORIZONTAL = 1;
	static constexpr int VERTICAL = 2;

	private:
	bool isMovingHorizontal;
	bool goingRight;
	bool goingDown;
	int minVal;
	int maxVal;

	//Sounds
	sf::Sound hurtSound;
};

#endif //ENEMY_H