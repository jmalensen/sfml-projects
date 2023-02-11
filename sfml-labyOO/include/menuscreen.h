#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "stdHeader.h"
#include "screen.h"
#include "assetsmanager.h"

class AssetsManager;

class MenuScreen : public Screen
{
public:
	// Constructor and destructor
	MenuScreen(AssetsManager &assetsManager);
	~MenuScreen();

	// Handling events
	void handleEvents(sf::Event event);

	// Update the menu screen
	void update(const float &dt);

	// Draw
	void draw(sf::RenderWindow *window);

private:
	// The assets manager
	AssetsManager &assetsManager;

	// Texture for the screen
	sf::Sprite screen;

	/// Text to display the text
	// Select the font
	sf::Font font;

	sf::Text titleScreen;

	// Initialization
	void initVariables();
};

#endif // MENUSCREEN_H