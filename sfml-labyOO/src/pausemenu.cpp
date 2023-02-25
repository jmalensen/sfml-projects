#include "../include/pausemenu.h"

// Initialization
void PauseMenu::initVariables(sf::VideoMode &vm)
{
	// Texture for the background
	this->m_background.setSize(
			sf::Vector2f(
					static_cast<float>(vm.width),
					static_cast<float>(vm.height)));

	if (!this->m_backgroundTexture.loadFromFile("images/menuscreen.png"))
	{
		throw "ERROR::PAUSE_MENU::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->m_background.setTexture(&this->m_backgroundTexture);
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
	target->draw(this->m_background);
}