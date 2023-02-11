#include "../include/menuscreen.h"

// Initialization
void MenuScreen::initVariables()
{
	// Texture for the background
	this->assetsManager.loadTexture("menuscreen", "images/menuscreen.jpg");
	this->screen.setTexture(this->assetsManager.getTexture("menuscreen"));
	this->screen.setPosition(0, 0);

	// Text to display the text
	this->assetsManager.loadFont("arial", "fonts/arial.ttf");
	this->titleScreen.setFont(this->assetsManager.getFont("arial"));

	// Initialize title text
	this->titleScreen.setString("Menu");
	this->titleScreen.setCharacterSize(70);
	this->titleScreen.setPosition(300, 320);
}

MenuScreen::MenuScreen(AssetsManager &assetsManager) : assetsManager(assetsManager)
{
	this->initVariables();
}

MenuScreen::~MenuScreen()
{
}

// Handling events
void MenuScreen::handleEvents(sf::Event event)
{
}

// Update the end screen
void MenuScreen::update(const float &dt)
{
}

// Draw
void MenuScreen::draw(sf::RenderWindow *window)
{

	// Draw the screen
	window->draw(this->screen);

	// Draw texts
	//  target.draw(titleScreen);
}