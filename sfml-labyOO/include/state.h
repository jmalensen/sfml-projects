#ifndef STATE_H
#define STATE_H

#include "stdHeader.h"

class State;

class StateData
{
public:
	StateData(){};

	// Variables
	sf::RenderWindow *window;
	std::stack<State *> *states;
};

class State
{
public:
	State(StateData *stateData);
	virtual ~State();

	// Accessors
	const bool &getQuit() const;

	void endState();

	// Functions
	virtual void update(const float &dt) = 0;
	virtual void draw(sf::RenderWindow *window = NULL) = 0;

protected:
	StateData *stateData;
	std::stack<State *> *states;
	sf::RenderWindow *window;

	bool quit;
};

#endif