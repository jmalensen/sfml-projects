#include "../include/mainscreen.h"

// Initialization
void MainScreen::initVariables()
{
	this->isPlayerDead = false;

	this->enemies.push_back(std::make_shared<Enemy>(1, this->map, this->assetsManager, 5, 4, Enemy::HORIZONTAL, 5, 14, 30.f));
	this->enemies.push_back(std::make_shared<Enemy>(2, this->map, this->assetsManager, 8, 9, Enemy::VERTICAL, 8, 13, 30.f));

	this->enemies.push_back(std::make_shared<Enemy>(3, this->map, this->assetsManager, 5, 6, Enemy::VERTICAL, 5, 13, 40.f));
	this->enemies.push_back(std::make_shared<Enemy>(4, this->map, this->assetsManager, 8, 16, Enemy::HORIZONTAL, 8, 18, 40.f));
	this->enemies.push_back(std::make_shared<Enemy>(5, this->map, this->assetsManager, 9, 10, Enemy::VERTICAL, 9, 19, 40.f));
	this->enemies.push_back(std::make_shared<Enemy>(6, this->map, this->assetsManager, 16, 10, Enemy::HORIZONTAL, 16, 24, 40.f));

	this->enemies.push_back(std::make_shared<Enemy>(7, this->map, this->assetsManager, 5, 6, Enemy::HORIZONTAL, 5, 13, 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(8, this->map, this->assetsManager, 8, 16, Enemy::VERTICAL, 8, 18, 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(9, this->map, this->assetsManager, 9, 10, Enemy::HORIZONTAL, 9, 19, 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(10, this->map, this->assetsManager, 16, 20, Enemy::VERTICAL, 16, 20, 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(11, this->map, this->assetsManager, 5, 10, Enemy::HORIZONTAL, 5, 20, 50.f));

	this->enemies.push_back(std::make_shared<Enemy>(12, this->map, this->assetsManager, 5, 6, Enemy::HORIZONTAL, 5, 13, 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(13, this->map, this->assetsManager, 8, 16, Enemy::VERTICAL, 8, 18, 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(14, this->map, this->assetsManager, 9, 10, Enemy::HORIZONTAL, 9, 19, 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(15, this->map, this->assetsManager, 16, 20, Enemy::VERTICAL, 16, 20, 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(16, this->map, this->assetsManager, 5, 10, Enemy::HORIZONTAL, 5, 20, 60.f));
}

MainScreen::MainScreen(AssetsManager &assetsManager) : assetsManager(assetsManager), map(assetsManager), player(map, assetsManager)
{
	this->initVariables();
}

MainScreen::~MainScreen()
{
}

// Handling events
void MainScreen::handleEvents(sf::Event event)
{
}

// Update the main screen
void MainScreen::update(const float &dt)
{
	// Update the maze
	this->map.update(dt);

	// Update the game
	this->player.update(dt);

	if (this->map.getLevel() == 2)
	{
		this->enemies[0]->update(dt, this->player);
		this->enemies[1]->update(dt, this->player);
	}
	if (this->map.getLevel() == 3)
	{
		// enemies.erase(0 + enemies.begin());
		this->enemies[2]->update(dt, this->player);
		this->enemies[3]->update(dt, this->player);
		this->enemies[4]->update(dt, this->player);
		this->enemies[5]->update(dt, this->player);
	}
	if (this->map.getLevel() == 4)
	{
		this->enemies[6]->update(dt, this->player);
		this->enemies[7]->update(dt, this->player);
		this->enemies[8]->update(dt, this->player);
		this->enemies[9]->update(dt, this->player);
		this->enemies[10]->update(dt, this->player);
	}
	if (this->map.getLevel() == 5)
	{
		this->enemies[11]->update(dt, this->player);
		this->enemies[12]->update(dt, this->player);
		this->enemies[13]->update(dt, this->player);
		this->enemies[14]->update(dt, this->player);
		this->enemies[15]->update(dt, this->player);
	}
}

// Draw
void MainScreen::draw(sf::RenderWindow *window)
{

	// Draw map
	this->map.draw(window);

	// Draw player
	this->player.draw(window);

	if (this->map.getLevel() == 2)
	{
		this->enemies[0]->draw(window);
		this->enemies[1]->draw(window);
	}

	if (this->map.getLevel() == 3)
	{
		this->enemies[2]->draw(window);
		this->enemies[3]->draw(window);
		this->enemies[4]->draw(window);
		this->enemies[5]->draw(window);
	}

	if (this->map.getLevel() == 4)
	{
		this->enemies[6]->draw(window);
		this->enemies[7]->draw(window);
		this->enemies[8]->draw(window);
		this->enemies[9]->draw(window); //
		this->enemies[10]->draw(window);
	}

	if (this->map.getLevel() == 5)
	{
		this->enemies[11]->draw(window);
		this->enemies[12]->draw(window);
		this->enemies[13]->draw(window);
		this->enemies[14]->draw(window); //
		this->enemies[15]->draw(window);
	}

	if (this->player.isDead())
	{
		this->active = false;
		this->isPlayerDead = true;
	}
	else if (this->player.getHasExited())
	{
		this->active = false;
		// //Slow down program
		// std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}

bool MainScreen::getIsPlayerDead() const
{
	return this->isPlayerDead;
}