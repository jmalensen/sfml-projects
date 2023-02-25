#include "../include/game.h"

// Initializer functions
void Game::initVariables()
{
	this->m_p_window = nullptr;
	this->m_dt = 0.f;
}

void Game::initGraphicsSettings()
{
	this->m_gfxSettings.loadFromFile("config/graphics.ini");
}

void Game::initWindow()
{
	/*Creates a SFML window.*/

	if (this->m_gfxSettings.fullscreen)
	{
		this->m_p_window = new sf::RenderWindow(
				this->m_gfxSettings.resolution,
				this->m_gfxSettings.title,
				sf::Style::Fullscreen,
				this->m_gfxSettings.contextSettings);
	}
	else
	{
		this->m_p_window = new sf::RenderWindow(
				this->m_gfxSettings.resolution,
				this->m_gfxSettings.title,
				sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,
				this->m_gfxSettings.contextSettings);
	}
	this->m_p_window->setPosition(sf::Vector2i(0, 0));
	this->m_p_window->setFramerateLimit(this->m_gfxSettings.frameRateLimit);
	// this->m_p_window->setVerticalSyncEnabled(this->m_gfxSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs("config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->m_supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	// DEBUG REMOVE LATER!
	for (auto i : this->m_supportedKeys)
	{
		// std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initStateData()
{
	this->m_stateData.window = this->m_p_window;
	this->m_stateData.gfxSettings = &this->m_gfxSettings;
	this->m_stateData.supportedKeys = &this->m_supportedKeys;
	this->m_stateData.states = &this->m_states;
	this->m_stateData.elapsedTime = sf::Time::Zero;
}

void Game::initStates()
{
	this->m_states.push(new MainMenuState(&this->m_stateData));
}

Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	delete this->m_p_window;

	while (!this->m_states.empty())
	{
		delete this->m_states.top();
		this->m_states.pop();
	}
}

// Methods
void Game::endApplication()
{
	std::cout << "Ending Application!" << std::endl;
}

void Game::updateDt()
{
	/*Updates the m_dt variable with the time it takes to update and render one frame.*/
	this->m_dt = this->m_dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->m_p_window->pollEvent(this->m_sfEvent))
	{
		if (this->m_sfEvent.type == sf::Event::Closed)
		{
			this->m_p_window->close();
		}

		else if (this->m_sfEvent.type == sf::Event::Resized)
		{
			if (!this->m_states.empty())
			{
				this->m_states.top()->updateGuiSize(this->m_sfEvent);
			}
		}
	}
}

void Game::update()
{

	this->updateSFMLEvents();

	if (!this->m_states.empty())
	{
		if (this->m_p_window->hasFocus())
		{
			this->m_states.top()->update(this->m_dt);

			if (this->m_states.top()->getQuit())
			{
				this->m_states.top()->endState();
				delete this->m_states.top();
				this->m_states.pop();
			}
		}
	}
	// Application end
	else
	{
		this->endApplication();
		this->m_p_window->close();
	}
}

void Game::draw()
{

	// Clear the window with black color
	this->m_p_window->clear(sf::Color::Black);

	// Render items
	if (!this->m_states.empty())
	{
		this->m_states.top()->draw();
	}

	// Display the window
	this->m_p_window->display();
}

void Game::run()
{
	while (this->m_p_window->isOpen())
	{
		this->updateDt();
		this->update();
		this->draw();
	}
}
