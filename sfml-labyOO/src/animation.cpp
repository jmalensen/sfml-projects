#include "../include/animation.h"

void Animation::initVariables()
{
}

Animation::Animation(short frameWidth, const std::string &textureLocation, short animationSpeed, short direction, short i_nbMovements, ParamsMovement params) : animationIterator(0), currentFrame(0), frameWidth(frameWidth), animationSpeed(std::max<short>(1, animationSpeed))
{
	initVariables();
	this->texture.loadFromFile(textureLocation);
	this->totalFrames = this->texture.getSize().x / this->frameWidth;
	this->nbMovements = i_nbMovements;
	this->paramsMovement = params;
}

Animation::~Animation()
{
}

void Animation::draw(sf::RenderWindow *window)
{
	this->sprite.setTexture(texture);

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

	// std::cout << "Change direction:" << direction << " " << top << std::endl;

	// Params for top sprite depending on direction for the player
	//- Number of possible moves (or line on the sprite)

	this->sprite.setTextureRect(sf::IntRect(this->currentFrame * this->frameWidth, top, this->frameWidth, this->texture.getSize().y / this->nbMovements));

	window->draw(this->sprite);
}

void Animation::setDirection(short ndirection)
{
	this->direction = ndirection;
}

void Animation::setAnimationSpeed(short nanimationSpeed)
{
	this->animationSpeed = std::max<unsigned short>(1, nanimationSpeed);
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

	// // Entity speed (pixels/s)
	// const float speed = 40.f;

	// // Delay between 2 moves
	// static float moveDelay = 0.1f; //(5.f / speed);

	// // Last time player moved
	// static float lastMove = 0.0f;
	// lastMove += dt;

	// if (lastMove >= moveDelay)
	// {
	// 	this->animationIterator -= this->animationSpeed;
	// 	this->currentFrame = (this->currentFrame + 1) % this->totalFrames;

	// 	lastMove = 0.0f;
	// }
}