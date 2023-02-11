#include "../include/screensmanager.h"

ScreensManager::ScreensManager(AssetsManager &assetsManager) : assetsManager(assetsManager)
{
	this->currentScreen = ScreensManager::MAINSCREEN;

	this->menuScreen = std::make_unique<MenuScreen>(this->assetsManager);
	this->mainScreen = std::make_unique<MainScreen>(this->assetsManager);
	this->endScreen = std::make_unique<EndScreen>(this->assetsManager);
	this->gameoverScreen = std::make_unique<GameoverScreen>(this->assetsManager);
}

ScreensManager::~ScreensManager() {}

void ScreensManager::showMenuScreen()
{
	this->currentScreen = ScreensManager::MENUSCREEN;
}

void ScreensManager::showMainScreen()
{
	this->currentScreen = ScreensManager::MAINSCREEN;
}

void ScreensManager::showEndScreen()
{
	this->currentScreen = ScreensManager::ENDSCREEN;
}

void ScreensManager::showGameoverScreen()
{
	this->currentScreen = ScreensManager::GAMEOVERSCREEN;
}

int ScreensManager::getCurrentScreen()
{
	return this->currentScreen;
}

void ScreensManager::handleEvents(sf::Event event)
{
	switch (this->currentScreen)
	{
	case ScreensManager::MENUSCREEN:
		this->menuScreen->handleEvents(event);
		break;

	case ScreensManager::MAINSCREEN:
		this->mainScreen->handleEvents(event);
		break;

	case ScreensManager::ENDSCREEN:
		this->endScreen->handleEvents(event);
		break;

	case ScreensManager::GAMEOVERSCREEN:
		this->gameoverScreen->handleEvents(event);
		break;
	}
}

void ScreensManager::update(const float &dt)
{
	switch (this->currentScreen)
	{
	case ScreensManager::MENUSCREEN:
		this->menuScreen->update(dt);
		break;

	case ScreensManager::MAINSCREEN:
		this->mainScreen->update(dt);
		break;

	case ScreensManager::ENDSCREEN:
		this->endScreen->update(dt);
		break;

	case ScreensManager::GAMEOVERSCREEN:
		this->gameoverScreen->update(dt);
		break;
	}
}

void ScreensManager::draw(sf::RenderWindow *window)
{
	switch (this->currentScreen)
	{
	case ScreensManager::MENUSCREEN:
		this->menuScreen->draw(window);
		break;

	case ScreensManager::MAINSCREEN:
		if (!this->mainScreen->active && this->mainScreen->getIsPlayerDead())
		{
			this->showGameoverScreen();
			this->gameoverScreen->draw(window);
		}
		else if (this->mainScreen->active)
		{
			this->mainScreen->draw(window);
		}
		else
		{
			this->showEndScreen();
			this->endScreen->draw(window);
		}
		break;

	case ScreensManager::ENDSCREEN:
		this->endScreen->draw(window);
		break;

	case ScreensManager::GAMEOVERSCREEN:
		this->gameoverScreen->draw(window);
		break;
	}
}