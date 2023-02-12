#include "../include/mainmenustate.h"

void MainMenuState::initBackground()
{
	this->background.setSize(
			sf::Vector2f(
					static_cast<float>(this->window->getSize().x),
					static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("images/bg1.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("fonts/arial.ttf"))
	{
		throw("ERROR::MAIN_MENU_STATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

	std::cout << ifs.good() << std::endl;

	if (ifs.is_open())
	{
		std::cout << "Open MainMenuState" << std::endl;
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			// std::cout << "after Open MainMenuState" << this->keybinds[key] << " " << this->supportedKeys->at(key2)
			// 					<< std::endl;
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(
			300.f, 420.f, 250.f, 50.f,
			&this->font, "New Game", 50,
			sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button(
			300.f, 520.f, 250.f, 50.f,
			&this->font, "Settings", 50,
			sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(
			300.f, 820.f, 250.f, 50.f,
			&this->font, "Quit", 50,
			sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
		: State(window, supportedKeys, states)
{
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float &dt)
{
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality.*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		std::cout << "GAME_STATE GameState!" << std::endl;
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	// Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));
	}

	// Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
}

void MainMenuState::update(const float &dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::drawButtons(sf::RenderTarget &target)
{
	for (auto &it : this->buttons)
	{
		it.second->draw(target);
	}
}

void MainMenuState::draw(sf::RenderTarget *target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->drawButtons(*target);
}