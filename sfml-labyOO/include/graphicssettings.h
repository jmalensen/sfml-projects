#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

#include "stdHeader.h"

class GraphicsSettings
{
public:
	GraphicsSettings();
	~GraphicsSettings();

	// Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	// Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};

#endif // GRAPHICSSETTINGS_H