#include "../include/endgamestate.h"

// Initialization
void EndGameState::initVariables()
{
	this->lastMove = 0.f;

	// Texture for the background
	const sf::VideoMode &vm = this->stateData->gfxSettings->resolution;

	this->background.setSize(
			sf::Vector2f(
					static_cast<float>(vm.width),
					static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("images/winscreen.jpg"))
	{
		throw "ERROR::ENDGAME_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	// Win sound
	this->assetsManager.loadSound("win", "sounds/win.ogg");
	this->winSound = (this->assetsManager.getSound("win"));
	this->winSound.setVolume(40);
}

void EndGameState::initKeybinds()
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

EndGameState::EndGameState(StateData *stateData)
		: State(stateData)
{
	this->initVariables();
	this->initKeybinds();
}

EndGameState::~EndGameState()
{
}

void EndGameState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->endState();
		this->window->close();
	}
}

void EndGameState::update(const float &dt)
{
	this->updateInput(dt);

	// This part is needed otherwise sound might not be played
	// Delay between 2 moves
	static float moveDelay = 0.2f; // 5.f / speed;

	// Last time player moved
	this->lastMove += dt;

	if (this->lastMove >= moveDelay && !this->playedWinSound)
	{
		this->winSound.play();
		this->lastMove = 0.f;
		this->playedWinSound = true;
	}
}

void EndGameState::draw(sf::RenderTarget *target)
{
	if (!target)
	{
		target = this->window;
	}

	// Draw the screen
	this->window->draw(this->background);
}