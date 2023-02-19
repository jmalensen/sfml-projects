#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include "stdHeader.h"

class AssetsManager
{
public:
	// Constructor and destructor
	AssetsManager();
	~AssetsManager();

	// Functions for loading and managing textures and sounds
	bool loadTexture(std::string name, std::string filepath);
	bool loadSound(std::string name, std::string filepath);
	bool loadFont(std::string name, std::string filepath);
	sf::Texture &getTexture(std::string name);
	sf::SoundBuffer &getSoundBuffer(std::string name);
	sf::Sound getSound(std::string name);
	sf::Font &getFont(std::string name);
	bool addAnimation(std::string name, std::vector<sf::IntRect> frames);

private:
	// Member variables for storing textures, sounds, animations, fonts
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, std::vector<sf::IntRect>> animations;
	std::map<std::string, sf::Font> fonts;
};

#endif // ASSETSMANAGER_H