#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "stdHeader.h"
#include "state.h"
#include "gamestate.h"
#include "assetsmanager.h"

class AssetsManager;
class GameState;

class MenuState : public State
{
public:
	MenuState(StateData *stateData);
	virtual ~MenuState();

	// Functions
	void updateInput(const float &dt);
	void update(const float &dt);
	void draw(sf::RenderTarget *target = NULL);

private:
	// Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	AssetsManager assetsManager;

	// Functions
	void initVariables();
	void initKeybinds();
};

#endif