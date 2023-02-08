#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "stdHeader.h"
#include "gamestate.h"
#include "button.h"

class MainMenuState :
	public State
{
	public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	//Methods
	void endState();

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);

	private:
	//Variables
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Methods
	void initFonts();
	void initKeybinds();
	void initButtons();
};

#endif