#include "../include/mainscreen.h"

MainScreen::MainScreen(AssetsManager &assetsManager): assetsManager(assetsManager), map(assetsManager), player(map, assetsManager), enemy(map, assetsManager), enemy2(map, assetsManager){
	init();
}

MainScreen::~MainScreen(){
}

//Initialization
void MainScreen::init(){
	if(map.getLevel() == 1){
		enemy.setPositionX(3);
		enemy.setPositionY(3);
		enemy.setBehaviour(Enemy::HORIZONTAL, 3, 11);

		enemy2.setPositionX(8);
		enemy2.setPositionY(8);
		enemy2.setBehaviour(Enemy::VERTICAL, 7, 13);
	}
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

	if(map.getLevel() == 1){
		enemy.update(TimePerFrame, player);
		enemy2.update(TimePerFrame, player);
	}
}

//Draw
void MainScreen::draw(sf::RenderWindow& target){

	//Draw map
	map.draw(target);

	//Draw player
	player.draw(target);

	if(map.getLevel() == 1){
		enemy.draw(target);
		enemy2.draw(target);
	}

	if(player.getHasExited() || player.isDead() ){
		this->active = false;
		// //Slow down program
		// std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}