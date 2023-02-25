#ifndef GAME_H
#define GAME_H

#include "stdHeader.h"
#include "graphicssettings.h"
#include "state.h"
#include "mainmenustate.h"

class GraphicsSettings;
class MainMenuState;

class Game
{
public:
	// Constructor and destructor
	Game();
	~Game();

	// Methods
	void endApplication();

	// Update the game
	void updateDt();
	void updateSFMLEvents();
	void update();

	// Draw
	void draw();

	// Run the game
	void run();

private:
	// Variables
	GraphicsSettings m_gfxSettings;
	StateData m_stateData;

	sf::Clock m_dtClock;
	float m_dt;

	std::stack<State *> m_states;

	std::map<std::string, int> m_supportedKeys;

	// The windows for the render
	sf::RenderWindow *m_p_window;
	sf::Event m_sfEvent;

	// Methods
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();
};

#endif // GAME_H