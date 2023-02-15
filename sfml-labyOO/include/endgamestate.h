#ifndef ENDGAMESTATE_H
#define ENDGAMESTATE_H

#include "stdHeader.h"
#include "state.h"
#include "assetsmanager.h"

class AssetsManager;

class EndGameState : public State
{
public:
	EndGameState(StateData *stateData);
	virtual ~EndGameState();

	// Functions
	void updateInput(const float &dt);
	void update(const float &dt);
	void draw(sf::RenderTarget *target = NULL);

private:
	// Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	AssetsManager assetsManager;

	// Victory sound
	float lastMove;
	sf::Sound winSound;
	bool playedWinSound;

	// Functions
	void initVariables();
	void initKeybinds();
};

#endif