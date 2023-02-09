#include "../include/screensmanager.h"

ScreensManager::ScreensManager(AssetsManager &assetsManager) : assetsManager(assetsManager)
{
	this->currentScreen = ScreensManager::STARTSCREEN;

	this->startScreen = std::make_unique<StartScreen>(this->assetsManager);
	this->mainScreen = std::make_unique<MainScreen>(this->assetsManager);
	this->menuScreen = std::make_unique<MenuScreen>(this->assetsManager);
	this->endScreen = std::make_unique<EndScreen>(this->assetsManager);
	this->gameoverScreen = std::make_unique<GameoverScreen>(this->assetsManager);
}

ScreensManager::~ScreensManager() {}

void ScreensManager::showStartScreen()
{
	this->currentScreen = ScreensManager::STARTSCREEN;
}

void ScreensManager::showMainScreen()
{
	this->currentScreen = ScreensManager::MAINSCREEN;
}

void ScreensManager::showMenuScreen()
{
	this->currentScreen = ScreensManager::MENUSCREEN;
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
	case ScreensManager::STARTSCREEN:
		this->startScreen->handleEvents(event);
		break;

	case ScreensManager::MAINSCREEN:
		this->mainScreen->handleEvents(event);
		break;

	case ScreensManager::MENUSCREEN:
		this->menuScreen->handleEvents(event);
		break;

	case ScreensManager::ENDSCREEN:
		this->endScreen->handleEvents(event);
		break;

	case ScreensManager::GAMEOVERSCREEN:
		this->gameoverScreen->handleEvents(event);
		break;
	}
}

void ScreensManager::update(sf::Time TimePerFrame)
{
	switch (this->currentScreen)
	{
	case ScreensManager::STARTSCREEN:
		this->startScreen->update(TimePerFrame);
		break;

	case ScreensManager::MAINSCREEN:
		this->mainScreen->update(TimePerFrame);
		break;

	case ScreensManager::MENUSCREEN:
		this->menuScreen->update(TimePerFrame);
		break;

	case ScreensManager::ENDSCREEN:
		this->endScreen->update(TimePerFrame);
		break;

	case ScreensManager::GAMEOVERSCREEN:
		this->gameoverScreen->update(TimePerFrame);
		break;
	}
}

void ScreensManager::draw(sf::RenderWindow &window)
{
	switch (this->currentScreen)
	{
	case ScreensManager::STARTSCREEN:
		this->startScreen->draw(window);
		break;

	case ScreensManager::MAINSCREEN:
		if (!this->mainScreen->active && this->mainScreen->getIsPlayerDead())
		{
			showGameoverScreen();
			this->gameoverScreen->draw(window);
		}
		else if (this->mainScreen->active)
		{
			this->mainScreen->draw(window);
		}
		else
		{
			showEndScreen();
			this->endScreen->draw(window);
		}
		break;

	case ScreensManager::MENUSCREEN:
		this->menuScreen->draw(window);
		break;

	case ScreensManager::ENDSCREEN:
		this->endScreen->draw(window);
		break;

	case ScreensManager::GAMEOVERSCREEN:
		this->gameoverScreen->draw(window);
		break;
	}
}