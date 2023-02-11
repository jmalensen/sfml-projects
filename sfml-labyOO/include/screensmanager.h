#ifndef SCREENSMANAGER_H
#define SCREENSMANAGER_H

#include "stdHeader.h"
#include "assetsmanager.h"
#include "menuscreen.h"
#include "mainscreen.h"
#include "endscreen.h"
#include "gameoverscreen.h"

class AssetsManager;
class MenuScreen;
class MainScreen;
class EndScreen;
class GameoverScreen;

class ScreensManager
{
public:
	// Constructor and destructor
	ScreensManager(AssetsManager &assetsManager);
	~ScreensManager();

	static constexpr int MENUSCREEN = 1;
	static constexpr int MAINSCREEN = 2;
	static constexpr int ENDSCREEN = 3;
	static constexpr int GAMEOVERSCREEN = 4;

	// Functions for switching between screens
	void showMainScreen();
	void showMenuScreen();
	void showEndScreen();
	void showGameoverScreen();
	int getCurrentScreen();

	void handleEvents(sf::Event event);
	void update(const float &dt);
	void draw(sf::RenderWindow *window);

private:
	AssetsManager &assetsManager;

	// Member variable for the current screen
	int currentScreen;

	std::unique_ptr<MainScreen> mainScreen;
	std::unique_ptr<MenuScreen> menuScreen;
	std::unique_ptr<EndScreen> endScreen;
	std::unique_ptr<GameoverScreen> gameoverScreen;
};

#endif // SCREENSMANAGER_H