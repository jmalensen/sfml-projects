#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "map.h"
#include "assetsmanager.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

class Map;
class AssetsManager;

class Entity{
	public:
	//Constructor and destructor
	Entity(Map& maze, AssetsManager &assetsManager);
	virtual ~Entity();

	//Initialization
	virtual void init() = 0;

	//Getters
	virtual int getPositionX() const;
	virtual int getPositionY() const;

	//Setters
	virtual void setPositionX(int newX);
	virtual void setPositionY(int newY);

	//Update position
	virtual void update(sf::Time dt) = 0;

	//Draw
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::FloatRect getHitBox() const;

	protected:
	AssetsManager &assetsManager;

	//Entity position
	int positionX;
	int positionY;

	//Texture for the entity
	sf::IntRect rectSourceSpriteEntity;
	sf::Sprite entity;

	//Map
	Map& maze;
};

#endif //ENTITY_H