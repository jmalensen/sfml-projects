#include "../include/entity.h"

Entity::Entity(Map &maze, AssetsManager &assetsManager) : maze(maze), assetsManager(assetsManager) {}

Entity::~Entity() {}

// Getters
int Entity::getPositionX() const
{
	return this->positionX;
}
int Entity::getPositionY() const
{
	return this->positionY;
}

// Setters
void Entity::setPositionX(int newX)
{
	this->positionX = newX;
}
void Entity::setPositionY(int newY)
{
	this->positionY = newY;
}

void Entity::setSpeed(float newSpeed)
{
	this->entitySpeed = newSpeed;
}

sf::FloatRect Entity::getHitBox() const
{
	return sf::FloatRect(this->positionX, this->positionY, 60, 60);
}