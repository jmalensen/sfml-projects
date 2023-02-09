#ifndef GAME_H
#define GAME_H

#include "stdHeader.h"
#include "graphicssettings.h"
#include "state.h"
#include "assetsmanager.h"
#include "screensmanager.h"

class GraphicsSettings;
class AssetsManager;
class ScreensManager;

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
	AssetsManager assetsManager;
	sf::Music music;

	sf::Clock dtClock;
	float dt;

	std::stack<State *> states;

	// The windows for the render
	sf::RenderWindow *window;
	sf::VideoMode vm;
	sf::Event sfEvent;

	// The screenmanager
	ScreensManager screensManager = ScreensManager(assetsManager);

	// Methods
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initStates();
};

#endif // GAME_H