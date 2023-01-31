#include "../include/enemy.h"

Enemy::Enemy(Map& maze, AssetsManager &assetsManager): Entity(maze, assetsManager){
	//Initialize the enemy
	init();
}

Enemy::~Enemy(){
}

//Initialization
void Enemy::init(){
	//Ennemy position
	positionX = 3;
	positionY = 3;

	goingRight = true;

	//Texture for the enemy
	assetsManager.loadTexture("enemy", "images/enemy.png");
	entity.setTexture(assetsManager.getTexture("enemy"));

	//Enemy animation
	rectSourceSpriteEntity.left = 0;
	rectSourceSpriteEntity.top = 0;
	rectSourceSpriteEntity.width = 60;
	rectSourceSpriteEntity.height = 60;
	entity.setTextureRect(rectSourceSpriteEntity);
}

//Update position
void Enemy::update(sf::Time dt){}
void Enemy::update(sf::Time dt, Player& player){

	///Needed to keep the same clock for the enemy (not moving too fast)
	//Enemy speed (pixels/s)
	static const float speed = 30.f;

	//Delay between 2 moves
	static const sf::Time moveDelay = sf::seconds(5.f / speed);

	//Last time player moved
	static sf::Time lastMove = sf::Time::Zero;
	lastMove += dt;

	if(lastMove >= moveDelay){
		if(positionX <= 11 && goingRight){
			positionX++;
		}
		if(positionX == 11){
			goingRight = false;
		}
		if(positionX >= 3 && !goingRight){
			positionX--;
		}
		if(positionX == 3){
			goingRight = true;
		}

		if( getHitBox().intersects(player.getHitBox()) ){
			std::cout << "DINO DIEEEDDD!!" << getHitBox().height << player.getHitBox().height << std::endl;
		}

		lastMove = sf::Time::Zero;
	}

	///Small animation of entity
	//Duration of the frame
	static float frameDuration = 0.4f;

	//Current time needed for the delta time
	static float currentTime = 0.0f;
	currentTime += dt.asSeconds();
	
	if(currentTime >= frameDuration){
		//Set rectangle left position
		if (rectSourceSpriteEntity.left == 60){
			rectSourceSpriteEntity.left = 0;
		}
		else{
			rectSourceSpriteEntity.left += 60;
		}

		currentTime = 0;

		std::cout << rectSourceSpriteEntity.left << std::endl;

		//Set the rectangle so we see the movement
		entity.setTextureRect(rectSourceSpriteEntity);
	}
}

//Draw
void Enemy::draw(sf::RenderTarget& target){
	entity.setPosition(positionX * maze.getBlockSize()+1, positionY * maze.getBlockSize()+1);

	//Draw the enemy
	target.draw(entity);
}