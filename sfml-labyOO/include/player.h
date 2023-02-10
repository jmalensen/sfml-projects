#ifndef PLAYER_H
#define PLAYER_H

#include "stdHeader.h"
#include "map.h"
#include "assetsmanager.h"
#include "animation.h"
#include "entity.h"
#include "customStructures.h"

class Map;
class AssetsManager;
class Animation;

class Player : public Entity
{
public:
	// Constructor and destructor
	Player(Map &maze, AssetsManager &assetsManager);
	~Player() final;

	// Getter exit
	bool getHasExited() const;

	// Set death status
	void justDie(bool newStatus);

	// Check if player is dead
	bool isDead() const;

	// Update position
	void update(sf::Time dt) override;

	// Reset sound memory for each level
	void resetSounds();

	// Draw
	void draw(sf::RenderWindow *window) override;

private:
	// Sounds
	sf::Sound sound;
	sf::Sound hurtSound;
	sf::Sound unlockSound;
	bool unlockEnabled;

	sf::Sound exitLevelSound;
	bool nextLevelEnabled;
	bool trapEnabled;

	bool dead;
	bool exit;

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