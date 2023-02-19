#ifndef STATE_H
#define STATE_H

#include "stdHeader.h"
#include "graphicssettings.h"

class State;
class GraphicsSettings;

class StateData
{
public:
	StateData(){};

	// Variables
	sf::RenderWindow *window;
	GraphicsSettings *gfxSettings;
	std::map<std::string, int> *supportedKeys;
	std::stack<State *> *states;
	sf::Time elapsedTime;
};

class State
{
public:
	State(StateData *stateData);
	virtual ~State();

	// Accessors
	const bool &getQuit() const;
	const bool getKeytime();

	virtual void checkForQuit();

	void endState();
	void pauseState();
	void unpauseState();
	virtual void updateMousePositions(sf::View *view = NULL);
	virtual void updateKeytime(const float &dt);
	virtual void update(const float &dt) = 0;
	virtual void draw(sf::RenderTarget *target = NULL) = 0;

protected:
	StateData *stateData;
	std::stack<State *> *states;
	sf::Time elapsedTime;
	sf::RenderWindow *window;
	std::map<std::string, int> *supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	std::vector<sf::Texture> textures;

	// Functions
	virtual void initKeybinds() = 0;

private:
};

#endif