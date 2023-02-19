#include "../include/gameoverstate.h"

// Initialization
void GameoverState::initVariables()
{
}

void GameoverState::initFonts()
{
	if (!this->font.loadFromFile("fonts/arial.ttf"))
	{
		throw("ERROR::GAMEOVER_STATE::COULD NOT LOAD FONT");
	}
}

void GameoverState::initKeybinds()
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

void GameoverState::initGui()
{
	// Texture for the background
	const sf::VideoMode &vm = this->stateData->gfxSettings->resolution;

	this->background.setSize(
			sf::Vector2f(
					static_cast<float>(vm.width),
					static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("images/gameoverscreen.jpg"))
	{
		throw "ERROR::GAMEOVER_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	this->buttons["TRYAGAIN"] = new gui::Button(
			gui::p2pX(44.f, vm), gui::p2pY(60.f, vm),
			gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
			&this->font, "Try again ?", gui::calcCharSize(vm),
			sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->timerText.setFont(this->font);

	// Set the character size (in pixels, not points)
	this->timerText.setCharacterSize(gui::calcCharSize(vm));

	// Set the text style
	this->timerText.setStyle(sf::Text::Bold);

	// Set the color
	this->timerText.setFillColor(sf::Color::White);
	this->timerText.setPosition(gui::p2pX(36.f, vm), gui::p2pY(70.f, vm));

	sf::Time elapsedTime = this->stateData->elapsedTime;
	// Convert to minutes, seconds, and milliseconds
	int minutes = elapsedTime.asSeconds() / 60;
	int seconds = static_cast<int>(elapsedTime.asSeconds()) % 60;
	int milliseconds = elapsedTime.asMilliseconds() % 1000;

	std::string timerString = "Your Time: " + std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(milliseconds);
	this->timerText.setString(timerString);
}

GameoverState::GameoverState(StateData *stateData)
		: State(stateData)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

GameoverState::~GameoverState()
{
}

void GameoverState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->endState();
		this->window->close();
	}
}

void GameoverState::updateGui(const float &dt)
{
	/*Updates all the gui elements in the state and handle their functionality.*/
	// Buttons
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// Button functionality
	// Restart the game
	if (this->buttons["TRYAGAIN"]->isPressed())
	{
		this->endState();
		this->states->push(new GameState(this->stateData));
	}
}

void GameoverState::update(const float &dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void GameoverState::drawGui(sf::RenderTarget &target)
{
	for (auto &it : this->buttons)
	{
		it.second->draw(target);
	}
}

void GameoverState::draw(sf::RenderTarget *target)
{
	if (!target)
	{
		target = this->window;
	}

	// Draw the screen
	this->window->draw(this->background);

	// Elapsed timer
	this->window->draw(this->timerText);

	this->drawGui(*target);
}