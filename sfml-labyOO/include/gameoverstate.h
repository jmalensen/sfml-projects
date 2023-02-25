#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "stdHeader.h"
#include "state.h"
#include "gamestate.h"
#include "gui.h"

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
	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;

	sf::Font m_font;
	std::map<std::string, gui::Button *> m_buttons;
	sf::Text m_timerText;

	// Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
};

#endif