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
	void draw(sf::RenderTarget& target) override;

	private:
	bool goingRight;
};

#endif //ENEMY_H