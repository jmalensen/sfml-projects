#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "stdHeader.h"
#include "state.h"
#include "menustate.h"
#include "endgamestate.h"
#include "gameoverstate.h"
#include "assetsmanager.h"
#include "map.h"
#include "player.h"
#include "enemy.h"

class AssetsManager;
class MenuState;
class EndGameState;
class GameoverState;
class Map;
class Player;
class Enemy;

class GameState : public State
{
public:
	GameState(StateData *stateData);
	virtual ~GameState();

	// Functions
	void updateInput(const float &dt);
	void update(const float &dt);
	void draw(sf::RenderTarget *target = NULL);

private:
	AssetsManager assetsManager;

	// The map
	Map map;

	// The player
	Player player;

	// The enemies
	std::vector<std::shared_ptr<Enemy>> enemies;

	// Functions
	void initVariables();
	void initKeybinds();
};

#endif