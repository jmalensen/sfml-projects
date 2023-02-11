#ifndef STATE_H
#define STATE_H

#include "stdHeader.h"

class State;
class GraphicsSettings;

class State
{
public:
	State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
	virtual ~State();

	// Accessors
	const bool &getQuit() const;
	const bool getKeytime();

	virtual void checkForQuit();

	void endState();
	void pauseState();
	void unpauseState();
	virtual void updateMousePositions();
	virtual void update(const float &dt) = 0;
	virtual void draw(sf::RenderTarget *target = NULL) = 0;

protected:
	std::stack<State *> *states;
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