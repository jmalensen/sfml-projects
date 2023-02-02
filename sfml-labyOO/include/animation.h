#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>

class Animation{
	public:
	static constexpr int RIGHT = 1;
	static constexpr int LEFT = 2;
	static constexpr int DOWN = 3;
	static constexpr int UP = 4;

	//Constructor and destructor
	Animation(short frameWidth, const std::string& textureLocation, short animationSpeed = 1, short direction = RIGHT);
	~Animation();

	void init();
	void update(sf::Time dt);
	void draw(sf::RenderWindow& window);

	void setDirection(short ndirection);
	void setAnimationSpeed(short nanimationSpeed);
	void setPosition(short x, short y);
	void setTextureLocation(const std::string& textureLocation);

	private:
	short direction;

	//Increment the currentFrame as soon as this iterator reaches the animationSpeed
	short animationIterator;
	short animationSpeed;
	short currentFrame;
	short frameWidth;
	short totalFrames;

	sf::Sprite sprite;

	sf::Texture texture;
};

#endif //ANIMATION_H