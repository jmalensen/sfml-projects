#include "../include/endscreen.h"

// Initialization
void EndScreen::initVariables()
{
	this->playedWinSound = false;

	// Texture for the background
	this->assetsManager.loadTexture("screen", "images/screen.jpg");
	this->screen.setTexture(this->assetsManager.getTexture("screen"));
	this->screen.setPosition(0, 0);

	// Text to display the text
	this->assetsManager.loadFont("arial", "fonts/arial.ttf");
	this->titleScreen.setFont(this->assetsManager.getFont("arial"));

	// Initialize title text
	this->titleScreen.setString("Endgame");
	this->titleScreen.setCharacterSize(70);
	this->titleScreen.setPosition(400, 520);

	// Win sound
	this->assetsManager.loadSound("win", "sounds/win.ogg");
	this->winSound = (this->assetsManager.getSound("win"));
	this->winSound.setVolume(15);
}

EndScreen::EndScreen(AssetsManager &assetsManager) : assetsManager(assetsManager)
{
	initVariables();
}

EndScreen::~EndScreen()
{
}

// Handling events
void EndScreen::handleEvents(sf::Event event)
{
}

// Update the end screen
void EndScreen::update(const float &dt)
{
	// This part is needed otherwise sound might not be played
	float speed = 40.f;

	// Delay between 2 moves
	float moveDelay = 5.f / speed;

	// Last time player moved
	float lastMove = 0.f;
	lastMove += dt;

	if (lastMove >= moveDelay && !this->playedWinSound)
	{
		this->winSound.play();
		lastMove = 0.f;
		this->playedWinSound = true;
	}
}

// Draw
void EndScreen::draw(sf::RenderWindow *window)
{

	// Draw the player
	window->draw(this->screen);

	// Draw texts
	window->draw(this->titleScreen);
}