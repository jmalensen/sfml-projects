#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <unordered_map>

class Map{
	public:
	//Constructor
	Map();

	//Getters
	int getRows() const{
		return ROWS;
	};
	int getCols() const{
		return COLS;
	};
	int getBlockSize() const{
		return BLOCK_SIZE;
	}

	//Get the value of a block in the map
	char operator()(int row, int col) const;
	char& operator()(int row, int col);

	void setNewMaze(std::array<std::array<char, 26>, 21> newMaze);
	std::array<std::array<char, 26>, 21>& getMazeByName(std::string name);

	int getLevel();
	void setLevel(int newLevel);

	//Initialization
	void init();

	//Update maze
	void update(sf::Time dt);

	//Draw the map
	void draw(sf::RenderTarget& target);

	private:
	static constexpr int ROWS = 21;
	static constexpr int COLS = 26;
	static constexpr int BLOCK_SIZE = 60;

	std::array<std::array<char, COLS>, ROWS> maze;
	std::array<std::array<char, COLS>, ROWS> maze2;

	int levelNum;

	//Store the multiple mazes (dynamic names aren't possible in c++)
	std::unordered_map<std::string, std::array<std::array<char, COLS>, ROWS>> mazeList;

	///Textures
	//Texture for the wall
	sf::Texture wallTexture;
	sf::Sprite wallSprite;

	//Texture for the path
	sf::Texture texturePath;
	sf::Sprite pathSprite;

	//Texture for the background
	sf::Texture textureBackground;
	sf::Sprite backgroundI;

	//Texture for the key
	sf::Texture textureKey;
	sf::IntRect rectSourceSpriteKey;
	sf::Sprite keySprite;

	//Texture for the nextLevel icon
	sf::Texture textureNextLevelIcon;
	sf::IntRect rectSourceSpriteNextLevel;
	sf::Sprite nextLevelSprite;

	//Texture for the trophy icon
	sf::Texture textureTrophyIcon;
	sf::Sprite trophySprite;

	///Text to display the level number
	sf::Text text;
	//Select the font
	sf::Font font;
};

#endif // MAP_H