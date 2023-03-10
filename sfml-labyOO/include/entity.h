#ifndef ENTITY_H
#define ENTITY_H

#include "stdHeader.h"
#include "map.h"
#include "assetsmanager.h"

class Map;
class AssetsManager;

class Entity
{
public:
	// Constructor and destructor
	Entity(Map &maze, AssetsManager &assetsManager);
	virtual ~Entity();

	// Getters
	virtual int getPositionX() const;
	virtual int getPositionY() const;

	// Setters
	virtual void setPositionX(int newX);
	virtual void setPositionY(int newY);

	virtual void setSpeed(float newSpeed);

	// Update position
	virtual void update(const float &dt) = 0;

	// Draw
	virtual void draw(sf::RenderWindow *window) = 0;

	sf::FloatRect getHitBox() const;

protected:
	AssetsManager &assetsManager;

	// Entity position
	int positionX;
	int positionY;

	// Animation of entity
	float entitySpeed;
	float lastMove;

	// Texture for the entity
	sf::IntRect rectSourceSpriteEntity;
	sf::Sprite entity;

	// Map
	Map &maze;

	// Initialization
	virtual void initVariables() = 0;
};

#endif // ENTITY_H