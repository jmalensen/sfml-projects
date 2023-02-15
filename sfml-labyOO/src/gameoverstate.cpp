#include "../include/gameoverstate.h"

// Initialization
void GameoverState::initVariables()
{
	// Texture for the background
	const sf::VideoMode &vm = this->stateData->gfxSettings->resolution;

	this->background.setSize(
			sf::Vector2f(
					static_cast<float>(vm.width),
					static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("images/gameoverscreen.jpg"))
	{
		throw "ERROR::GAMEOVER_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void GameoverState::initKeybinds()
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

GameoverState::GameoverState(StateData *stateData)
		: State(stateData)
{
	this->initVariables();
	this->initKeybinds();
}

GameoverState::~GameoverState()
{
}

void GameoverState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->endState();
		this->window->close();
	}
}

void GameoverState::update(const float &dt)
{
	this->updateInput(dt);
}

void GameoverState::draw(sf::RenderTarget *target)
{
	if (!target)
	{
		target = this->window;
	}

	// Draw the screen
	this->window->draw(this->background);
}