#include "../include/enemy.h"

Enemy::Enemy(int id, Map &maze, AssetsManager &assetsManager, int posx, int posy, int direction, int min, int max, float speed) : Entity(maze, assetsManager), idEnemy(id), directionEnemy(direction), minVal(min), maxVal(max), moveAnimation(60, "images/enemy.png", 4, Animation::RIGHT, 4)
{
	// Initialize the enemy
	init();
	setPositionX(posx);
	setPositionY(posy);
	setSpeed(speed);
}

Enemy::~Enemy()
{
}

// Initialization
void Enemy::init()
{

	this->goingRight = true;

	// Hurt sound
	this->assetsManager.loadSound("dead", "sounds/dead.ogg");
	this->hurtSound = (this->assetsManager.getSound("dead"));
	this->hurtSound.setVolume(10);

	this->moveAnimation.setParamsMovements(this->paramsMovement);
}

void Enemy::setBehaviour(int directionMovement, int min, int max)
{
	this->directionEnemy = directionMovement;
	this->minVal = min;
	this->maxVal = max;
}

// Update position
void Enemy::update(sf::Time dt) {}
void Enemy::update(sf::Time dt, Player &player)
{

	/// Needed to keep the same clock for the enemy (not moving too fast)
	// Enemy speed (pixels/s)
	// entitySpeed

	// Delay between 2 moves
	static const sf::Time moveDelay = sf::seconds(5.f / this->entitySpeed);

	// Last time player moved
	static sf::Time lastMove = sf::Time::Zero;
	lastMove += dt;

	if (lastMove >= moveDelay)
	{

		if (this->directionEnemy == Enemy::HORIZONTAL)
		{

			if (this->positionX <= this->maxVal && this->goingRight)
			{
				this->moveAnimation.setDirection(Animation::RIGHT);
				this->positionX++;
				if (this->positionX == this->maxVal)
				{
					this->goingRight = false;
				}
			}
			if (this->positionX >= this->minVal && !this->goingRight)
			{
				this->moveAnimation.setDirection(Animation::LEFT);
				this->positionX--;
				if (this->positionX == this->minVal)
				{
					this->goingRight = true;
				}
			}
		}
		else if (this->directionEnemy == Enemy::VERTICAL)
		{

			if (this->positionY <= this->maxVal && this->goingDown)
			{
				this->moveAnimation.setDirection(Animation::DOWN);
				this->positionY++;
				if (this->positionY == this->maxVal)
				{
					this->goingDown = false;
				}
			}
			if (this->positionY >= this->minVal && !this->goingDown)
			{
				this->moveAnimation.setDirection(Animation::UP);
				this->positionY--;
				if (this->positionY == this->minVal)
				{
					this->goingDown = true;
				}
			}
		}

		// if( getHitBox().intersects(player.getHitBox()) ){
		// 	std::cout << "DINO DIEEEDDD!!" << std::to_string(getHitBox().left) << "=" << std::to_string(getHitBox().top) << " - " << std::to_string(player.getHitBox().left) << "=" << std::to_string(player.getHitBox().top) << std::endl;
		// }

		// Enemy hit player
		if (getHitBox().left == player.getHitBox().left && getHitBox().top == player.getHitBox().top)
		{
			std::cout << "You DIEEEDDD!!" << std::endl;
			this->hurtSound.play();
			player.justDie(true);
		}

		this->moveAnimation.update(dt);

		lastMove = sf::Time::Zero;
	}
}

// Draw
void Enemy::draw(sf::RenderWindow &window)
{

	// Draw the enemy
	this->moveAnimation.setPosition(this->positionX * this->maze.getBlockSize() + 1, this->positionY * this->maze.getBlockSize() + 1);
	this->moveAnimation.draw(window);
}