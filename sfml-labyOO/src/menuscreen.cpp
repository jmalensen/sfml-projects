#include "../include/menuscreen.h"

MenuScreen::MenuScreen(AssetsManager &assetsManager) : assetsManager(assetsManager){
	init();
}

MenuScreen::~MenuScreen(){
}

//Initialization
void MenuScreen::init(){
	//Texture for the background
	assetsManager.loadTexture("menuscreen", "images/menuscreen.jpg");
	screen.setTexture(assetsManager.getTexture("menuscreen"));
	screen.setPosition(0,0);

	//Text to display the text
	assetsManager.loadFont("arial", "fonts/arial.ttf");
	titleScreen.setFont(assetsManager.getFont("arial"));

	// Initialize title text
	titleScreen.setString("Menu");
	titleScreen.setCharacterSize(70);
	titleScreen.setPosition(300, 320);
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
	target.draw(screen);

	//Draw texts
	// target.draw(titleScreen);
}