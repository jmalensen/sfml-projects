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
	sf::Music m_music;
	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;
	sf::Font m_font;

	std::map<std::string, gui::Button *> m_buttons;

	// Functions
	void initGui();
	void resetGui();
	void initFonts();
	void initKeybinds();
};

#endif