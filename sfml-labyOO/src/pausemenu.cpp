#include "../include/pausemenu.h"

// Initialization
void PauseMenu::initVariables(sf::VideoMode &vm)
{
	// Texture for the background
	this->background.setSize(
			sf::Vector2f(
					static_cast<float>(vm.width),
					static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("images/menuscreen.png"))
	{
		throw "ERROR::PAUSE_MENU::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

PauseMenu::PauseMenu(sf::VideoMode &vm)
{
	this->initVariables(vm);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::update(const float &dt)
{
}

void PauseMenu::draw(sf::RenderTarget *target)
{
	// Draw the screen
	target->draw(this->background);
}