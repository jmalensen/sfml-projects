#include "../include/screensmanager.h"

ScreensManager::ScreensManager(AssetsManager &assetsManager): assetsManager(assetsManager) {
	currentScreen = ScreensManager::STARTSCREEN;

	startScreen = std::make_unique<StartScreen>(assetsManager);
	mainScreen = std::make_unique<MainScreen>(assetsManager);
	menuScreen = std::make_unique<MenuScreen>(assetsManager);
	endScreen = std::make_unique<EndScreen>(assetsManager);
	gameoverScreen = std::make_unique<GameoverScreen>(assetsManager);
}

ScreensManager::~ScreensManager() {}

void ScreensManager::showStartScreen() {
	currentScreen = ScreensManager::STARTSCREEN;
}

void ScreensManager::showMainScreen() {
	currentScreen = ScreensManager::MAINSCREEN;
}

void ScreensManager::showMenuScreen() {
	currentScreen = ScreensManager::MENUSCREEN;
}

void ScreensManager::showEndScreen() {
	currentScreen = ScreensManager::ENDSCREEN;
}

void ScreensManager::showGameoverScreen() {
	currentScreen = ScreensManager::GAMEOVERSCREEN;
}

int ScreensManager::getCurrentScreen() {
	return currentScreen;
}

void ScreensManager::handleEvents(sf::Event event) {
	switch (currentScreen) {
		case ScreensManager::STARTSCREEN :
		startScreen->handleEvents(event);
		break;

		case ScreensManager::MAINSCREEN :
		mainScreen->handleEvents(event);
		break;

		case ScreensManager::MENUSCREEN :
		menuScreen->handleEvents(event);
		break;

		case ScreensManager::ENDSCREEN :
		endScreen->handleEvents(event);
		break;

		case ScreensManager::GAMEOVERSCREEN :
		gameoverScreen->handleEvents(event);
		break;
	}
}

void ScreensManager::update(sf::Time TimePerFrame) {
	switch (currentScreen) {
		case ScreensManager::STARTSCREEN :
		startScreen->update(TimePerFrame);
		break;

		case ScreensManager::MAINSCREEN :
		mainScreen->update(TimePerFrame);
		break;

		case ScreensManager::MENUSCREEN :
		menuScreen->update(TimePerFrame);
		break;

		case ScreensManager::ENDSCREEN :
		endScreen->update(TimePerFrame);
		break;

		case ScreensManager::GAMEOVERSCREEN :
		gameoverScreen->update(TimePerFrame);
		break;
	}
}

void ScreensManager::draw(sf::RenderWindow &window) {
	switch (currentScreen) {
		case ScreensManager::STARTSCREEN :
		startScreen->draw(window);
		break;

		case ScreensManager::MAINSCREEN :
		if(!mainScreen->active && mainScreen->getIsPlayerDead()){
			showGameoverScreen();
			gameoverScreen->draw(window);
		}
		else if(mainScreen->active){
			mainScreen->draw(window);
		}
		else{
			showEndScreen();
			endScreen->draw(window);
		}
		break;

		case ScreensManager::MENUSCREEN :
		menuScreen->draw(window);
		break;

		case ScreensManager::ENDSCREEN :
		endScreen->draw(window);
		break;

		case ScreensManager::GAMEOVERSCREEN :
		gameoverScreen->draw(window);
		break;
	}
}