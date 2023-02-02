#include "../include/endscreen.h"

EndScreen::EndScreen(AssetsManager &assetsManager) : assetsManager(assetsManager){
	init();
}

EndScreen::~EndScreen(){
}

//Initialization
void EndScreen::init(){
	playedWinSound = false;

	//Texture for the background
	assetsManager.loadTexture("screen", "images/screen.jpg");
	screen.setTexture(assetsManager.getTexture("screen"));
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
	winSound.setVolume(15);
}

//Handling events
void EndScreen::handleEvents(sf::Event event){
}

//Update the end screen
void EndScreen::update(sf::Time dt){
	//This part is needed otherwise sound might not be played
	static const float speed = 40.f;

	//Delay between 2 moves
	static const sf::Time moveDelay = sf::seconds(5.f / speed);

	//Last time player moved
	static sf::Time lastMove = sf::Time::Zero;
	lastMove += dt;

	if(lastMove >= moveDelay && !playedWinSound){
		winSound.play();
		lastMove = sf::Time::Zero;
		playedWinSound = true;
	}

}

//Draw
void EndScreen::draw(sf::RenderTarget& target){

	//Draw the player
	target.draw(screen);

	//Draw texts
	target.draw(titleScreen);
}