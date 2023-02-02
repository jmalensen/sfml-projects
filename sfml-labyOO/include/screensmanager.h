#ifndef SCREENSMANAGER_H
#define SCREENSMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "assetsmanager.h"
#include "startscreen.h"
#include "menuscreen.h"
#include "mainscreen.h"
#include "endscreen.h"
#include "gameoverscreen.h"

class AssetsManager;
class StartScreen;
class MenuScreen;
class MainScreen;
class EndScreen;
class GameoverScreen;

class ScreensManager {
	public:
	//Constructor and destructor
	ScreensManager(AssetsManager &assetsManager);
	~ScreensManager();

	static constexpr int STARTSCREEN = 0;
	static constexpr int MAINSCREEN = 1;
	static constexpr int MENUSCREEN = 2;
	static constexpr int ENDSCREEN = 3;
	static constexpr int ENDSCREEN = 4;
	
	// Functions for switching between screens
	void showStartScreen();
	void showMainScreen();
	void showMenuScreen();
	void showEndScreen();
	void showGameoverScreen();
	int getCurrentScreen();

	void handleEvents(sf::Event event);
	void update(sf::Time TimePerFrame);
	void draw(sf::RenderWindow &window);

	private:
	AssetsManager &assetsManager;

	// Member variable for the current screen
	int currentScreen;

	std::unique_ptr<StartScreen> startScreen;
	std::unique_ptr<MainScreen> mainScreen;
	std::unique_ptr<MenuScreen> menuScreen;
	std::unique_ptr<EndScreen> endScreen;
	std::unique_ptr<GameoverScreen> gameoverScreen;
};

#endif //SCREENSMANAGER_H