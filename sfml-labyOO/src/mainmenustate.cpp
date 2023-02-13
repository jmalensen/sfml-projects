#include "../include/mainmenustate.h"

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

void MainMenuState::initGui()
{
	this->window->setPosition(sf::Vector2i(0, 0));
	const sf::VideoMode &vm = this->stateData->gfxSettings->resolution;

	this->background.setSize(
			sf::Vector2f(
					static_cast<float>(vm.width),
					static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("images/bg1.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	this->buttons["GAME_STATE"] = new gui::Button(
			gui::p2pX(15.6f, vm), gui::p2pY(40.f, vm),
			gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
			&this->font, "New Game", gui::calcCharSize(vm),
			sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color::White);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
			gui::p2pX(15.6f, vm), gui::p2pY(50.f, vm),
			gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
			&this->font, "Settings", gui::calcCharSize(vm),
			sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color::White);

	this->buttons["EXIT_STATE"] = new gui::Button(
			gui::p2pX(15.6f, vm), gui::p2pY(60.f, vm),
			gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
			&this->font, "Quit", gui::calcCharSize(vm),
			sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), sf::Color::White);
}

void MainMenuState::resetGui()
{
	/*
	 * Clears the GUI elements and re-initialises the GUI.
	 *
	 * @return void
	 */

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initGui();
}

MainMenuState::MainMenuState(StateData *stateData)
		: State(stateData)
{
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();

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
		it.second->update(this->mousePosWindow);
	}

	// New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		std::cout << "GAME_STATE GameState!" << std::endl;
		this->states->push(new GameState(this->stateData));
	}

	// Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->endState();
		this->states->push(new SettingsState(this->stateData));
	}

	// Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
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
	{
		target = this->window;
	}

	target->draw(this->background);

	this->drawButtons(*target);
}