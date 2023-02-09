#include "../include/gameoverscreen.h"

GameoverScreen::GameoverScreen(AssetsManager &assetsManager) : assetsManager(assetsManager)
{
	init();
}

GameoverScreen::~GameoverScreen()
{
}

// Initialization
void GameoverScreen::init()
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

// Handling events
void GameoverScreen::handleEvents(sf::Event event)
{
}

// Update the screen
void GameoverScreen::update(sf::Time dt)
{
}

// Draw
void GameoverScreen::draw(sf::RenderTarget &target)
{

	// Draw the screen
	target.draw(this->screen);

	// Draw text
	target.draw(this->titleScreen);
}