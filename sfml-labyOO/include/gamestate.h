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
	sf::Music m_music;
	AssetsManager m_assetsManager;
	PauseMenu *m_p_pmenu;

	sf::Clock m_clock;
	sf::Time m_startTime;
	sf::Time m_pausedTime;
	sf::Font m_font;
	sf::Text m_timerText;

	// The map
	Map m_map;

	// The player
	Player m_player;

	// The enemies
	std::vector<std::shared_ptr<Enemy>> m_enemies;

	int getRandomNumber(int min, int max);

	// Functions
	void initVariables();
	void initKeybinds();
};

#endif