#include "../include/gameoverscreen.h"

// Initialization
void GameoverScreen::initVariables()
{

	// Texture for the background
	this->assetsManager.loadTexture("screen", "images/screen.jpg");
	this->screen.setTexture(this->assetsManager.getTexture("screen"));
	this->screen.setPosition(0, 0);

	// Text to display the text
	this->assetsManager.loadFont("arial", "fonts/arial.ttf");
	this->titleScreen.setFont(this->assetsManager.getFont("arial"));

	// Initialize title text
	this->titleScreen.setString("Game Over");
	this->titleScreen.setCharacterSize(70);
	this->titleScreen.setPosition(400, 520);
}

GameoverScreen::GameoverScreen(AssetsManager &assetsManager) : assetsManager(assetsManager)
{
	initVariables();
}

GameoverScreen::~GameoverScreen()
{
}

// Handling events
void GameoverScreen::handleEvents(sf::Event event)
{
}

// Update the screen
void GameoverScreen::update(sf::Time dt)
{
}

// Draw
void GameoverScreen::draw(sf::RenderWindow *window)
{

	// Draw the screen
	window->draw(this->screen);

	// Draw text
	window->draw(this->titleScreen);
}