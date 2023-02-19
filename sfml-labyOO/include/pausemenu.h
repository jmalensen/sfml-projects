#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "stdHeader.h"
#include "gui.h"

class PauseMenu
{
public:
	PauseMenu(sf::VideoMode &vm);
	virtual ~PauseMenu();

	// Functions
	void update(const float &dt);
	void draw(sf::RenderTarget *target);

private:
	// Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	// Functions
	void initVariables(sf::VideoMode &vm);
};

#endif