#include "../include/animation.h"

Animation::Animation(short frameWidth, const std::string& textureLocation, short animationSpeed, short direction): animationIterator(0), currentFrame(0), frameWidth(frameWidth), animationSpeed(std::max<short>(1, animationSpeed)){
	init();
	texture.loadFromFile(textureLocation);
	totalFrames = texture.getSize().x / frameWidth;
}

Animation::~Animation(){
}

void Animation::init(){
}

void Animation::draw(sf::RenderWindow& window){
	sprite.setTexture(texture);

	//0-60 down
	//60-120 left
	//120-180 right
	//180-240 up
	int top;
	if(direction == RIGHT){
		top = 120;
	} else if(direction == LEFT){
		top = 60;
	} else if(direction == DOWN){
		top = 0;
	} else if(direction == UP){
		top = 180;
	}

	sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, top, frameWidth, texture.getSize().y / 4));

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

void Animation::update(sf::Time dt){

	//Player speed (pixels/s)
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