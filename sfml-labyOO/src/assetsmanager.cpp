#include "../include/assetsmanager.h"

AssetsManager::AssetsManager() {}

AssetsManager::~AssetsManager() {}

bool AssetsManager::loadTexture(std::string name, std::string filepath){
	// Check if the texture has already been loaded
	if (textures.count(name) == 0) {
		sf::Texture texture;
		if (!texture.loadFromFile(filepath)) {
			std::cout << "Failed to load sprite: " << filepath << std::endl;
			return false;
		}
		textures[name] = texture;
		std::cout << "Load sprite: " << name << " " << filepath  << std::endl;
	}
	return true;
}

bool AssetsManager::loadSound(std::string name, std::string filepath) {
	// check if the sound has already been loaded
	if (soundBuffers.count(name) == 0) {
		sf::SoundBuffer soundBuffer;
		if (!soundBuffer.loadFromFile(filepath)) {
			std::cout << "Failed to load sound: " << filepath << std::endl;
			return false;
		}
		soundBuffers[name] = soundBuffer;
	}
	return true;
}

sf::Texture& AssetsManager::getTexture(std::string name) {
	if(textures.count(name) == 0){
		throw std::invalid_argument("Texture not found : " + name);
	}
	return textures[name];
}

sf::SoundBuffer& AssetsManager::getSoundBuffer(std::string name) {
	if(soundBuffers.count(name) == 0){
		throw std::invalid_argument("Sound not found : " + name);
	}
	return soundBuffers[name];
}

sf::Sound AssetsManager::getSound(std::string name){
	sf::Sound sound(getSoundBuffer(name));
	return sound;
}

bool AssetsManager::addAnimation(std::string name, std::vector<sf::IntRect> frames){
	if(animations.count(name) != 0){
		std::cout << "Animation already exists : " << name << std::endl;
		return false;
	}
	animations[name] = frames;
	return true;
}

sf::IntRect AssetsManager::getAnimationFrame(std::string animationName,int frame){
	if(animations.count(animationName) == 0){
		throw std::invalid_argument("Animation not found : " + animationName);
	}
	return animations[animationName][frame];
}

int AssetsManager::getNumberOfFrames(std::string animationName){
	if(animations.count(animationName) == 0){
		throw std::invalid_argument("Animation not found : " + animationName);
	}
	return animations[animationName].size();
}