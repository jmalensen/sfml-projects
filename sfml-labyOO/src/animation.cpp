#include "../include/animation.h"

void Animation::initVariables()
{
}

Animation::Animation(short frameWidth, const std::string &textureLocation, short direction, short i_nbMovements, ParamsMovement params) : direction(direction), animationIterator(0), currentFrame(0), frameWidth(frameWidth)
{
	this->initVariables();

	if (!this->texture.loadFromFile(textureLocation))
	{
		throw "ERROR::ANIMATION::FAILED_TO_LOAD_ANIMATION_TEXTURE";
	}

	this->totalFrames = this->texture.getSize().x / this->frameWidth;
	this->nbMovements = i_nbMovements;
	this->paramsMovement = params;
	this->sprite.setTexture(texture);
}

Animation::~Animation()
{
}

void Animation::draw(sf::RenderWindow *window)
{
	int top;
	if (this->direction == NODIRECTION)
	{
		top = 0;
	}
	else if (this->direction == RIGHT)
	{
		top = this->paramsMovement.topSpriteMoveRight;
	}
	else if (this->direction == LEFT)
	{
		top = this->paramsMovement.topSpriteMoveLeft;
	}
	else if (this->direction == DOWN)
	{
		top = this->paramsMovement.topSpriteMoveDown;
	}
	else if (this->direction == UP)
	{
		top = this->paramsMovement.topSpriteMoveUp;
	}

	// Params for top sprite depending on direction for the player
	//- Number of possible moves (or line on the sprite)

	this->sprite.setTextureRect(sf::IntRect(this->currentFrame * this->frameWidth, top, this->frameWidth, this->texture.getSize().y / this->nbMovements));

	float factor = gui::getFactor(60, window);
	this->sprite.setScale(factor, factor);

	// std::cout << "Scale factor:" << gui::getFactor(60, window) << std::endl;

	// sf::RectangleShape recTest;
	// recTest.setFillColor(sf::Color::Black);
	// recTest.setSize(sf::Vector2f(
	// 		factor,
	// 		factor));

	// recTest.setPosition(sf::Vector2f(
	// 		this->sprite.getPosition()));

	// window->draw(recTest);
	window->draw(this->sprite);
}

void Animation::setDirection(short ndirection)
{
	this->direction = ndirection;
}

void Animation::setPosition(short x, short y)
{
	this->sprite.setPosition(x, y);
}

void Animation::setTextureLocation(const std::string &textureLocation)
{
	this->texture.loadFromFile(textureLocation);
}

void Animation::setNbMovements(short nNbMovements)
{
	this->nbMovements = nNbMovements;
}

void Animation::setParamsMovements(ParamsMovement nParamMovements)
{
	this->paramsMovement = nParamMovements;
}

void Animation::update(const float &dt)
{

	// Add the elapsed time since the last update to the animation time
	this->animationTime += dt;

	// Calculate the number of frames that have passed since the last update
	int numFrames = static_cast<int>(this->animationTime / this->frameDuration);

	// Update the current frame based on the number of frames that have passed
	this->currentFrame = (this->currentFrame + numFrames) % this->totalFrames;

	// std::cout << "Animation::update: " << this->currentFrame << " " << numFrames << std::endl;

	// Reset the animation time to the reminder after dividing by the frame duration
	this->animationTime = fmodf(this->animationTime, this->frameDuration);
}