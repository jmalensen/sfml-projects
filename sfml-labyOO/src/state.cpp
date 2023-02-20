#include "../include/state.h"

State::State(StateData *stateData)
{
	this->stateData = stateData;
	this->window = stateData->window;
	this->supportedKeys = stateData->supportedKeys;
	this->states = stateData->states;
	this->elapsedTime = stateData->elapsedTime;
	this->quit = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
}

State::~State()
{
}

const bool &State::getQuit() const
{
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

// Functions
void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateGuiSize(sf::Event sfEvent)
{
	// const sf::Vector2u oldSize = this->window->getSize();

	this->window->setSize(
			sf::Vector2u(
					static_cast<int>(sfEvent.size.width),
					static_cast<int>(sfEvent.size.height)));

	// Update the view to the new size of the window
	sf::FloatRect visibleArea(0.f, 0.f, sfEvent.size.width, sfEvent.size.height);
	this->window->setView(sf::View(visibleArea));

	std::cout << "Resolution event !" << sfEvent.size.width << " " << sfEvent.size.height << std::endl;

	// Update the size and position of relevant elements
	const sf::Vector2u newSize = this->window->getSize();
	// const float xScale = static_cast<float>(newSize.x) / oldSize.x;
	// const float yScale = static_cast<float>(newSize.y) / oldSize.y;

	// Update the resolution in the graphics settings
	this->stateData->gfxSettings->resolution.width = newSize.x;
	this->stateData->gfxSettings->resolution.height = newSize.y;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->quit = true;
	}
}

void State::updateMousePositions(sf::View *view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view)
	{
		this->window->setView(*view);
	}

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float &dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 100.f * dt;
	}
}