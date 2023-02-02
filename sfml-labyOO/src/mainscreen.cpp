#include "../include/mainscreen.h"

MainScreen::MainScreen(AssetsManager &assetsManager): assetsManager(assetsManager), map(assetsManager), player(map, assetsManager){
	init();
}

MainScreen::~MainScreen(){
}

//Initialization
void MainScreen::init(){

	enemies.push_back(std::make_shared<Enemy>(1, map, assetsManager, 5,4, Enemy::HORIZONTAL, 5,14, 30.f));
	enemies.push_back(std::make_shared<Enemy>(2, map, assetsManager, 8,9, Enemy::VERTICAL, 8,13, 35.f));

	enemies.push_back(std::make_shared<Enemy>(3, map, assetsManager, 5,6, Enemy::VERTICAL, 5,13, 30.f));
	enemies.push_back(std::make_shared<Enemy>(4, map, assetsManager, 8,16, Enemy::HORIZONTAL, 8,18, 40.f));
	enemies.push_back(std::make_shared<Enemy>(5, map, assetsManager, 9,10, Enemy::VERTICAL, 9,19, 50.f));
	enemies.push_back(std::make_shared<Enemy>(6, map, assetsManager, 16,10, Enemy::HORIZONTAL, 16,24, 60.f));
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

	if(map.getLevel() == 2){
		enemies[0]->update(TimePerFrame, player);
		enemies[1]->update(TimePerFrame, player);
	}
	if(map.getLevel() == 3){
		enemies[2]->update(TimePerFrame, player);
		enemies[3]->update(TimePerFrame, player);
		enemies[4]->update(TimePerFrame, player);
		enemies[5]->update(TimePerFrame, player);
	}
}

//Draw
void MainScreen::draw(sf::RenderWindow& window){

	//Draw map
	map.draw(window);

	//Draw player
	player.draw(window);

	if(map.getLevel() == 2){
		enemies[0]->draw(window);
		enemies[1]->draw(window);
	}

	if(map.getLevel() == 3){
		enemies[2]->draw(window);
		enemies[3]->draw(window);
		enemies[4]->draw(window);
		enemies[5]->draw(window);
	}

	if(player.getHasExited() || player.isDead() ){
		this->active = false;
		// //Slow down program
		// std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}