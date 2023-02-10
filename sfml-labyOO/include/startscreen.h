#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "stdHeader.h"
#include "screen.h"
#include "assetsmanager.h"

class AssetsManager;

class StartScreen : public Screen
{
public:
	// Constructor and destructor
	StartScreen(AssetsManager &assetsManager);
	~StartScreen();

	// Initialization
	void init();

	// Handling events
	void handleEvents(sf::Event event);

	// Update the start screen
	void update(sf::Time TimePerFrame);

	// Draw
	void draw(sf::RenderWindow *window);

private:
	// The assets manager
	AssetsManager &assetsManager;

	// Texture for the screen
	sf::Texture textureBackgroundScreen;
	sf::Sprite screen;

	/// Text to display the level number
	// Select the font
	sf::Font font;

	sf::Text titleScreen;
	sf::Text textPressEnter;
};

#endif // STARTSCREEN_H