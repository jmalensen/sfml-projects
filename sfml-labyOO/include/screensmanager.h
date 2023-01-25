#ifndef SCREENSMANAGER_H
#define SCREENSMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "startscreen.h"
#include "mainscreen.h"
#include "endscreen.h"

class StartScreen;
class MainScreen;
class EndScreen;

class ScreensManager {
	public:
	//Constructor and destructor
	ScreensManager();
	~ScreensManager();
	
	// Functions for switching between screens
	void showStartScreen();
	void showMainScreen();
	//void showMenuScreen();
	void showEndScreen();
	void handleEvent(sf::Event event);
	void render(sf::RenderWindow &window);
	void update();

	private:
	// Member variable for the current screen
	int currentScreen;
	std::unique_ptr<StartScreen> startScreen;
	std::unique_ptr<MainScreen> mainScreen;
	//std::unique_ptr<MenuScreen> menuScreen;
	std::unique_ptr<EndScreen> endScreen;
};

#endif //SCREENSMANAGER_H