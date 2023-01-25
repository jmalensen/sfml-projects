#include "../include/screensmanager.h"

ScreensManager::ScreensManager() {
	currentScreen = 0;
	startScreen = std::make_unique<StartScreen>();
	mainScreen = std::make_unique<MainScreen>();
	// menuScreen = std::make_unique<MenuScreen>();
	endScreen = std::make_unique<EndScreen>();
}

ScreensManager::~ScreensManager() {}

void ScreensManager::showStartScreen() {
	currentScreen = 0;
}

void ScreensManager::showMainScreen() {
	currentScreen = 1;
}

// void ScreensManager::showMenuScreen() {
// 	currentScreen = 2;
// }

void ScreensManager::showEndScreen() {
	currentScreen = 3;
}

void ScreensManager::handleEvent(sf::Event event) {
	// switch (currentScreen) {
	// 	case 0: startScreen->handleEvent(event); break;
	// 	case 1: mainScreen->handleEvent(event); break;
	// 	//case 2: menuScreen->handleEvent(event); break;
	// 	case 3: endScreen->handleEvent(event); break;
	// }
}

void ScreensManager::render(sf::RenderWindow &window) {
	// switch (currentScreen) {
	// 	case 0: startScreen->render(window); break;
	// 	case 1: mainScreen->render(window); break;
	// 	// case 2: menuScreen->render(window); break;
	// 	case 3: endScreen->render(window); break;
	// }
}

void ScreensManager::update() {
	// switch (currentScreen) {
	// 	case 0: startScreen->update(); break;
	// 	case 1: mainScreen->update(); break;
	// 	// case 2: menuScreen->update(); break;
	// 	case 3: endScreen->update(); break;
	// }
}