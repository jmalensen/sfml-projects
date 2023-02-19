#include "../include/game.h"

// Initializer functions
void Game::initVariables()
{
	this->window = nullptr;
	this->dt = 0.f;

	// Background music
	if (!this->music.openFromFile("sounds/musicloop.ogg"))
	{
		// std::cout << "Fail to load music file" << std::endl;
	}

	this->music.setVolume(20);
	this->music.setLoop(true);
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("config/graphics.ini");
}

void Game::initWindow()
{
	/*Creates a SFML window.*/

	if (this->gfxSettings.fullscreen)
	{
		this->window = new sf::RenderWindow(
				this->gfxSettings.resolution,
				this->gfxSettings.title,
				sf::Style::Fullscreen,
				this->gfxSettings.contextSettings);
	}
	else
	{
		this->window = new sf::RenderWindow(
				this->gfxSettings.resolution,
				this->gfxSettings.title,
				sf::Style::Titlebar | sf::Style::Close,
				this->gfxSettings.contextSettings);
	}
	this->window->setPosition(sf::Vector2i(0, 0));
	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	// this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
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
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	// DEBUG REMOVE LATER!
	for (auto i : this->supportedKeys)
	{
		// std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.elapsedTime = sf::Time::Zero;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();

	this->music.play();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

// Methods
void Game::endApplication()
{
	std::cout << "Ending Application!" << std::endl;
}

void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame.*/
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::update()
{

	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	// Application end
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::draw()
{

	// Clear the window with black color
	this->window->clear(sf::Color::Black);

	// Render items
	if (!this->states.empty())
	{
		this->states.top()->draw();
	}

	// Display the window
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->draw();
	}
}
