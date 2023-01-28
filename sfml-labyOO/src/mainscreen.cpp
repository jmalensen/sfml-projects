#include "../include/mainscreen.h"

MainScreen::MainScreen(AssetsManager &assetsManager): assetsManager(assetsManager), map(assetsManager), player(map, assetsManager){
	init();
}

MainScreen::~MainScreen(){
}

//Initialization
void MainScreen::init(){
}

//Handling events
void MainScreen::handleEvents(sf::Event event){
}

//Update the main screen
void MainScreen::update(sf::Time TimePerFrame){
	//Update the maze
	map.update(TimePerFrame);

	//Update the game
	player.update(TimePerFrame);
}

//Draw
void MainScreen::draw(sf::RenderWindow& target){

	//Draw map
	map.draw(target);

	//Draw player
	player.draw(target);

	if(player.getHasExited()){
		this->active = false;
		// //Slow down program
		// std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}