#ifndef ANIMATION_H
#define ANIMATION_H

#include "stdHeader.h"
#include "customStructures.h"
#include "gui.h"

class Animation
{
public:
	static constexpr short RIGHT = 1;
	static constexpr short LEFT = 2;
	static constexpr short DOWN = 3;
	static constexpr short UP = 4;
	static constexpr short NODIRECTION = 0;

	// Constructor and destructor
	Animation(short frameWidth, const std::string &textureLocation, short direction = NODIRECTION, short i_nbMovements = 1, ParamsMovement params = {0, 0, 0, 0});
	~Animation();

	void update(const float &dt);
	void draw(sf::RenderWindow *window);

	void setDirection(short ndirection);
	void setPosition(short x, short y);
	void setTextureLocation(const std::string &textureLocation);

	void setNbMovements(short nNbMovements);
	void setParamsMovements(ParamsMovement nParamMovements);

private:
	short m_direction;

	// Increment the currentFrame as soon as this iterator reaches the animationSpeed
	short m_animationIterator;
	short m_frameWidth;
	short m_totalFrames;
	short m_nbMovements;

	sf::Sprite m_sprite;

	sf::Texture m_texture;

	ParamsMovement m_paramsMovement;

	float m_animationTime{0.f};
	float m_frameDuration{0.125f};
	int m_currentFrame;

	sf::RectangleShape m_rectangleSize;

	void initVariables();
};

#endif // ANIMATION_H