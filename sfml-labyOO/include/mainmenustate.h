#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "stdHeader.h"
#include "settingsstate.h"
#include "gamestate.h"
#include "gui.h"

class GameState;

class MainMenuState : public State
{
public:
	MainMenuState(StateData *stateData);
	virtual ~MainMenuState();

	// Functions
	void updateInput(const float &dt);
	void updateButtons();
	void update(const float &dt);
	void drawButtons(sf::RenderTarget &target);
	void draw(sf::RenderTarget *target = NULL);

private:
	// Variables
	sf::Music music;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button *> buttons;

	// Functions
	void initGui();
	void resetGui();
	void initFonts();
	void initKeybinds();
};

#endif