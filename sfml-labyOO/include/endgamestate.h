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
	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;
	AssetsManager m_assetsManager;

	// Victory sound
	float m_lastMove;
	sf::Sound m_winSound;
	bool m_playedWinSound;

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