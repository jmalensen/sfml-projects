#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "stdHeader.h"
#include "state.h"
#include "pausemenu.h"
#include "endgamestate.h"
#include "gameoverstate.h"
#include "assetsmanager.h"
#include "map.h"
#include "player.h"
#include "enemy.h"

class AssetsManager;
class PauseMenu;
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
	void updateGuiSize(sf::Event sfEvent) override;
	void updateInput(const float &dt);
	void update(const float &dt);
	void draw(sf::RenderTarget *target = NULL);

private:
	sf::Music music;
	AssetsManager assetsManager;
	PauseMenu *pmenu;

	sf::Clock clock;
	sf::Time startTime;
	sf::Time pausedTime;
	sf::Font font;
	sf::Text timerText;

	// The map
	Map map;

	// The player
	Player player;

	// The enemies
	std::vector<std::shared_ptr<Enemy>> enemies;

	int getRandomNumber(int min, int max);

	// Functions
	void initVariables();
	void initKeybinds();
};

#endif