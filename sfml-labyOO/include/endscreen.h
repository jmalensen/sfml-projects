#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "screen.h"

class EndScreen: public Screen{
	public:
	EndScreen();

	//Initialization
	void init();

	//Update the end screen
	void update(sf::Time TimePerFrame);

	//Draw
	void draw(sf::RenderTarget& target);

	private:
	//Texture for the screen
	sf::Texture textureBackgroundScreen;
	sf::Sprite screen;

	///Text to display the text
	//Select the font
	sf::Font font;

	sf::Text titleScreen;

	//Victory sound
	sf::SoundBuffer buffer;
	sf::Sound winSound;
};

#endif //ENDSCREEN_H