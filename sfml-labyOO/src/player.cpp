#include "../include/player.h"

void Player::initVariables()
{
	// Player position
	this->positionX = 1;
	this->positionY = 1;

	this->dead = false;

	/// Sounds
	// Movement sound
	this->assetsManager.loadSound("jump", "sounds/jump.ogg");
	this->sound = (this->assetsManager.getSound("jump"));
	this->sound.setVolume(10);

	// Hurt sound
	this->assetsManager.loadSound("hitHurt", "sounds/hitHurt.ogg");
	this->hurtSound = (this->assetsManager.getSound("hitHurt"));
	this->hurtSound.setVolume(100);
	this->trapEnabled = false;

	// Unlock sound
	this->assetsManager.loadSound("unlock", "sounds/unlock-sound.ogg");
	this->unlockSound = (this->assetsManager.getSound("unlock"));
	this->unlockSound.setVolume(50);
	this->unlockEnabled = false;

	// Exit level sound
	this->assetsManager.loadSound("exitlevel", "sounds/exitlevel.ogg");
	this->exitLevelSound = (this->assetsManager.getSound("exitlevel"));
	this->exitLevelSound.setVolume(30);
	this->nextLevelEnabled = false;

	this->exit = false;

	this->walkAnimation.setParamsMovements(this->paramsMovement);
}

Player::Player(Map &maze, AssetsManager &assetsManager) : Entity(maze, assetsManager), walkAnimation(60, "images/perso.png", 4, Animation::RIGHT, 4)
{
	// Initialize the player
	initVariables();
}

Player::~Player()
{
}

bool Player::getHasExited() const
{
	return this->exit;
}

void Player::justDie(bool newStatus)
{
	this->dead = newStatus;
}

bool Player::isDead() const
{
	return this->dead;
}

void Player::update(sf::Time dt)
{

	/// Needed to keep the same clock for the player (not moving too fast)
	// Player speed (pixels/s)
	static const float speed = 40.f;

	// Delay between 2 moves
	static const sf::Time moveDelay = sf::seconds(5.f / speed);

	// Last time player moved
	static sf::Time lastMove = sf::Time::Zero;
	lastMove += dt;

	// getHitBox().intersects(enemy.getHitBox());
	this->walkAnimation.update(dt);

	if (!this->dead)
	{
		// Handle movement of player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->walkAnimation.setDirection(Animation::UP);

			if (lastMove >= moveDelay)
			{
				if (this->maze.operator()(this->positionY - 1, this->positionX) != '#')
				{
					// std::cout << "Going up" << std::endl;
					this->positionY--;
					lastMove = sf::Time::Zero;
				}
				else
				{
					// std::cout << "Ouch" << std::endl;
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->walkAnimation.setDirection(Animation::DOWN);

			if (lastMove >= moveDelay)
			{
				if (this->maze.operator()(this->positionY + 1, this->positionX) != '#')
				{
					// std::cout << "Going down" << std::endl;
					this->positionY++;
					lastMove = sf::Time::Zero;
				}
				else
				{
					// std::cout << "Ouch" << std::endl;
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->walkAnimation.setDirection(Animation::LEFT);

			if (lastMove >= moveDelay)
			{
				if (this->maze.operator()(this->positionY, this->positionX - 1) != '#')
				{
					// std::cout << "Going left" << std::endl;
					this->positionX--;
					lastMove = sf::Time::Zero;
				}
				else
				{
					// std::cout << "Ouch" << std::endl;
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->walkAnimation.setDirection(Animation::RIGHT);

			if (lastMove >= moveDelay)
			{
				if (this->maze.operator()(this->positionY, this->positionX + 1) != '#')
				{
					// std::cout << "Going right" << std::endl;
					this->positionX++;
					lastMove = sf::Time::Zero;
				}
				else
				{
					// std::cout << "Ouch" << std::endl;
				}
			}
		}
	}

	if (this->maze.operator()(this->positionY, this->positionX) == 't' && this->trapEnabled != true)
	{
		this->hurtSound.play();

		if (this->maze.getLevel() == 2)
		{
			this->maze.operator()(8, 5) = '#';
			this->maze.operator()(13, 15) = 'k';
		}
		else if (this->maze.getLevel() == 3)
		{
			this->maze.operator()(1, 22) = '#';
			this->maze.operator()(13, 15) = 'k';
		}
		else if (this->maze.getLevel() == 4)
		{
			this->maze.operator()(19, 20) = '#';
			this->maze.operator()(10, 10) = 'k';
		}
		this->maze.operator()(this->positionY, this->positionX) = ' ';
		this->unlockEnabled = false;
		this->trapEnabled = true;
	}

	// If case is a key
	if (this->maze.operator()(this->positionY, this->positionX) == 'k' && this->unlockEnabled != true)
	{
		// Key disappear
		this->maze.operator()(this->positionY, this->positionX) = ' ';

		// Open the path
		if (this->maze.getLevel() == 1)
		{
			this->maze.operator()(16, 3) = ' ';
		}
		else if (this->maze.getLevel() == 2)
		{
			this->maze.operator()(5, 5) = ' ';
			this->maze.operator()(8, 5) = ' ';
		}
		else if (this->maze.getLevel() == 3)
		{
			this->maze.operator()(1, 22) = ' ';
		}
		else if (this->maze.getLevel() == 4)
		{
			this->maze.operator()(19, 20) = ' ';
		}
		else if (this->maze.getLevel() == 5)
		{
			this->maze.operator()(19, 2) = ' '; // access trophy
			this->maze.operator()(19, 20) = ' ';
		}
		this->unlockSound.play();

		std::cout << "Change content:" << this->maze.operator()(this->positionY, this->positionX) << this->positionY << this->positionX << ":P" << std::endl;
		this->unlockEnabled = true;
	}

	// Next level phase
	if (this->maze.operator()(this->positionY, this->positionX) == 'n' && this->nextLevelEnabled != true)
	{
		this->exitLevelSound.play();
		std::cout << "Next level!!" << std::endl;
		this->nextLevelEnabled = true;

		this->maze.setLevel(this->maze.getLevel() + 1);

		// Need to reset the sounds for the next level
		resetSounds();

		// Name of the maze level
		std::string name = "maze" + std::to_string(this->maze.getLevel());

		// Set new level
		this->maze.setNewMaze(this->maze.getMazeByName(name));

		this->positionX = 1;
		this->positionY = 1;
		this->entity.setPosition(this->positionX * this->maze.getBlockSize() + 1, this->positionY * this->maze.getBlockSize() + 1);
	}

	// Sound of the win for the exit
	if (this->maze.operator()(this->positionY, this->positionX) == 'e' && this->exit != true)
	{
		std::cout << "Exit!!" << std::endl;
		this->exit = true;
	}
}

void Player::resetSounds()
{
	// Reset unlock sound
	this->unlockEnabled = false;

	// Reset nextlevel sound
	this->nextLevelEnabled = false;

	// Reset trap sound
	this->trapEnabled = false;
}

void Player::draw(sf::RenderWindow *window)
{

	// Draw the player
	this->walkAnimation.setPosition(this->positionX * this->maze.getBlockSize() + 1, this->positionY * this->maze.getBlockSize() + 1);
	this->walkAnimation.draw(window);
}