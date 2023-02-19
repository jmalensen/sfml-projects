#include "../include/assetsmanager.h"

AssetsManager::AssetsManager() {}

AssetsManager::~AssetsManager() {}

bool AssetsManager::loadTexture(std::string name, std::string filepath)
{
	// Check if the texture has already been loaded
	if (this->textures.count(name) == 0)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(filepath))
		{
			// std::cout << "Failed to load texture: " << filepath << std::endl;
			throw "ERROR::ASSETSMANAGER::Failed to load texture:" + filepath;
			return false;
		}
		this->textures[name] = texture;
		// std::cout << "Load texture: " << name << " " << filepath << std::endl;
	}
	return true;
}

bool AssetsManager::loadSound(std::string name, std::string filepath)
{
	// check if the sound has already been loaded
	if (this->soundBuffers.count(name) == 0)
	{
		sf::SoundBuffer soundBuffer;
		if (!soundBuffer.loadFromFile(filepath))
		{
			// std::cout << "Failed to load sound: " << filepath << std::endl;
			throw "ERROR::ASSETSMANAGER::Failed to load sound:" + filepath;
			return false;
		}
		this->soundBuffers[name] = soundBuffer;
	}
	return true;
}

bool AssetsManager::loadFont(std::string name, std::string filepath)
{
	// check if the font has already been loaded
	if (this->fonts.count(name) == 0)
	{
		sf::Font font;
		if (!font.loadFromFile(filepath))
		{
			// std::cout << "Failed to load font: " << filepath << std::endl;
			throw "ERROR::ASSETSMANAGER::Failed to load font:" + filepath;
			return false;
		}
		this->fonts[name] = font;
	}
	return true;
}

sf::Texture &AssetsManager::getTexture(std::string name)
{
	if (this->textures.count(name) == 0)
	{
		throw std::invalid_argument("Texture not found : " + name);
	}
	return this->textures[name];
}

sf::SoundBuffer &AssetsManager::getSoundBuffer(std::string name)
{
	if (this->soundBuffers.count(name) == 0)
	{
		throw std::invalid_argument("Sound not found : " + name);
	}
	return this->soundBuffers[name];
}

sf::Sound AssetsManager::getSound(std::string name)
{
	sf::Sound sound(getSoundBuffer(name));
	return sound;
}

// sf::Music& AssetsManager::getMusic(std::string name){
// 	if(musics.count(name) == 0){
// 		throw std::invalid_argument("Music not found : " + name);
// 	}
// 	return musics[name];
// }

sf::Font &AssetsManager::getFont(std::string name)
{
	if (this->fonts.count(name) == 0)
	{
		throw std::invalid_argument("Font not found : " + name);
	}
	return this->fonts[name];
}

bool AssetsManager::addAnimation(std::string name, std::vector<sf::IntRect> frames)
{
	if (this->animations.count(name) != 0)
	{
		// std::cout << "Animation already exists : " << name << std::endl;
		return false;
	}
	this->animations[name] = frames;
	return true;
}