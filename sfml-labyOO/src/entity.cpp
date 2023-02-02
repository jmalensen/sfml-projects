#include "../include/entity.h"

Entity::Entity(Map& maze, AssetsManager &assetsManager): maze(maze), assetsManager(assetsManager) {}

Entity::~Entity() {}

//Getters
int Entity::getPositionX() const{
	return positionX;
}
int Entity::getPositionY() const{
	return positionY;
}

//Setters
void Entity::setPositionX(int newX){
	positionX = newX;
}
void Entity::setPositionY(int newY){
	positionY = newY;
}

void Entity::setSpeed(float newSpeed){
	entitySpeed = newSpeed;
}

sf::FloatRect Entity::getHitBox() const{
	return sf::FloatRect(positionX, positionY, 60, 60);
}