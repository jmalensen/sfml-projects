#include "../include/endscreen.h"

EndScreen::EndScreen(AssetsManager &assetsManager) : assetsManager(assetsManager){
	init();
}

EndScreen::~EndScreen(){
}

//Initialization
void EndScreen::init(){
	//Texture for the background
	assetsManager.loadTexture("startscreen", "images/startscreen.jpg");
	screen.setTexture(assetsManager.getTexture("startscreen"));
	screen.setPosition(0,0);

	//Text to display the text
	assetsManager.loadFont("arial", "fonts/arial.ttf");
	titleScreen.setFont(assetsManager.getFont("arial"));

	// Initialize title text
	titleScreen.setString("Endgame");
	titleScreen.setCharacterSize(70);
	titleScreen.setPosition(400, 520);

	//Win sound
	assetsManager.loadSound("win", "sounds/win.ogg");
	winSound = (assetsManager.getSound("win"));
}

//Handling events
void EndScreen::handleEvents(sf::Event event){
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