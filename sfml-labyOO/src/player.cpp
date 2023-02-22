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

	// Damage sound
	this->assetsManager.loadSound("damage", "sounds/damage.ogg");
	this->damageSound = (this->assetsManager.getSound("damage"));
	this->damageSound.setVolume(100);

	// Death sound
	this->assetsManager.loadSound("dead", "sounds/dead.ogg");
	this->deathSound = (this->assetsManager.getSound("dead"));
	this->deathSound.setVolume(15);

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

Player::Player(Map &maze, AssetsManager &assetsManager) : Entity(maze, assetsManager), walkAnimation(60, "images/perso.png", Animation::RIGHT, 4), nbLives(3), speed(0), invincibleTimer(0)
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

void Player::justDie(bool instantDeath)
{
	// If instant death, you just die
	this->dead = instantDeath;

	if (this->getNbLives() == 0 && this->invincibleTimer == 0)
	{
		std::cout << "You DIEEEDDD!!" << std::endl;
		this->deathSound.play();
		this->dead = true;
	}
	else if (this->getNbLives() > 0 && this->invincibleTimer == 0)
	{
		// std::cout << "Damage by enemy!!" << std::endl;
		this->damageSound.play();
		this->setNbLives(this->getNbLives() - 1);
		this->invincibleTimer = INVINCIBILITY_DURATION;
	}
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

void Player::update(const float &dt) {}
void Player::update(const float &dt, std::vector<std::shared_ptr<Enemy>> enemies)
{

	/// Needed to keep the same clock for the player (not moving too fast)
	// Delay between 2 moves
	static float moveDelay = 0.2f; //(5.f / speed);

	// Last time player moved
	this->lastMove += dt;

	// getHitBox().intersects(enemy.getHitBox());
	this->walkAnimation.update(dt);

	// The base player speed (in pixels per second)
	static const float BASE_SPEED = 60.0f;

	// The maximum speed that the player can achieve (in pixels per second)
	static const float MAX_SPEED = 80.0f;

	// The acceleration of the player (in pixels per second squared)
	static const float ACCELERATION = 100.0f;

	// The deceleration of the player (in pixels per second squared)
	static const float DECELERATION = 200.0f;

	// The minimum delay between two moves (in seconds)
	static const float MIN_MOVE_DELAY = 0.2f;

	// The current player speed (in pixels per second)
	float speed = BASE_SPEED;

	// Update the move delay based on the current player speed
	moveDelay = 2.0f / speed;

	if (!this->dead)
	{
		if (this->lastMove >= moveDelay)
		{

			// Handle acceleration and deceleration
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				speed += ACCELERATION * dt;
				speed = std::min(speed, MAX_SPEED);
			}
			else
			{
				speed -= DECELERATION * dt;
				speed = std::max(speed, BASE_SPEED);
			}

			// Handle movement in the x and y axis
			float moveAmount = speed * dt;
			sf::Vector2i moveDirection(0, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				this->walkAnimation.setDirection(Animation::UP);
				moveDirection = sf::Vector2i(0, -1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				this->walkAnimation.setDirection(Animation::DOWN);
				moveDirection = sf::Vector2i(0, 1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				this->walkAnimation.setDirection(Animation::LEFT);
				moveDirection = sf::Vector2i(-1, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				this->walkAnimation.setDirection(Animation::RIGHT);
				moveDirection = sf::Vector2i(1, 0);
			}

			// Normalize the move direction to ensure that diagonal movement is not faster than horizontal or vertical movement
			if (moveDirection != sf::Vector2i(0, 0))
			{
				moveDirection = moveDirection / std::max(std::abs(moveDirection.x), std::abs(moveDirection.y));
			}

			// Move the player by the required amount
			sf::Vector2i newPosition = sf::Vector2i(positionX, positionY) + moveDirection * static_cast<int>(moveAmount);
			if (maze.operator()(newPosition.y, newPosition.x) != '#')
			{
				positionX = newPosition.x;
				positionY = newPosition.y;
			}

			// Reset last move
			this->lastMove = 0.f;
		}

		// Invicibility countdown if exists
		if (this->invincibleTimer > 0)
		{
			this->invincibleTimer--;
		}

		// Check hitboxes enemies depending on levels
		for (short a = 0; a < enemies.size(); a++)
		{
			// Check level where enemy is displayed
			int mapLevelEnemy = enemies[a]->getMapLevel();
			if (this->maze.getLevel() == mapLevelEnemy)
			{

				if (this->getHitBox().left == enemies[a]->getHitBox().left && this->getHitBox().top == enemies[a]->getHitBox().top)
				{
					this->justDie(false);

					break;
				}
			}
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

			// std::cout << "Change content:" << this->maze.operator()(this->positionY, this->positionX) << this->positionY << this->positionX << ":P" << std::endl;
			this->unlockEnabled = true;
		}

		// Next level phase
		if (this->maze.operator()(this->positionY, this->positionX) == 'n' && this->nextLevelEnabled != true)
		{
			this->exitLevelSound.play();
			// std::cout << "Next level!!" << std::endl;
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

	// When player is invincible, his sprite will blink.
	if ((invincibleTimer / BLINKING % 2) == 0)
	{
		this->walkAnimation.draw(window);
	}

	// Draw the text
	this->text.setPosition(170, 10);
	window->draw(this->text);
}