#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "stdHeader.h"
#include "state.h"
#include "assetsmanager.h"
#include "screensmanager.h"

class AssetsManager;
class ScreensManager;

class GameState : public State
{
public:
	GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
	virtual ~GameState();

	// Functions
	void updateInput(const float &dt);
	void update(const float &dt);
	void draw(sf::RenderTarget *target = NULL);

private:
	AssetsManager assetsManager;
	// The screenmanager
	ScreensManager screensManager = ScreensManager(assetsManager);

	// Functions
	void initKeybinds();
};

#endif