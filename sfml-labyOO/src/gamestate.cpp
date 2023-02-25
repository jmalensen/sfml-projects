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
	if (!this->m_music.openFromFile("sounds/musicloop.ogg"))
	{
		// std::cout << "Fail to load music file" << std::endl;
	}

	this->m_music.setVolume(20);
	this->m_music.setLoop(true);

	this->m_enemies.push_back(std::make_shared<Enemy>(2, this->m_map, this->m_assetsManager, 5, 4, Enemy::HORIZONTAL, 5, getRandomNumber(18, 22), 30.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(2, this->m_map, this->m_assetsManager, 8, 7, Enemy::HORIZONTAL, 8, getRandomNumber(15, 24), 30.f));

	this->m_enemies.push_back(std::make_shared<Enemy>(3, this->m_map, this->m_assetsManager, 5, 6, Enemy::HORIZONTAL, 6, getRandomNumber(15, 21), 50.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(3, this->m_map, this->m_assetsManager, 8, 13, Enemy::HORIZONTAL, 8, getRandomNumber(16, 23), 50.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(3, this->m_map, this->m_assetsManager, 9, 10, Enemy::HORIZONTAL, 9, getRandomNumber(25, 30), 50.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(3, this->m_map, this->m_assetsManager, 16, 10, Enemy::HORIZONTAL, 16, getRandomNumber(24, 28), 50.f));

	this->m_enemies.push_back(std::make_shared<Enemy>(4, this->m_map, this->m_assetsManager, 5, 3, Enemy::HORIZONTAL, 5, getRandomNumber(13, 18), 60.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(4, this->m_map, this->m_assetsManager, 8, 6, Enemy::HORIZONTAL, 8, getRandomNumber(20, 26), 60.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(4, this->m_map, this->m_assetsManager, 9, 8, Enemy::HORIZONTAL, 9, getRandomNumber(16, 19), 60.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(4, this->m_map, this->m_assetsManager, 16, 10, Enemy::HORIZONTAL, 16, getRandomNumber(28, 31), 60.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(4, this->m_map, this->m_assetsManager, 7, 11, Enemy::HORIZONTAL, 7, getRandomNumber(20, 28), 60.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(4, this->m_map, this->m_assetsManager, 5, 13, Enemy::HORIZONTAL, 5, getRandomNumber(26, 32), 60.f));

	this->m_enemies.push_back(std::make_shared<Enemy>(5, this->m_map, this->m_assetsManager, 8, 5, Enemy::HORIZONTAL, 8, getRandomNumber(18, 24), 70.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(5, this->m_map, this->m_assetsManager, 5, 6, Enemy::HORIZONTAL, 5, getRandomNumber(17, 22), 70.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(5, this->m_map, this->m_assetsManager, 8, 8, Enemy::HORIZONTAL, 8, getRandomNumber(20, 29), 70.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(5, this->m_map, this->m_assetsManager, 9, 10, Enemy::HORIZONTAL, 9, getRandomNumber(15, 22), 70.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(5, this->m_map, this->m_assetsManager, 16, 10, Enemy::HORIZONTAL, 16, getRandomNumber(20, 23), 70.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(5, this->m_map, this->m_assetsManager, 7, 13, Enemy::HORIZONTAL, 7, getRandomNumber(22, 28), 70.f));
	this->m_enemies.push_back(std::make_shared<Enemy>(5, this->m_map, this->m_assetsManager, 10, 14, Enemy::HORIZONTAL, 10, getRandomNumber(16, 19), 70.f));

	this->paused = false;
	this->m_p_pmenu = new PauseMenu(this->stateData->gfxSettings->resolution);

	// Text to display the time
	if (!this->m_font.loadFromFile("fonts/arial.ttf"))
	{
		throw("ERROR::GAME::COULD NOT LOAD FONT");
	}
	this->m_timerText.setFont(this->m_font);

	// Set the string to display
	this->m_timerText.setString("Time elapsed: 0s");

	// Set the character size (in pixels, not points)
	this->m_timerText.setCharacterSize(36);

	// Set the text style
	this->m_timerText.setStyle(sf::Text::Bold);

	// Set the color
	this->m_timerText.setFillColor(sf::Color::White);
	this->m_timerText.setPosition(10, 40);

	// Initialize the timer
	this->m_startTime = this->m_clock.getElapsedTime();
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
		: State(stateData), m_assetsManager(m_assetsManager), m_map(m_assetsManager), m_player(m_map, m_assetsManager)
{
	this->initVariables();
	this->initKeybinds();

	// this->m_music.play();
}

GameState::~GameState()
{
	delete this->m_p_pmenu;
}

void GameState::updateGuiSize(sf::Event sfEvent)
{
	// Call the parent class
	State::updateGuiSize(sfEvent);
	delete this->m_p_pmenu;
	std::cout << "Update resolution !" << this->stateData->gfxSettings->resolution.width << " " << this->stateData->gfxSettings->resolution.height << std::endl;
	this->m_p_pmenu = new PauseMenu(this->stateData->gfxSettings->resolution);
}

void GameState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
		{
			// Store the time when pause is triggered
			this->m_pausedTime = this->m_clock.getElapsedTime();
			this->pauseState();
		}
		else
		{
			sf::Time resumeTime = this->m_clock.getElapsedTime();
			sf::Time pauseDuration = resumeTime - this->m_pausedTime;
			this->m_startTime += pauseDuration;
			this->unpauseState();
		}
	}
}

void GameState::update(const float &dt)
{
	// std::cout << "GameState::update" << std::endl;
	if (this->m_player.isDead())
	{
		this->m_music.stop();
		this->endState();
		this->states->push(new GameoverState(this->stateData));
	}
	else if (this->m_player.getHasExited())
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
		this->m_map.update(dt);

		// Update the game
		this->m_player.update(dt, this->m_enemies);

		if (this->m_map.getLevel() == 2)
		{
			this->m_enemies[0]->update(dt, this->m_player);
			this->m_enemies[1]->update(dt, this->m_player);
		}
		if (this->m_map.getLevel() == 3)
		{
			// m_enemies.erase(0 + m_enemies.begin());
			this->m_enemies[2]->update(dt, this->m_player);
			this->m_enemies[3]->update(dt, this->m_player);
			this->m_enemies[4]->update(dt, this->m_player);
			this->m_enemies[5]->update(dt, this->m_player);
		}
		if (this->m_map.getLevel() == 4)
		{
			this->m_enemies[6]->update(dt, this->m_player);
			this->m_enemies[7]->update(dt, this->m_player);
			this->m_enemies[8]->update(dt, this->m_player);
			this->m_enemies[9]->update(dt, this->m_player);
			this->m_enemies[10]->update(dt, this->m_player);
			this->m_enemies[11]->update(dt, this->m_player);
		}
		if (this->m_map.getLevel() == 5)
		{
			this->m_enemies[12]->update(dt, this->m_player);
			this->m_enemies[13]->update(dt, this->m_player);
			this->m_enemies[14]->update(dt, this->m_player);
			this->m_enemies[15]->update(dt, this->m_player);
			this->m_enemies[16]->update(dt, this->m_player);
			this->m_enemies[17]->update(dt, this->m_player);
			this->m_enemies[18]->update(dt, this->m_player);
		}

		// Time elapsed since the start of the game (updated by pause)
		sf::Time &elapsedTime = this->stateData->elapsedTime;
		elapsedTime = this->m_clock.getElapsedTime() - this->m_startTime;

		// Convert to minutes, seconds, and milliseconds
		int minutes = elapsedTime.asSeconds() / 60;
		int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;
		int milliseconds = elapsedTime.asMilliseconds() % 1000;

		std::string timerString = "Elapsed Time: " + std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(milliseconds);
		this->m_timerText.setString(timerString);
	}
	else
	{
		this->m_p_pmenu->update(dt);
	}
}

void GameState::draw(sf::RenderTarget *target)
{
	if (!target)
	{
		target = this->window;
	}

	// Draw map
	this->m_map.draw(this->window);

	// Draw player
	this->m_player.draw(this->window);

	if (this->m_map.getLevel() == 2)
	{
		this->m_enemies[0]->draw(this->window);
		this->m_enemies[1]->draw(this->window);
	}

	if (this->m_map.getLevel() == 3)
	{
		this->m_enemies[2]->draw(this->window);
		this->m_enemies[3]->draw(this->window);
		this->m_enemies[4]->draw(this->window);
		this->m_enemies[5]->draw(this->window);
	}

	if (this->m_map.getLevel() == 4)
	{
		this->m_enemies[6]->draw(this->window);
		this->m_enemies[7]->draw(this->window);
		this->m_enemies[8]->draw(this->window);
		this->m_enemies[9]->draw(this->window);
		this->m_enemies[10]->draw(this->window);
		this->m_enemies[11]->draw(this->window);
	}

	if (this->m_map.getLevel() == 5)
	{
		this->m_enemies[12]->draw(this->window);
		this->m_enemies[13]->draw(this->window);
		this->m_enemies[14]->draw(this->window);
		this->m_enemies[15]->draw(this->window);
		this->m_enemies[16]->draw(this->window);
		this->m_enemies[17]->draw(this->window);
		this->m_enemies[18]->draw(this->window);
	}

	// Elapsed timer
	this->window->draw(this->m_timerText);

	// Pause menu render
	if (this->paused)
	{
		this->m_p_pmenu->draw(this->window);
	}
}