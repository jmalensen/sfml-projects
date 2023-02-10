#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "stdHeader.h"
#include "gamestate.h"
#include "settingsstate.h"
#include "gui.h"

class MainMenuState : public State
{
public:
	MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
	virtual ~MainMenuState();

	// Functions
	void updateInput(const float &dt);
	void updateButtons();
	void update(const float &dt);
	void drawButtons(sf::RenderTarget &target);
	void draw(sf::RenderTarget *target = NULL);

private:
	// Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button *> buttons;

	// Functions
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
};

#endif