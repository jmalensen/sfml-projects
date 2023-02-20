#include "../include/gamestate.h"

int GameState::getRandomNumber(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

// Initialization
void GameState::initVariables()
{
	// Background music
	if (!this->music.openFromFile("sounds/musicloop.ogg"))
	{
		// std::cout << "Fail to load music file" << std::endl;
	}

	this->music.setVolume(20);
	this->music.setLoop(true);

	this->enemies.push_back(std::make_shared<Enemy>(2, this->map, this->assetsManager, 5, 4, Enemy::HORIZONTAL, 5, getRandomNumber(13, 19), 30.f));
	this->enemies.push_back(std::make_shared<Enemy>(2, this->map, this->assetsManager, 8, 7, Enemy::HORIZONTAL, 8, getRandomNumber(15, 24), 30.f));

	this->enemies.push_back(std::make_shared<Enemy>(3, this->map, this->assetsManager, 5, 6, Enemy::HORIZONTAL, 6, getRandomNumber(12, 18), 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(3, this->map, this->assetsManager, 8, 13, Enemy::HORIZONTAL, 8, getRandomNumber(16, 23), 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(3, this->map, this->assetsManager, 9, 10, Enemy::HORIZONTAL, 9, getRandomNumber(25, 30), 50.f));
	this->enemies.push_back(std::make_shared<Enemy>(3, this->map, this->assetsManager, 16, 10, Enemy::HORIZONTAL, 16, getRandomNumber(19, 26), 50.f));

	this->enemies.push_back(std::make_shared<Enemy>(4, this->map, this->assetsManager, 5, 6, Enemy::HORIZONTAL, 5, getRandomNumber(12, 16), 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(4, this->map, this->assetsManager, 8, 12, Enemy::HORIZONTAL, 8, getRandomNumber(19, 26), 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(4, this->map, this->assetsManager, 9, 8, Enemy::HORIZONTAL, 9, getRandomNumber(13, 19), 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(4, this->map, this->assetsManager, 20, 10, Enemy::HORIZONTAL, 20, getRandomNumber(22, 28), 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(4, this->map, this->assetsManager, 5, 12, Enemy::HORIZONTAL, 5, getRandomNumber(26, 32), 60.f));
	this->enemies.push_back(std::make_shared<Enemy>(4, this->map, this->assetsManager, 7, 11, Enemy::HORIZONTAL, 7, getRandomNumber(20, 28), 60.f));

	this->enemies.push_back(std::make_shared<Enemy>(5, this->map, this->assetsManager, 5, 6, Enemy::HORIZONTAL, 5, getRandomNumber(13, 16), 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(5, this->map, this->assetsManager, 8, 5, Enemy::HORIZONTAL, 8, getRandomNumber(15, 24), 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(5, this->map, this->assetsManager, 9, 10, Enemy::HORIZONTAL, 9, getRandomNumber(13, 19), 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(5, this->map, this->assetsManager, 16, 10, Enemy::HORIZONTAL, 16, getRandomNumber(18, 23), 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(5, this->map, this->assetsManager, 7, 13, Enemy::HORIZONTAL, 7, getRandomNumber(22, 28), 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(5, this->map, this->assetsManager, 12, 14, Enemy::HORIZONTAL, 12, getRandomNumber(16, 19), 70.f));
	this->enemies.push_back(std::make_shared<Enemy>(5, this->map, this->assetsManager, 10, 8, Enemy::HORIZONTAL, 10, getRandomNumber(20, 29), 70.f));

	this->paused = false;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution);

	// Text to display the time
	if (!this->font.loadFromFile("fonts/arial.ttf"))
	{
		throw("ERROR::GAME::COULD NOT LOAD FONT");
	}
	this->timerText.setFont(this->font);

	// Set the string to display
	this->timerText.setString("Time elapsed: 0s");

	// Set the character size (in pixels, not points)
	this->timerText.setCharacterSize(36);

	// Set the text style
	this->timerText.setStyle(sf::Text::Bold);

	// Set the color
	this->timerText.setFillColor(sf::Color::White);
	this->timerText.setPosition(10, 40);

	// Initialize the timer
	this->startTime = this->clock.getElapsedTime();
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

	this->music.play();
}

GameState::~GameState()
{
	delete this->pmenu;
}

void GameState::updateGuiSize(sf::Event sfEvent)
{
	// Call the parent class
	State::updateGuiSize(sfEvent);
	delete this->pmenu;
	std::cout << "Update resolution !" << this->stateData->gfxSettings->resolution.width << " " << this->stateData->gfxSettings->resolution.height << std::endl;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution);
}

void GameState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
		{
			// Store the time when pause is triggered
			this->pausedTime = this->clock.getElapsedTime();
			this->pauseState();
		}
		else
		{
			sf::Time resumeTime = this->clock.getElapsedTime();
			sf::Time pauseDuration = resumeTime - this->pausedTime;
			this->startTime += pauseDuration;
			this->unpauseState();
		}
	}
}

void GameState::update(const float &dt)
{
	// std::cout << "GameState::update" << std::endl;
	if (this->player.isDead())
	{
		this->music.stop();
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
			this->enemies[11]->update(dt, this->player);
		}
		if (this->map.getLevel() == 5)
		{
			this->enemies[12]->update(dt, this->player);
			this->enemies[13]->update(dt, this->player);
			this->enemies[14]->update(dt, this->player);
			this->enemies[15]->update(dt, this->player);
			this->enemies[16]->update(dt, this->player);
			this->enemies[17]->update(dt, this->player);
			this->enemies[18]->update(dt, this->player);
		}

		// Time elapsed since the start of the game (updated by pause)
		sf::Time &elapsedTime = this->stateData->elapsedTime;
		elapsedTime = this->clock.getElapsedTime() - this->startTime;

		// Convert to minutes, seconds, and milliseconds
		int minutes = elapsedTime.asSeconds() / 60;
		int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;
		int milliseconds = elapsedTime.asMilliseconds() % 1000;

		std::string timerString = "Elapsed Time: " + std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(milliseconds);
		this->timerText.setString(timerString);
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
		this->enemies[9]->draw(this->window);
		this->enemies[10]->draw(this->window);
		this->enemies[11]->draw(this->window);
	}

	if (this->map.getLevel() == 5)
	{
		this->enemies[12]->draw(this->window);
		this->enemies[13]->draw(this->window);
		this->enemies[14]->draw(this->window);
		this->enemies[15]->draw(this->window);
		this->enemies[16]->draw(this->window);
		this->enemies[17]->draw(this->window);
		this->enemies[18]->draw(this->window);
	}

	// Elapsed timer
	this->window->draw(this->timerText);

	// Pause menu render
	if (this->paused)
	{
		this->pmenu->draw(this->window);
	}
}