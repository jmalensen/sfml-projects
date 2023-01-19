#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "startscreen.h"
#include "mainscreen.h"
#include <iostream>
#include <chrono>
#include <thread>

class StartScreen;
class MainScreen;

class Game{
	public:
	//Constructor
	Game();

	//Run the game
	void run();

	private:
	//Handle events
	void handleEvents();

	//Update the game
	void update(sf::Time TimePerFrame);

	//Draw
	void draw();

	//The windows for the render
	sf::RenderWindow window;

	//The startscreen
	StartScreen startScreen;
	MainScreen mainScreen;
};

#endif //GAME_H