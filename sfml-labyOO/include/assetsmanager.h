#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>

class AssetsManager {
	public:
	//Constructor and destructor
	AssetsManager();
	~AssetsManager();

	// Functions for loading and managing textures and sounds
	bool loadTexture(std::string name, std::string filepath);
	bool loadSound(std::string name, std::string filepath);
	sf::Texture& getTexture(std::string name);
	sf::SoundBuffer& getSoundBuffer(std::string name);
	sf::Sound getSound(std::string name);
	bool addAnimation(std::string name, std::vector<sf::IntRect> frames);
	sf::IntRect getAnimationFrame(std::string animationName,int frame);
	int getNumberOfFrames(std::string animationName);

	private:
	// Member variables for storing textures and sounds
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, std::vector<sf::IntRect>> animations;
};

#endif //ASSETSMANAGER_H