#include "../include/gamestate.h"

// Initialization
void GameState::initVariables()
{
	this->enemies.push_back(std::make_shared<Enemy>(1, this->map, this->assetsManager, 5, 4, Enemy::HORIZONTAL, 5, 16, 30.f));
	this->enemies.push_back(std::make_shared<Enemy>(2, this->map, this->assetsManager, 8, 7, Enemy::HORIZONTAL, 8, 22, 30.f));

	this->enemies.push_back(std::make_shared<Enemy>(3, this->map, this->assetsManager, 5, 6, Enemy::HORIZONTAL, 6, 15, 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(4, this->map, this->assetsManager, 8, 13, Enemy::HORIZONTAL, 8, 21, 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(5, this->map, this->assetsManager, 9, 10, Enemy::HORIZONTAL, 9, 28, 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(6, this->map, this->assetsManager, 16, 10, Enemy::HORIZONTAL, 16, 24, 50.f));

	this->enemies.push_back(std::make_shared<Enemy>(7, this->map, this->assetsManager, 5, 6, Enemy::HORIZONTAL, 5, 14, 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(8, this->map, this->assetsManager, 8, 12, Enemy::HORIZONTAL, 8, 25, 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(9, this->map, this->assetsManager, 9, 10, Enemy::HORIZONTAL, 9, 19, 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(10, this->map, this->assetsManager, 20, 10, Enemy::HORIZONTAL, 20, 24, 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(11, this->map, this->assetsManager, 5, 12, Enemy::HORIZONTAL, 5, 30, 60.f));

	this->enemies.push_back(std::make_shared<Enemy>(12, this->map, this->assetsManager, 5, 6, Enemy::HORIZONTAL, 5, 13, 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(13, this->map, this->assetsManager, 8, 5, Enemy::HORIZONTAL, 8, 23, 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(14, this->map, this->assetsManager, 9, 10, Enemy::HORIZONTAL, 9, 19, 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(15, this->map, this->assetsManager, 16, 10, Enemy::HORIZONTAL, 16, 21, 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(16, this->map, this->assetsManager, 5, 13, Enemy::HORIZONTAL, 5, 27, 70.f));

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

GameState::GameState(StateData *stateData)
		: State(stateData), assetsManager(assetsManager), map(assetsManager), player(map, assetsManager)
{
	this->initVariables();
	this->initKeybinds();
}

GameState::~GameState()
{
	delete this->pmenu;
}

void GameState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::update(const float &dt)
{
	// std::cout << "GameState::update" << std::endl;
	if (this->player.isDead())
	{
		this->endState();
		this->states->push(new GameoverState(this->stateData));
	}
	else if (this->player.getHasExited())
	{
		this->endState();
		this->states->push(new EndGameState(this->stateData));
	}

	this->updateKeytime(dt);
	this->updateInput(dt);

	// Unpaused update
	if (!this->paused)
	{

		// Update the maze
		this->map.update(dt);

		// Update the game
		this->player.update(dt, this->enemies);

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
	else
	{
		this->pmenu->update(dt);
	}
}

void GameState::draw(sf::RenderTarget *target)
{
	if (!target)
	{
		target = this->window;
	}

	// Draw map
	this->map.draw(this->window);

	// Draw player
	this->player.draw(this->window);

	if (this->map.getLevel() == 2)
	{
		this->enemies[0]->draw(this->window);
		this->enemies[1]->draw(this->window);
	}

	if (this->map.getLevel() == 3)
	{
		this->enemies[2]->draw(this->window);
		this->enemies[3]->draw(this->window);
		this->enemies[4]->draw(this->window);
		this->enemies[5]->draw(this->window);
	}

	if (this->map.getLevel() == 4)
	{
		this->enemies[6]->draw(this->window);
		this->enemies[7]->draw(this->window);
		this->enemies[8]->draw(this->window);
		this->enemies[9]->draw(this->window); //
		this->enemies[10]->draw(this->window);
	}

	if (this->map.getLevel() == 5)
	{
		this->enemies[11]->draw(this->window);
		this->enemies[12]->draw(this->window);
		this->enemies[13]->draw(this->window);
		this->enemies[14]->draw(this->window); //
		this->enemies[15]->draw(this->window);
	}

	// Pause menu render
	if (this->paused)
	{
		this->pmenu->draw(this->window);
	}
}