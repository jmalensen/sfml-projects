#include "../include/player.h"

void Player::initVariables()
{
	// Player position
	this->positionX = 1;
	this->positionY = 1;

	this->m_dead = false;

	this->lastMove = 0.f;

	/// Sounds
	// Trap sound
	this->assetsManager.loadSound("trap", "sounds/trap.ogg");
	this->m_trapSound = (this->assetsManager.getSound("trap"));
	this->m_trapSound.setVolume(100);
	this->m_trapEnabled = false;

	// Unlock sound
	this->assetsManager.loadSound("unlock", "sounds/unlock-sound.ogg");
	this->m_unlockSound = (this->assetsManager.getSound("unlock"));
	this->m_unlockSound.setVolume(50);
	this->m_unlockEnabled = false;

	// Exit level sound
	this->assetsManager.loadSound("exitlevel", "sounds/exitlevel.ogg");
	this->m_exitLevelSound = (this->assetsManager.getSound("exitlevel"));
	this->m_exitLevelSound.setVolume(30);
	this->m_nextLevelEnabled = false;

	// Damage sound
	this->assetsManager.loadSound("damage", "sounds/damage.ogg");
	this->m_damageSound = (this->assetsManager.getSound("damage"));
	this->m_damageSound.setVolume(100);

	// Death sound
	this->assetsManager.loadSound("dead", "sounds/dead.ogg");
	this->m_deathSound = (this->assetsManager.getSound("dead"));
	this->m_deathSound.setVolume(15);

	this->m_exit = false;

	this->m_walkAnimation.setParamsMovements(this->m_paramsMovement);
	this->m_walkAnimation.update(0.f);

	// Text to display the number of lives of the player
	this->assetsManager.loadFont("arial", "fonts/arial.ttf");
	this->m_text.setFont(this->assetsManager.getFont("arial"));

	// Set the string to display
	this->m_text.setString("Nb lives: " + std::to_string(this->m_nbLives));

	// Set the character size (in pixels, not points)
	this->m_text.setCharacterSize(36);

	// Set the text style
	this->m_text.setStyle(sf::Text::Bold);

	// Set the color
	this->m_text.setFillColor(sf::Color::White);
}

Player::Player(Map &maze, AssetsManager &assetsManager) : Entity(maze, assetsManager), m_walkAnimation(60, "images/perso.png", Animation::RIGHT, 4), m_nbLives(3), m_speed(0), m_invincibleTimer(0)
{
	// Initialize the player
	this->initVariables();
}

Player::~Player()
{
}

bool Player::getHasExited() const
{
	return this->m_exit;
}

void Player::justDie(bool instantDeath)
{
	// If instant death, you just die
	this->m_dead = instantDeath;

	if (this->getNbLives() == 0 && this->m_invincibleTimer == 0)
	{
		std::cout << "You DIEEEDDD!!" << std::endl;
		this->m_deathSound.play();
		this->m_dead = true;
	}
	else if (this->getNbLives() > 0 && this->m_invincibleTimer == 0)
	{
		// std::cout << "Damage by enemy!!" << std::endl;
		this->m_damageSound.play();
		this->setNbLives(this->getNbLives() - 1);
		this->m_invincibleTimer = INVINCIBILITY_DURATION;
	}
}

bool Player::isDead() const
{
	return this->m_dead;
}

int Player::getNbLives() const
{
	return this->m_nbLives;
}

void Player::setNbLives(int nnbLives)
{
	this->m_nbLives = nnbLives;

	// Set the string to display when m_nbLives  change
	this->m_text.setString("Nb lives: " + std::to_string(this->m_nbLives));
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
	this->m_walkAnimation.update(dt);

	// The base player speed (in pixels per second)
	static const float BASE_SPEED = 60.0f;

	// The maximum speed that the player can achieve (in pixels per second)
	// static const float MAX_SPEED = 80.0f;

	// The acceleration of the player (in pixels per second squared)
	// static const float ACCELERATION = 100.0f;

	// The deceleration of the player (in pixels per second squared)
	// static const float DECELERATION = 200.0f;

	// The minimum delay between two moves (in seconds)
	// static const float MIN_MOVE_DELAY = 0.2f;

	// The current player speed (in pixels per second)
	float speed = BASE_SPEED;

	// Update the move delay based on the current player speed
	moveDelay = 3.0f / speed;

	if (!this->m_dead)
	{
		if (this->lastMove >= moveDelay)
		{

			// Handle acceleration and deceleration
			// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			// {
			// 	speed += ACCELERATION * dt;
			// 	speed = std::min(speed, MAX_SPEED);
			// }
			// else
			// {
			// 	speed -= DECELERATION * dt;
			// 	speed = std::max(speed, BASE_SPEED);
			// }

			// Handle movement in the x and y axis
			// float moveAmount = speed * dt;
			sf::Vector2i moveDirection(0, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				this->m_walkAnimation.setDirection(Animation::UP);
				moveDirection = sf::Vector2i(0, -1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				this->m_walkAnimation.setDirection(Animation::DOWN);
				moveDirection = sf::Vector2i(0, 1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				this->m_walkAnimation.setDirection(Animation::LEFT);
				moveDirection = sf::Vector2i(-1, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				this->m_walkAnimation.setDirection(Animation::RIGHT);
				moveDirection = sf::Vector2i(1, 0);
			}

			// Normalize the move direction to ensure that diagonal movement is not faster than horizontal or vertical movement
			if (moveDirection != sf::Vector2i(0, 0))
			{
				moveDirection = moveDirection / std::max(std::abs(moveDirection.x), std::abs(moveDirection.y));
			}

			// Move the player by the required amount
			sf::Vector2i newPosition = sf::Vector2i(positionX, positionY) + moveDirection; //*static_cast<int>(moveAmount);
			if (maze.operator()(newPosition.y, newPosition.x) != '#')
			{
				positionX = newPosition.x;
				positionY = newPosition.y;
			}

			// Reset last move
			this->lastMove = 0.f;
		}

		// Invicibility countdown if exists
		if (this->m_invincibleTimer > 0)
		{
			this->m_invincibleTimer--;
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

		if (this->maze.operator()(this->positionY, this->positionX) == 't' && this->m_trapEnabled != true)
		{
			this->m_trapSound.play();

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
			this->m_unlockEnabled = false;
			this->m_trapEnabled = true;
		}

		// If case is a key
		if (this->maze.operator()(this->positionY, this->positionX) == 'k' && this->m_unlockEnabled != true)
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
			this->m_unlockSound.play();

			// std::cout << "Change content:" << this->maze.operator()(this->positionY, this->positionX) << this->positionY << this->positionX << ":P" << std::endl;
			this->m_unlockEnabled = true;
		}

		// Next level phase
		if (this->maze.operator()(this->positionY, this->positionX) == 'n' && this->m_nextLevelEnabled != true)
		{
			this->m_exitLevelSound.play();
			// std::cout << "Next level!!" << std::endl;
			this->m_nextLevelEnabled = true;

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
		if (this->maze.operator()(this->positionY, this->positionX) == 'e' && this->m_exit != true)
		{
			std::cout << "Exit!!" << std::endl;
			this->m_exit = true;
		}
	}
}

void Player::resetSounds()
{
	// Reset unlock sound
	this->m_unlockEnabled = false;

	// Reset nextlevel sound
	this->m_nextLevelEnabled = false;

	// Reset trap sound
	this->m_trapEnabled = false;
}

void Player::draw(sf::RenderWindow *window)
{
	float blockSize = gui::scale(this->maze.getBlockSize(), window);

	// Draw the player
	this->m_walkAnimation.setPosition(this->positionX * blockSize + 1, this->positionY * blockSize + 1);

	// When player is invincible, his sprite will blink.
	if ((this->m_invincibleTimer / BLINKING % 2) == 0)
	{
		this->m_walkAnimation.draw(window);
	}

	// Draw the text
	this->m_text.setPosition(170, 10);
	window->draw(this->m_text);
}