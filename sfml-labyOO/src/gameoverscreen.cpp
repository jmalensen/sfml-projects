#include "../include/gameoverscreen.h"

GameoverScreen::GameoverScreen(AssetsManager &assetsManager) : assetsManager(assetsManager){
	init();
}

GameoverScreen::~GameoverScreen(){
}

//Initialization
void GameoverScreen::init(){

	//Texture for the background
	assetsManager.loadTexture("screen", "images/screen.jpg");
	screen.setTexture(assetsManager.getTexture("screen"));
	screen.setPosition(0,0);

	//Text to display the text
	assetsManager.loadFont("arial", "fonts/arial.ttf");
	titleScreen.setFont(assetsManager.getFont("arial"));

	// Initialize title text
	titleScreen.setString("Game Over");
	titleScreen.setCharacterSize(70);
	titleScreen.setPosition(400, 520);
}

//Handling events
void GameoverScreen::handleEvents(sf::Event event){
}

//Update the screen
void GameoverScreen::update(sf::Time dt){
}

//Draw
void GameoverScreen::draw(sf::RenderTarget& target){

	//Draw the screen
	target.draw(screen);

	//Draw text
	target.draw(titleScreen);
}