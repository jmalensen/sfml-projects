#include "../include/mainscreen.h"
#include "../include/map.h"
#include "../include/player.h"

MainScreen::MainScreen(): map(), player(map){
	init();
}

//Initialization
void MainScreen::init(){
	
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

	if(player.getExited()){
		// //Slow down program
		// std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		this->active = false;
	}
}