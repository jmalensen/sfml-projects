#include "../include/gamestate.h"

// Constructors / Destructors
GameState::GameState(StateData *stateData)
		: State(stateData)
{
}

GameState::~GameState()
{
}

// Functions
void GameState::updateView(const float &dt)
{
}

void GameState::update(const float &dt)
{
}

void GameState::draw(sf::RenderWindow *window)
{
}
