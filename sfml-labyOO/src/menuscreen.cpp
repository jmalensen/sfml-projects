#include "../include/menuscreen.h"

MenuScreen::MenuScreen(AssetsManager &assetsManager) : assetsManager(assetsManager){
	init();
}

MenuScreen::~MenuScreen(){
}

//Initialization
void MenuScreen::init(){
	//Texture for the background
	this->assetsManager.loadTexture("menuscreen", "images/menuscreen.jpg");
	this->screen.setTexture(this->assetsManager.getTexture("menuscreen"));
	this->screen.setPosition(0,0);

	//Text to display the text
	this->assetsManager.loadFont("arial", "fonts/arial.ttf");
	this->titleScreen.setFont(this->assetsManager.getFont("arial"));

	// Initialize title text
	this->titleScreen.setString("Menu");
	this->titleScreen.setCharacterSize(70);
	this->titleScreen.setPosition(300, 320);
}

//Handling events
void MenuScreen::handleEvents(sf::Event event){
}

//Update the end screen
void MenuScreen::update(sf::Time TimePerFrame){
}

//Draw
void MenuScreen::draw(sf::RenderTarget& target){

	//Draw the screen
	target.draw(this->screen);

	//Draw texts
	// target.draw(titleScreen);
}