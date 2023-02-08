#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "stdHeader.h"
#include "state.h"

class GameState :
	public State
{
	public:
	GameState(StateData* stateData);
	virtual ~GameState();

	//Functions
	void updateView(const float& dt);
	void update(const float& dt);

	void draw(sf::RenderWindow* window = NULL);

	private:
	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;

	sf::Clock keyTimer;
	float keyTimeMax;
};

#endif