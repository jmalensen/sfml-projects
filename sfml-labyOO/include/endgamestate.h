#ifndef ENDGAMESTATE_H
#define ENDGAMESTATE_H

#include "stdHeader.h"
#include "state.h"
#include "gamestate.h"
#include "assetsmanager.h"
#include "gui.h"

class AssetsManager;
class GameState;

class EndGameState : public State
{
public:
	EndGameState(StateData *stateData);
	virtual ~EndGameState();

	// Functions
	void updateInput(const float &dt);
	void updateGui(const float &dt);
	void update(const float &dt);
	void drawGui(sf::RenderTarget &target);
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

	sf::Font font;
	std::map<std::string, gui::Button *> buttons;
	sf::Text timerText;

	// Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
};

#endif