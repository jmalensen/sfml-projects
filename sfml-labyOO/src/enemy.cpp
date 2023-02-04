#include "../include/enemy.h"

Enemy::Enemy(int id, Map& maze, AssetsManager &assetsManager, int posx, int posy, int direction, int min, int max, float speed): Entity(maze, assetsManager), idEnemy(id), directionEnemy(direction), minVal(min), maxVal(max), moveAnimation(60, "images/enemy.png", 4, Animation::RIGHT, 4){
	//Initialize the enemy
	init();
	setPositionX(posx);
	setPositionY(posy);
	setSpeed(speed);
}

Enemy::~Enemy(){
}

//Initialization
void Enemy::init(){

	goingRight = true;

	//Hurt sound
	assetsManager.loadSound("dead", "sounds/dead.ogg");
	hurtSound = (assetsManager.getSound("dead"));
	hurtSound.setVolume(10);

	moveAnimation.setParamsMovements(paramsMovement);
}

void Enemy::setBehaviour(int directionMovement, int min, int max){
	directionEnemy = directionMovement;
	minVal = min;
	maxVal = max;
}

//Update position
void Enemy::update(sf::Time dt){}
void Enemy::update(sf::Time dt, Player& player){

	///Needed to keep the same clock for the enemy (not moving too fast)
	//Enemy speed (pixels/s)
	//entitySpeed

	//Delay between 2 moves
	static const sf::Time moveDelay = sf::seconds(5.f / entitySpeed);

	//Last time player moved
	static sf::Time lastMove = sf::Time::Zero;
	lastMove += dt;

	if(lastMove >= moveDelay){

		if(directionEnemy == Enemy::HORIZONTAL){

			if(positionX <= maxVal && goingRight){
				moveAnimation.setDirection(Animation::RIGHT);
				positionX++;
				if(positionX == maxVal){
					goingRight = false;
				}
			}
			if(positionX >= minVal && !goingRight){
				moveAnimation.setDirection(Animation::LEFT);
				positionX--;
				if(positionX == minVal){
					goingRight = true;
				}
			}
		}
		else if(directionEnemy == Enemy::VERTICAL){

			if(positionY <= maxVal && goingDown){
				moveAnimation.setDirection(Animation::DOWN);
				positionY++;
				if(positionY == maxVal){
					goingDown = false;
				}
			}
			if(positionY >= minVal && !goingDown){
				moveAnimation.setDirection(Animation::UP);
				positionY--;
				if(positionY == minVal){
					goingDown = true;
				}
			}
		}

		// if( getHitBox().intersects(player.getHitBox()) ){
		// 	std::cout << "DINO DIEEEDDD!!" << std::to_string(getHitBox().left) << "=" << std::to_string(getHitBox().top) << " - " << std::to_string(player.getHitBox().left) << "=" << std::to_string(player.getHitBox().top) << std::endl;
		// }

		//Enemy hit player
		if( getHitBox().left == player.getHitBox().left && getHitBox().top == player.getHitBox().top ){
			std::cout << "You DIEEEDDD!!" << std::endl;
			hurtSound.play();
			player.justDie(true);
		}

		moveAnimation.update(dt);

		lastMove = sf::Time::Zero;
	}
}

//Draw
void Enemy::draw(sf::RenderWindow& window){

	// //Draw the enemy
	moveAnimation.setPosition(positionX * maze.getBlockSize()+1, positionY * maze.getBlockSize()+1);
	moveAnimation.draw(window);
}