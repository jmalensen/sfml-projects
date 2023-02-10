#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "stdHeader.h"
#include "screen.h"
#include "assetsmanager.h"

class AssetsManager;

class EndScreen : public Screen
{
public:
	// Constructor and destructor
	EndScreen(AssetsManager &assetsManager);
	~EndScreen();

	// Handling events
	void handleEvents(sf::Event event);

	// Update the end screen
	void update(sf::Time TimePerFrame);

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

	// Victory sound
	sf::Sound winSound;
	bool playedWinSound;

	// Initialization
	void initVariables();
};

#endif // ENDSCREEN_H