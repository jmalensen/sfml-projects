#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "stdHeader.h"
#include "state.h"
#include "gui.h"

class SettingsState : public State
{
public:
	SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
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
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button *> buttons;
	std::map<std::string, gui::DropDownList *> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initText();
};

#endif