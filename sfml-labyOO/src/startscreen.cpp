#include "../include/startscreen.h"

StartScreen::StartScreen(AssetsManager &assetsManager): assetsManager(assetsManager){
	init();
}

StartScreen::~StartScreen(){
}

//Initialization
void StartScreen::init(){
	//Texture for the background
	assetsManager.loadTexture("screen", "images/screen.jpg");
	screen.setTexture(assetsManager.getTexture("screen"));
	screen.setPosition(0,0);

	//Text to display the text
	assetsManager.loadFont("arial", "fonts/arial.ttf");
	titleScreen.setFont(assetsManager.getFont("arial"));
	textPressEnter.setFont(assetsManager.getFont("arial"));

	// Initialize title text
	titleScreen.setString("Javla Labyrinth");
	titleScreen.setCharacterSize(70);
	titleScreen.setPosition(400, 520);

	// Initialize press enter text
	textPressEnter.setString("Press Space to start");
	textPressEnter.setCharacterSize(50);
	textPressEnter.setPosition(400, 640);
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
	target.draw(screen);

	//Draw texts
	target.draw(titleScreen);
	target.draw(textPressEnter);
}