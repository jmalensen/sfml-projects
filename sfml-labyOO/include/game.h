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
	GraphicsSettings gfxSettings;
	StateData stateData;

	sf::Clock dtClock;
	float dt;

	std::stack<State *> states;

	std::map<std::string, int> supportedKeys;

	// The windows for the render
	sf::RenderWindow *window;
	sf::VideoMode vm;
	sf::Event sfEvent;

	// Methods
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();
};

#endif // GAME_H