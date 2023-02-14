#include "../include/gameoverscreen.h"

// Initialization
void GameoverScreen::initVariables()
{

	// Texture for the background
	this->assetsManager.loadTexture("gameoverscreen", "images/gameoverscreen.jpg");
	this->screen.setTexture(this->assetsManager.getTexture("gameoverscreen"));
	this->screen.setPosition(0, 0);

	// Text to display the text
	// this->assetsManager.loadFont("arial", "fonts/arial.ttf");
	// this->titleScreen.setFont(this->assetsManager.getFont("arial"));

	// // Initialize title text
	// this->titleScreen.setString("Game Over");
	// this->titleScreen.setCharacterSize(70);
	// this->titleScreen.setPosition(400, 520);
}

GameoverScreen::GameoverScreen(AssetsManager &assetsManager) : assetsManager(assetsManager)
{
	this->initVariables();
}

GameoverScreen::~GameoverScreen()
{
}

// Handling events
void GameoverScreen::handleEvents(sf::Event event)
{
}

// Update the screen
void GameoverScreen::update(const float &dt)
{
}

// Draw
void GameoverScreen::draw(sf::RenderWindow *window)
{

	float factor = gui::getFactor(60, window);
	this->screen.setScale(factor, factor);

	// Draw the screen
	window->draw(this->screen);

	// Draw text
	// window->draw(this->titleScreen);
}