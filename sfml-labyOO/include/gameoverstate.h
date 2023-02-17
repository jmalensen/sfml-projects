#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "stdHeader.h"
#include "state.h"
#include "gamestate.h"
#include "assetsmanager.h"
#include "gui.h"

class AssetsManager;
class GameState;

class GameoverState : public State
{
public:
	GameoverState(StateData *stateData);
	virtual ~GameoverState();

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

	sf::Font font;
	std::map<std::string, gui::Button *> buttons;

	// Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
};

#endif