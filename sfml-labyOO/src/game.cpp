#include "../include/game.h"

// Initializer functions
void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;

	// Background music
	if (!this->music.openFromFile("sounds/musicloop.ogg"))
	{
		std::cout << "Fail to load music file" << std::endl;
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
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initStates()
{
	// this->states.push();
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStates();

	// this->screensManager.showStartScreen();
	this->music.play();

	// Create the window
	//  this->window = new sf::RenderWindow(
	//  		sf::VideoMode(1500, 1260),
	//  		"Test working?");

	// this->window->create(sf::VideoMode(1500, 1260), "Test working?");
	// this->window->setFramerateLimit(60);

	// vm = sf::VideoMode::getFullscreenModes()[0];
	// // vm = sf::VideoMode::getDesktopMode();
	// window.create(vm, "Resizable Window laby");
	// std::cout << "Window size: " << vm.width << " " << vm.height << std::endl;

	// sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x * 2.f, window.getSize().y * 2.f));

	// view.setSize(vm.width * 2, vm.height * 2);
	// view.setCenter(vm.width, vm.height);
	// view.zoom(2.f);
	// window.setView(view);
	// window.setFramerateLimit(60);
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
