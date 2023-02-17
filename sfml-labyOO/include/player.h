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

	// Get the number of lives of the player
	int getNbLives() const;
	void setNbLives(int nnbLives);

	// Update position
	void update(const float &dt) override;

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

	int nbLives;
	bool dead;
	bool exit;

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