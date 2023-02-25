#include "../include/enemy.h"

// Initialization
void Enemy::initVariables()
{

	this->m_goingRight = true;
	this->lastMove = 0.f;

	this->m_moveAnimation.setParamsMovements(this->m_paramsMovement);
	this->m_moveAnimation.update(0.f);
}

Enemy::Enemy(int levelNum, Map &maze, AssetsManager &assetsManager, int posx, int posy, int direction, int min, int max, float speed) : Entity(maze, assetsManager), m_mapLevel(levelNum), m_directionEnemy(direction), m_minVal(min), m_maxVal(max), m_moveAnimation(60, "images/enemy.png", Animation::RIGHT, 4)
{
	// Initialize the enemy
	this->initVariables();
	this->setPositionX(posx);
	this->setPositionY(posy);
	this->setSpeed(speed);
}

Enemy::~Enemy()
{
}

void Enemy::setBehaviour(int directionMovement, int min, int max)
{
	this->m_directionEnemy = directionMovement;
	this->m_minVal = min;
	this->m_maxVal = max;
}

// Get MapLevel enemy
int Enemy::getMapLevel()
{
	return this->m_mapLevel;
}

// Update position
void Enemy::update(const float &dt) {}
void Enemy::update(const float &dt, Player &player)
{

	/// Needed to keep the same clock for the enemy (not moving too fast)
	// Delay between 2 moves
	static float moveDelay = (5.f / this->entitySpeed);

	// Last time player moved
	this->lastMove += dt;

	if (this->lastMove >= moveDelay)
	{
		this->lastMove = 0.f;
		if (this->m_directionEnemy == Enemy::HORIZONTAL)
		{

			if (this->positionX <= this->m_maxVal && this->m_goingRight)
			{
				this->m_moveAnimation.setDirection(Animation::RIGHT);
				this->positionX++;
				if (this->positionX == this->m_maxVal)
				{
					this->m_goingRight = false;
				}
			}
			if (this->positionX >= this->m_minVal && !this->m_goingRight)
			{
				this->m_moveAnimation.setDirection(Animation::LEFT);
				this->positionX--;
				if (this->positionX == this->m_minVal)
				{
					this->m_goingRight = true;
				}
			}
		}
		else if (this->m_directionEnemy == Enemy::VERTICAL)
		{

			if (this->positionY <= this->m_maxVal && this->m_goingDown)
			{
				this->m_moveAnimation.setDirection(Animation::DOWN);
				this->positionY++;
				if (this->positionY == this->m_maxVal)
				{
					this->m_goingDown = false;
				}
			}
			if (this->positionY >= this->m_minVal && !this->m_goingDown)
			{
				this->m_moveAnimation.setDirection(Animation::UP);
				this->positionY--;
				if (this->positionY == this->m_minVal)
				{
					this->m_goingDown = true;
				}
			}
		}

		// if( getHitBox().intersects(player.getHitBox()) ){
		// 	std::cout << "DINO DIEEEDDD!!" << std::to_string(getHitBox().left) << "=" << std::to_string(getHitBox().top) << " - " << std::to_string(player.getHitBox().left) << "=" << std::to_string(player.getHitBox().top) << std::endl;
		// }

		// Enemy hit player
		if (this->getHitBox().left == player.getHitBox().left && this->getHitBox().top == player.getHitBox().top)
		{
			player.justDie(false);
		}

		this->m_moveAnimation.update(dt);
	}
}

// Draw
void Enemy::draw(sf::RenderWindow *window)
{

	float blockSize = gui::scale(this->maze.getBlockSize(), window);

	// Draw the enemy
	this->m_moveAnimation.setPosition(this->positionX * blockSize + 1, this->positionY * blockSize + 1);
	this->m_moveAnimation.draw(window);
}