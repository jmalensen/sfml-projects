#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "customStructures.h"

class Animation{
	public:

	static constexpr short RIGHT = 1;
	static constexpr short LEFT = 2;
	static constexpr short DOWN = 3;
	static constexpr short UP = 4;
	static constexpr short NODIRECTION = 0;

	//Constructor and destructor
	Animation(short frameWidth, const std::string& textureLocation, short animationSpeed = 1, short direction = NODIRECTION, short i_nbMovements = 1, ParamsMovement params = {0,0,0,0});
	~Animation();

	void init();
	void update(sf::Time dt);
	void draw(sf::RenderWindow& window);

	void setDirection(short ndirection);
	void setAnimationSpeed(short nanimationSpeed);
	void setPosition(short x, short y);
	void setTextureLocation(const std::string& textureLocation);

	void setNbMovements(short nNbMovements);
	void setParamsMovements(ParamsMovement nParamMovements);

	private:
	short direction;

	//Increment the currentFrame as soon as this iterator reaches the animationSpeed
	short animationIterator;
	short animationSpeed;
	short currentFrame;
	short frameWidth;
	short totalFrames;

	short nbMovements;

	sf::Sprite sprite;

	sf::Texture texture;

	ParamsMovement paramsMovement;
};

#endif //ANIMATION_H