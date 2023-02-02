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

	//Hurt sound
	assetsManager.loadSound("dead", "sounds/dead.ogg");
	hurtSound = (assetsManager.getSound("dead"));
	hurtSound.setVolume(10);
}

void Enemy::setBehaviour(int directionMovement, int min, int max){
	if(directionMovement == Enemy::HORIZONTAL){
		isMovingHorizontal = true;
	}
	else{
		isMovingHorizontal = false;
	}

	minVal = min;
	maxVal = max;
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

		if(isMovingHorizontal){
			// std::cout << "Enemy going horizontal!! " << std::to_string(goingRight) << "-" << std::to_string(positionX) << "-" << std::to_string(minVal) << "-" << std::to_string(maxVal) << std::endl;

			if(positionX <= maxVal && goingRight){
				positionX++;
				if(positionX == maxVal){
					goingRight = false;
				}
			}
			if(positionX >= minVal && !goingRight){
				positionX--;
				if(positionX == minVal){
					goingRight = true;
				}
			}
		}
		else{
			// std::cout << "Enemy going vertical!! " << std::to_string(goingDown) << "-" << std::to_string(positionY) << "-" << std::to_string(minVal) << "-" << std::to_string(maxVal) << std::endl;

			if(positionY <= maxVal && goingDown){
				positionY++;
				if(positionY == maxVal){
					goingDown = false;
				}
			}
			if(positionY >= minVal && !goingDown){
				positionY--;
				if(positionY == minVal){
					goingDown = true;
				}
			}
		}

		// if( getHitBox().intersects(player.getHitBox()) ){
		// 	std::cout << "DINO DIEEEDDD!!" << std::to_string(getHitBox().left) << "=" << std::to_string(getHitBox().top) << " - " << std::to_string(player.getHitBox().left) << "=" << std::to_string(player.getHitBox().top) << std::endl;
		// }

		if( getHitBox().left == player.getHitBox().left && getHitBox().top == player.getHitBox().top ){
			std::cout << "DINO DIEEEDDD!!" << std::endl;
			hurtSound.play();
			player.justDie(true);
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