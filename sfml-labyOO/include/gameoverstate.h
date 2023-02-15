#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "stdHeader.h"
#include "state.h"
#include "assetsmanager.h"

class AssetsManager;

class GameoverState : public State
{
public:
	GameoverState(StateData *stateData);
	virtual ~GameoverState();

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