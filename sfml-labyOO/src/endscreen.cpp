#include "../include/endscreen.h"

EndScreen::EndScreen(){
	init();
}

EndScreen::~EndScreen(){
}

//Initialization
void EndScreen::init(){
	//Texture for the background
	if(!textureBackgroundScreen.loadFromFile("images/startscreen.jpg")){
		std::cout << "Failed to load background screen texture" << std::endl;
	}

	screen.setTexture(textureBackgroundScreen);
	screen.setPosition(0,0);

	//Text to display the text
	if (!font.loadFromFile("fonts/arial.ttf")){
		std::cout << "Failed to load font" << std::endl;
	}
	titleScreen.setFont(font);

	// Initialize title text
	titleScreen.setString("Endgame");
	titleScreen.setCharacterSize(70);
	titleScreen.setPosition(400, 520);

	//Win sound
	if (!buffer.loadFromFile("sounds/win.wav")){
		std::cout << "Fail to load win sound file" << std::endl;
	}
	winSound.setBuffer(buffer);
}

//Update the end screen
void EndScreen::update(sf::Time TimePerFrame){
	winSound.play();
}

//Draw
void EndScreen::draw(sf::RenderTarget& target){

	//Draw the player
	target.draw(screen);

	//Draw texts
	target.draw(titleScreen);
}