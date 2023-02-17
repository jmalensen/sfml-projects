#include "../include/player.h"

void Player::initVariables()
{
	// Player position
	this->positionX = 1;
	this->positionY = 1;

	this->dead = false;

	this->lastMove = 0.f;

	/// Sounds
	// Trap sound
	this->assetsManager.loadSound("trap", "sounds/trap.ogg");
	this->trapSound = (this->assetsManager.getSound("trap"));
	this->trapSound.setVolume(100);
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
	this->walkAnimation.update(0.f);

	// Text to display the number of lives of the player
	this->assetsManager.loadFont("arial", "fonts/arial.ttf");
	this->text.setFont(this->assetsManager.getFont("arial"));

	// Set the string to display
	this->text.setString("Nb lives: " + std::to_string(this->nbLives));

	// Set the character size (in pixels, not points)
	this->text.setCharacterSize(36);

	// Set the text style
	this->text.setStyle(sf::Text::Bold);

	// Set the color
	this->text.setFillColor(sf::Color::White);
}

Player::Player(Map &maze, AssetsManager &assetsManager) : Entity(maze, assetsManager), walkAnimation(60, "images/perso.png", Animation::RIGHT, 4), nbLives(3), speed(0)
{
	// Initialize the player
	this->initVariables();
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

int Player::getNbLives() const
{
	return this->nbLives;
}

void Player::setNbLives(int nnbLives)
{
	this->nbLives = nnbLives;

	// Set the string to display when nbLives  change
	this->text.setString("Nb lives: " + std::to_string(this->nbLives));
}

void Player::update(const float &dt)
{

	/// Needed to keep the same clock for the player (not moving too fast)
	// Delay between 2 moves
	static float moveDelay = 0.2f; //(5.f / speed);

	// Last time player moved
	this->lastMove += dt;

	// getHitBox().intersects(enemy.getHitBox());
	this->walkAnimation.update(dt);

	if (!this->dead)
	{
		// Handle movement of player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->walkAnimation.setDirection(Animation::UP);

			if (this->lastMove >= moveDelay)
			{
				if (this->maze.operator()(this->positionY - 1, this->positionX) != '#')
				{
					// std::cout << "Going up" << std::endl;
					this->positionY--;
					this->lastMove = 0;
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

			if (this->lastMove >= moveDelay)
			{
				if (this->maze.operator()(this->positionY + 1, this->positionX) != '#')
				{
					// std::cout << "Going down" << std::endl;
					this->positionY++;
					this->lastMove = 0;
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

			if (this->lastMove >= moveDelay)
			{
				if (this->maze.operator()(this->positionY, this->positionX - 1) != '#')
				{
					// std::cout << "Going left" << std::endl;
					this->positionX--;
					this->lastMove = 0;
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

			// std::cout << "Right player: " << std::to_string(lastMove >= moveDelay) << " " << lastMove << " " << moveDelay << " " << dt << std::endl;

			if (this->lastMove >= moveDelay)
			{
				if (this->maze.operator()(this->positionY, this->positionX + 1) != '#')
				{
					// std::cout << "Going right" << std::endl;
					this->positionX++;
					this->lastMove = 0;
				}
				else
				{
					// std::cout << "Ouch" << std::endl;
				}
			}
		}

		// check hitboxes enemies depending on levels
	}

	if (this->maze.operator()(this->positionY, this->positionX) == 't' && this->trapEnabled != true)
	{
		this->trapSound.play();

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
			this->maze.operator()(13, 3) = '#';
			this->maze.operator()(14, 12) = 'k';
		}
		else if (this->maze.getLevel() == 5)
		{
			this->maze.operator()(14, 29) = ' '; // remove trophy
			this->maze.operator()(14, 8) = 'e';
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
			this->maze.operator()(13, 4) = ' ';
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
			this->maze.operator()(13, 3) = ' ';
		}
		else if (this->maze.getLevel() == 5)
		{
			this->maze.operator()(14, 27) = ' ';
			this->maze.operator()(14, 28) = ' ';
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
		this->resetSounds();

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
	float blockSize = gui::scale(this->maze.getBlockSize(), window);

	// Draw the player
	this->walkAnimation.setPosition(this->positionX * blockSize + 1, this->positionY * blockSize + 1);
	this->walkAnimation.draw(window);

	// Draw the text
	this->text.setPosition(170, 10);
	window->draw(this->text);
}