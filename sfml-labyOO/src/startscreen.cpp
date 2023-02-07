#include "../include/startscreen.h"

StartScreen::StartScreen(AssetsManager &assetsManager): assetsManager(assetsManager){
	init();
}

StartScreen::~StartScreen(){
}

//Initialization
void StartScreen::init(){
	//Texture for the background
	this->assetsManager.loadTexture("screen", "images/screen.jpg");
	this->screen.setTexture(this->assetsManager.getTexture("screen"));
	this->screen.setPosition(0,0);

	//Text to display the text
	this->assetsManager.loadFont("arial", "fonts/arial.ttf");
	this->titleScreen.setFont(this->assetsManager.getFont("arial"));
	this->textPressEnter.setFont(this->assetsManager.getFont("arial"));

	// Initialize title text
	this->titleScreen.setString("Javla Labyrinth");
	this->titleScreen.setCharacterSize(70);
	this->titleScreen.setPosition(400, 520);

	// Initialize press enter text
	this->textPressEnter.setString("Press Space to start");
	this->textPressEnter.setCharacterSize(50);
	this->textPressEnter.setPosition(400, 640);
}

//Handling events
void StartScreen::handleEvents(sf::Event event){
}

//Update the start screen
void StartScreen::update(sf::Time TimePerFrame){
}

//Draw
void StartScreen::draw(sf::RenderTarget& target){
	//Draw the player
	target.draw(this->screen);

	//Draw texts
	target.draw(this->titleScreen);
	target.draw(this->textPressEnter);
}