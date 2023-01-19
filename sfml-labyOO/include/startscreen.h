#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "screen.h"

class StartScreen: public Screen{
	public:
	StartScreen();

	//Initialization
	void init();

	//Update the start screen
	void update(sf::Time TimePerFrame);

	//Draw
	void draw(sf::RenderTarget& target);

	private:
	//Texture for the screen
	sf::Texture textureBackgroundScreen;
	sf::Sprite screen;

	///Text to display the level number
	//Select the font
	sf::Font font;

	sf::Text titleScreen;
	sf::Text textPressEnter;
};

#endif //STARTSCREEN_H