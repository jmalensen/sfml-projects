#include "../include/state.h"

State::State(StateData* stateData){
	this->stateData = stateData;
	this->window = stateData->window;
	this->states = stateData->states;
	this->quit = false;
}

State::~State(){
}

//Accessors
const bool & State::getQuit() const{
	return this->quit;
}

void State::endState(){
	this->quit = true;
}
