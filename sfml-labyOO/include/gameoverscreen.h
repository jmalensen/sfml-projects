#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "stdHeader.h"
#include "screen.h"
#include "assetsmanager.h"

class AssetsManager;

class GameoverScreen: public Screen{
	public:
	//Constructor and destructor
	GameoverScreen(AssetsManager &assetsManager);
	~GameoverScreen();

	//Initialization
	void init();

	//Handling events
	void handleEvents(sf::Event event);

	//Update the screen
	void update(sf::Time TimePerFrame);

	//Draw
	void draw(sf::RenderTarget& target);

	private:
	//The assets manager
	AssetsManager &assetsManager;

	//Texture for the screen
	sf::Sprite screen;

	///Text to display the text
	//Select the font
	sf::Font font;

	sf::Text titleScreen;
};

#endif //GAMEOVERSCREEN_H