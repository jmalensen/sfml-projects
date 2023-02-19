#ifndef ENEMY_H
#define ENEMY_H

#include "stdHeader.h"
#include "map.h"
#include "assetsmanager.h"
#include "animation.h"
#include "entity.h"
#include "player.h"
#include "customStructures.h"

class Map;
class AssetsManager;
class Player;
class Animation;

class Enemy : public Entity
{
public:
	// Constructor and destructor
	Enemy(int levelNum, Map &maze, AssetsManager &assetsManager, int posx, int posy, int direction, int min, int max, float speed);
	~Enemy() final;

	// Update position
	void update(const float &dt) override;
	void update(const float &dt, Player &player);

	// Draw
	void draw(sf::RenderWindow *window) override;

	// Set direction of enemy
	void setBehaviour(int directionMovement, int min, int max);

	// Get MapLevel enemy
	int getMapLevel();

	static constexpr int HORIZONTAL = 1;
	static constexpr int VERTICAL = 2;

private:
	int mapLevel;
	int directionEnemy;
	bool goingRight;
	bool goingDown;
	int minVal;
	int maxVal;

	Animation moveAnimation;

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

#endif // ENEMY_H