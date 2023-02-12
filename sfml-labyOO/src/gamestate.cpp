#include "../include/gamestate.h"

void GameState::initKeybinds()
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

GameState::GameState(StateData *stateData)
		: State(stateData)
{
	this->initKeybinds();

	this->screensManager.showMenuScreen();
}

GameState::~GameState()
{
}

void GameState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::update(const float &dt)
{
	// std::cout << "GameState::update" << std::endl;
	this->screensManager.update(dt);

	// Handle enter key press
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ENTER"))) && this->screensManager.getCurrentScreen() != ScreensManager::MAINSCREEN)
	{
		this->screensManager.showMainScreen();
	}

	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->screensManager.getCurrentScreen() == ScreensManager::ENDSCREEN) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->screensManager.getCurrentScreen() == ScreensManager::GAMEOVERSCREEN))
	{
		this->window->close();
	}

	// Display the menu
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->screensManager.getCurrentScreen() != ScreensManager::MENUSCREEN)
	{
		this->screensManager.showMenuScreen();
	}
}

void GameState::draw(sf::RenderTarget *target)
{
	if (!target)
	{
		target = this->window;
	}

	// Draw screens
	this->screensManager.draw(this->window);
}