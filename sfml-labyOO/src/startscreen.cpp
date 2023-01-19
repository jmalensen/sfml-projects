#include "../include/startscreen.h"

StartScreen::StartScreen(){
	init();
}

//Initialization
void StartScreen::init(){
	//Texture for the background
	if(!textureBackgroundScreen.loadFromFile("images/startscreen.jpg")){
		std::cout << "Failed to load background screen texture" << std::endl;
	}

	screen.setTexture(textureBackgroundScreen);
	screen.setPosition(0,0);

	//Text to display the level number
	if (!font.loadFromFile("fonts/arial.ttf")){
		std::cout << "Failed to load font" << std::endl;
	}
	titleScreen.setFont(font);
	textPressEnter.setFont(font);

	// Initialize title text
	titleScreen.setString("Javla Labyrinth");
	titleScreen.setCharacterSize(70);
	titleScreen.setPosition(400, 520);

	// Initialize press enter text
	textPressEnter.setString("Press Enter to start");
	textPressEnter.setCharacterSize(50);
	textPressEnter.setPosition(400, 640);
}

//Update the start screen
void StartScreen::update(sf::Time TimePerFrame){
	
}

//Draw
void StartScreen::draw(sf::RenderTarget& target){
	//Draw the player
	target.draw(screen);

	//Draw texts
	target.draw(titleScreen);
	target.draw(textPressEnter);
}