#include "../include/mainscreen.h"

MainScreen::MainScreen(AssetsManager &assetsManager): assetsManager(assetsManager), map(assetsManager), player(map, assetsManager){
	init();
}

MainScreen::~MainScreen(){
}

//Initialization
void MainScreen::init(){
	isPlayerDead = false;

	enemies.push_back(std::make_shared<Enemy>(1, map, assetsManager, 5,4, Enemy::HORIZONTAL, 5,14, 30.f));
	enemies.push_back(std::make_shared<Enemy>(2, map, assetsManager, 8,9, Enemy::VERTICAL, 8,13, 35.f));

	enemies.push_back(std::make_shared<Enemy>(3, map, assetsManager, 5,6, Enemy::VERTICAL, 5,13, 30.f));
	enemies.push_back(std::make_shared<Enemy>(4, map, assetsManager, 8,16, Enemy::HORIZONTAL, 8,18, 40.f));
	enemies.push_back(std::make_shared<Enemy>(5, map, assetsManager, 9,10, Enemy::VERTICAL, 9,19, 50.f));
	enemies.push_back(std::make_shared<Enemy>(6, map, assetsManager, 16,10, Enemy::HORIZONTAL, 16,24, 60.f));

	enemies.push_back(std::make_shared<Enemy>(7, map, assetsManager, 5,6, Enemy::HORIZONTAL, 5,13, 40.f));
	enemies.push_back(std::make_shared<Enemy>(8, map, assetsManager, 8,16, Enemy::VERTICAL, 8,18, 50.f));
	enemies.push_back(std::make_shared<Enemy>(9, map, assetsManager, 9,10, Enemy::HORIZONTAL, 9,19, 60.f));
	enemies.push_back(std::make_shared<Enemy>(10, map, assetsManager, 16,20, Enemy::VERTICAL, 16,20, 70.f));
	enemies.push_back(std::make_shared<Enemy>(11, map, assetsManager, 5,10, Enemy::HORIZONTAL, 5,20, 80.f));
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
	if(map.getLevel() == 4){
		enemies[6]->update(TimePerFrame, player);
		enemies[7]->update(TimePerFrame, player);
		enemies[8]->update(TimePerFrame, player);
		enemies[9]->update(TimePerFrame, player);
		enemies[10]->update(TimePerFrame, player);
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

	if(map.getLevel() == 4){
		enemies[6]->draw(window);
		enemies[7]->draw(window);
		enemies[8]->draw(window);
		enemies[9]->draw(window);//
		enemies[10]->draw(window);
	}

	if(player.isDead()){
		this->active = false;
		this->isPlayerDead = true;
	}
	else if(player.getHasExited()){
		this->active = false;
		// //Slow down program
		// std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}

bool MainScreen::getIsPlayerDead() const{
	return isPlayerDead;
}