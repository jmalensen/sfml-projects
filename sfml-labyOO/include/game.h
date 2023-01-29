#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "assetsmanager.h"
#include "screensmanager.h"
#include <iostream>
#include <chrono>
#include <thread>

class AssetsManager;
class ScreensManager;

class Game{
	public:
	//Constructor and destructor
	Game();
	~Game();

	//Run the game
	void run();

	private:
	AssetsManager assetsManager;
	sf::Music music;

	//Handle events
	void handleEvents();

	//Update the game
	void update(sf::Time TimePerFrame);

	//Draw
	void draw();

	//The windows for the render
	sf::RenderWindow window;

	//The screenmanager
	ScreensManager screensManager = ScreensManager(assetsManager);
};

#endif //GAME_H