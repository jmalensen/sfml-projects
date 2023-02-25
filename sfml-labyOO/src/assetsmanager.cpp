#include "../include/assetsmanager.h"

AssetsManager::AssetsManager() {}

AssetsManager::~AssetsManager() {}

bool AssetsManager::loadTexture(std::string name, std::string filepath)
{
	// Check if the texture has already been loaded
	if (this->m_textures.count(name) == 0)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(filepath))
		{
			// std::cout << "Failed to load texture: " << filepath << std::endl;
			throw "ERROR::ASSETSMANAGER::Failed to load texture:" + filepath;
			return false;
		}
		this->m_textures[name] = texture;
		// std::cout << "Load texture: " << name << " " << filepath << std::endl;
	}
	return true;
}

bool AssetsManager::loadSound(std::string name, std::string filepath)
{
	// check if the sound has already been loaded
	if (this->m_soundBuffers.count(name) == 0)
	{
		sf::SoundBuffer soundBuffer;
		if (!soundBuffer.loadFromFile(filepath))
		{
			// std::cout << "Failed to load sound: " << filepath << std::endl;
			throw "ERROR::ASSETSMANAGER::Failed to load sound:" + filepath;
			return false;
		}
		this->m_soundBuffers[name] = soundBuffer;
	}
	return true;
}

bool AssetsManager::loadFont(std::string name, std::string filepath)
{
	// check if the font has already been loaded
	if (this->m_fonts.count(name) == 0)
	{
		sf::Font font;
		if (!font.loadFromFile(filepath))
		{
			// std::cout << "Failed to load font: " << filepath << std::endl;
			throw "ERROR::ASSETSMANAGER::Failed to load font:" + filepath;
			return false;
		}
		this->m_fonts[name] = font;
	}
	return true;
}

sf::Texture &AssetsManager::getTexture(std::string name)
{
	if (this->m_textures.count(name) == 0)
	{
		throw std::invalid_argument("Texture not found : " + name);
	}
	return this->m_textures[name];
}

sf::SoundBuffer &AssetsManager::getSoundBuffer(std::string name)
{
	if (this->m_soundBuffers.count(name) == 0)
	{
		throw std::invalid_argument("Sound not found : " + name);
	}
	return this->m_soundBuffers[name];
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
	if (this->m_fonts.count(name) == 0)
	{
		throw std::invalid_argument("Font not found : " + name);
	}
	return this->m_fonts[name];
}

bool AssetsManager::addAnimation(std::string name, std::vector<sf::IntRect> frames)
{
	if (this->m_animations.count(name) != 0)
	{
		// std::cout << "Animation already exists : " << name << std::endl;
		return false;
	}
	this->m_animations[name] = frames;
	return true;
}