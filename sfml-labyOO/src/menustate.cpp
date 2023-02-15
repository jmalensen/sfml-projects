#include "../include/menustate.h"

// Initialization
void MenuState::initVariables()
{
	// Texture for the background
	const sf::VideoMode &vm = this->stateData->gfxSettings->resolution;

	this->background.setSize(
			sf::Vector2f(
					static_cast<float>(vm.width),
					static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("images/menuscreen.jpg"))
	{
		throw "ERROR::MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MenuState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

MenuState::MenuState(StateData *stateData)
		: State(stateData)
{
	this->initVariables();
	this->initKeybinds();
}

MenuState::~MenuState()
{
}

void MenuState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ENTER"))))
	{
		this->endState();
		this->states->push(new GameState(this->stateData));
	}
}

void MenuState::update(const float &dt)
{
	this->updateInput(dt);
}

void MenuState::draw(sf::RenderTarget *target)
{
	if (!target)
	{
		target = this->window;
	}

	// Draw the screen
	this->window->draw(this->background);
}