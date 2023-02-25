#include "../include/animation.h"

void Animation::initVariables()
{
}

Animation::Animation(short frameWidth, const std::string &textureLocation, short direction, short i_nbMovements, ParamsMovement params) : m_direction(direction), m_animationIterator(0), m_currentFrame(0), m_frameWidth(frameWidth)
{
	this->initVariables();

	if (!this->m_texture.loadFromFile(textureLocation))
	{
		throw "ERROR::ANIMATION::FAILED_TO_LOAD_ANIMATION_TEXTURE";
	}

	this->m_totalFrames = this->m_texture.getSize().x / this->m_frameWidth;
	this->m_nbMovements = i_nbMovements;
	this->m_paramsMovement = params;
	this->m_sprite.setTexture(m_texture);
}

Animation::~Animation()
{
}

void Animation::draw(sf::RenderWindow *window)
{
	int top;
	if (this->m_direction == NODIRECTION)
	{
		top = 0;
	}
	else if (this->m_direction == RIGHT)
	{
		top = this->m_paramsMovement.topSpriteMoveRight;
	}
	else if (this->m_direction == LEFT)
	{
		top = this->m_paramsMovement.topSpriteMoveLeft;
	}
	else if (this->m_direction == DOWN)
	{
		top = this->m_paramsMovement.topSpriteMoveDown;
	}
	else if (this->m_direction == UP)
	{
		top = this->m_paramsMovement.topSpriteMoveUp;
	}

	// Params for top sprite depending on direction for the player
	//- Number of possible moves (or line on the sprite)

	this->m_sprite.setTextureRect(sf::IntRect(this->m_currentFrame * this->m_frameWidth, top, this->m_frameWidth, this->m_texture.getSize().y / this->m_nbMovements));

	float factor = gui::getFactor(60, window);
	this->m_sprite.setScale(factor, factor);

	// std::cout << "Scale factor:" << gui::getFactor(60, window) << std::endl;

	// sf::RectangleShape recTest;
	// recTest.setFillColor(sf::Color::Black);
	// recTest.setSize(sf::Vector2f(
	// 		factor,
	// 		factor));

	// recTest.setPosition(sf::Vector2f(
	// 		this->m_sprite.getPosition()));

	// window->draw(recTest);
	window->draw(this->m_sprite);
}

void Animation::setDirection(short ndirection)
{
	this->m_direction = ndirection;
}

void Animation::setPosition(short x, short y)
{
	this->m_sprite.setPosition(x, y);
}

void Animation::setTextureLocation(const std::string &textureLocation)
{
	this->m_texture.loadFromFile(textureLocation);
}

void Animation::setNbMovements(short nNbMovements)
{
	this->m_nbMovements = nNbMovements;
}

void Animation::setParamsMovements(ParamsMovement nParamMovements)
{
	this->m_paramsMovement = nParamMovements;
}

void Animation::update(const float &dt)
{

	// Add the elapsed time since the last update to the animation time
	this->m_animationTime += dt;

	// Calculate the number of frames that have passed since the last update
	int numFrames = static_cast<int>(this->m_animationTime / this->m_frameDuration);

	// Update the current frame based on the number of frames that have passed
	this->m_currentFrame = (this->m_currentFrame + numFrames) % this->m_totalFrames;

	// std::cout << "Animation::update: " << this->m_currentFrame << " " << numFrames << std::endl;

	// Reset the animation time to the reminder after dividing by the frame duration
	this->m_animationTime = fmodf(this->m_animationTime, this->m_frameDuration);
}