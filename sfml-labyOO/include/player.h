#ifndef PLAYER_H
#define PLAYER_H

#include "stdHeader.h"
#include "map.h"
#include "assetsmanager.h"
#include "animation.h"
#include "entity.h"
#include "enemy.h"
#include "customStructures.h"

class Map;
class AssetsManager;
class Animation;
class Enemy;

class Player : public Entity
{
public:
	// Constructor and destructor
	Player(Map &maze, AssetsManager &assetsManager);
	~Player() final;

	static constexpr int PLAYER_SPEED = 2;
	static constexpr float PLAYER_ACCELERATION = 0.25f;
	static constexpr short INVINCIBILITY_DURATION = 128;
	static constexpr short BLINKING = 4;

	// Getter exit
	bool getHasExited() const;

	// Set death status
	void justDie(bool newStatus);

	// Check if player is dead
	bool isDead() const;

	// Get the number of lives of the player
	int getNbLives() const;
	void setNbLives(int nnbLives);

	// Update position
	void update(const float &dt) override;
	void update(const float &dt, std::vector<std::shared_ptr<Enemy>> enemies);

	// Reset sound memory for each level
	void resetSounds();

	// Draw
	void draw(sf::RenderWindow *window) override;

private:
	// Sounds
	sf::Sound trapSound;
	sf::Sound unlockSound;
	bool unlockEnabled;

	sf::Sound exitLevelSound;
	bool nextLevelEnabled;
	bool trapEnabled;

	// Sounds
	sf::Sound damageSound;
	sf::Sound deathSound;

	int nbLives;
	bool dead;
	bool exit;

	float speed;

	short invincibleTimer;

	/// Text to display the level number
	sf::Text text;
	// Select the font
	sf::Font font;

	Animation walkAnimation;

	// 0-60 down
	// 60-120 left
	// 120-180 right
	// 180-240 up
	ParamsMovement paramsMovement{
			120, // Right
			60,	 // Left
			180, // Up
			0		 // Down
	};

	// Initialization
	void initVariables() override;
};

#endif // PLAYER_H