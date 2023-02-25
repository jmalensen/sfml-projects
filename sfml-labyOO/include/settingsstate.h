#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "stdHeader.h"
#include "state.h"
#include "mainmenustate.h"
#include "gui.h"

class SettingsState : public State
{
public:
	SettingsState(StateData *stateData);
	virtual ~SettingsState();

	// Accessors

	// Functions
	void updateInput(const float &dt);
	void updateGui(const float &dt);
	void update(const float &dt);
	void drawGui(sf::RenderTarget &target);
	void draw(sf::RenderTarget *target = NULL);

private:
	// Variables
	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;
	sf::Font m_font;

	std::map<std::string, gui::Button *> m_buttons;
	std::map<std::string, gui::DropDownList *> m_dropDownLists;

	sf::Text m_optionsText;

	std::vector<sf::VideoMode> m_modes;

	// Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();
};

#endif