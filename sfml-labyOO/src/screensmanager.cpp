#include "../include/screensmanager.h"

ScreensManager::ScreensManager(AssetsManager &assetsManager): assetsManager(assetsManager) {
	currentScreen = ScreensManager::STARTSCREEN;

	startScreen = std::make_unique<StartScreen>(assetsManager);
	mainScreen = std::make_unique<MainScreen>(assetsManager);
	// menuScreen = std::make_unique<MenuScreen>();
	endScreen = std::make_unique<EndScreen>(assetsManager);
}

ScreensManager::~ScreensManager() {}

void ScreensManager::showStartScreen() {
	currentScreen = ScreensManager::STARTSCREEN;
}

void ScreensManager::showMainScreen() {
	currentScreen = ScreensManager::MAINSCREEN;
}

void ScreensManager::showMenuScreen() {
	//currentScreen = 2;
}

void ScreensManager::showEndScreen() {
	currentScreen = ScreensManager::ENDSCREEN;
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

		//case 2: menuScreen->handleEvents(event); break;

		case ScreensManager::ENDSCREEN :
		endScreen->handleEvents(event);
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

		// case 2: menuScreen->update(); break;

		case ScreensManager::ENDSCREEN :
		endScreen->update(TimePerFrame);
		break;
	}
}

void ScreensManager::draw(sf::RenderWindow &window) {
	switch (currentScreen) {
		case ScreensManager::STARTSCREEN :
		startScreen->draw(window);
		break;

		case ScreensManager::MAINSCREEN :
		if(mainScreen->active){
			mainScreen->draw(window);
		}
		else{
			showEndScreen();
			endScreen->draw(window);
		}
		break;

		// case 2: menuScreen->draw(window); break;

		case ScreensManager::ENDSCREEN :
		endScreen->draw(window);
		break;
	}
}