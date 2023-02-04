#include "../include/animation.h"

Animation::Animation(short frameWidth, const std::string& textureLocation, short animationSpeed, short direction, short i_nbMovements, ParamsMovement params): animationIterator(0), currentFrame(0), frameWidth(frameWidth), animationSpeed(std::max<short>(1, animationSpeed)){
	init();
	texture.loadFromFile(textureLocation);
	totalFrames = texture.getSize().x / frameWidth;
	nbMovements = i_nbMovements;
	paramsMovement = params;
}

Animation::~Animation(){
}

void Animation::init(){
}

void Animation::draw(sf::RenderWindow& window){
	sprite.setTexture(texture);

	int top;
	if(direction == NODIRECTION){
		top = 0;
	} else if(direction == RIGHT){
		top = paramsMovement.topSpriteMoveRight;
	} else if(direction == LEFT){
		top = paramsMovement.topSpriteMoveLeft;
	} else if(direction == DOWN){
		top = paramsMovement.topSpriteMoveDown;
	} else if(direction == UP){
		top = paramsMovement.topSpriteMoveUp;
	}

	// std::cout << "Change direction:" << direction << " " << top << std::endl;

	//Params for top sprite depending on direction for the player
	//- Number of possible moves (or line on the sprite)

	sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, top, frameWidth, texture.getSize().y / nbMovements));

	window.draw(sprite);
}

void Animation::setDirection(short ndirection){
	this->direction = ndirection;
}

void Animation::setAnimationSpeed(short nanimationSpeed){
	this->animationSpeed = std::max<unsigned short>(1, nanimationSpeed);
}

void Animation::setPosition( short x, short y){
	sprite.setPosition(x, y);
}

void Animation::setTextureLocation(const std::string& textureLocation){
	texture.loadFromFile(textureLocation);
}

void Animation::setNbMovements(short nNbMovements){
	nbMovements = nNbMovements;
}

void Animation::setParamsMovements(ParamsMovement nParamMovements){
	paramsMovement = nParamMovements;
}

void Animation::update(sf::Time dt){

	//Entity speed (pixels/s)
	static const float speed = 40.f;

	//Delay between 2 moves
	static const sf::Time moveDelay = sf::seconds(5.f / speed);

	//Last time player moved
	static sf::Time lastMove = sf::Time::Zero;
	lastMove += dt;

	if(lastMove >= moveDelay){
		animationIterator -= animationSpeed;
		currentFrame = (currentFrame + 1) % totalFrames;
		
		lastMove = sf::Time::Zero;
	}
}