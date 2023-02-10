#ifndef MAP_H
#define MAP_H

#include "stdHeader.h"
#include "assetsmanager.h"
#include "animation.h"

class AssetsManager;
class Animation;

class Map
{
public:
	// Constructor and destructor
	Map(AssetsManager &assetsManager);
	~Map();

	static constexpr int ROWS = 21;
	static constexpr int COLS = 26;
	static constexpr int BLOCK_SIZE = 60;

	// Getters
	int getRows() const
	{
		return ROWS;
	};
	int getCols() const
	{
		return COLS;
	};
	int getBlockSize() const
	{
		return BLOCK_SIZE;
	}

	// Get the value of a block in the map
	char operator()(int row, int col) const;
	char &operator()(int row, int col);

	void setNewMaze(std::array<std::array<char, COLS>, ROWS> newMaze);
	std::array<std::array<char, COLS>, ROWS> &getMazeByName(std::string name);

	int getLevel();
	void setLevel(int newLevel);

	// Update maze
	void update(sf::Time dt);

	// Draw the map
	void draw(sf::RenderWindow *window);

private:
	AssetsManager &assetsManager;

	std::array<std::array<char, COLS>, ROWS> maze;
	std::array<std::array<char, COLS>, ROWS> maze2;
	std::array<std::array<char, COLS>, ROWS> maze3;
	std::array<std::array<char, COLS>, ROWS> maze4;
	std::array<std::array<char, COLS>, ROWS> maze5;

	int levelNum;

	// Store the multiple mazes (dynamic names aren't possible in c++)
	std::unordered_map<std::string, std::array<std::array<char, COLS>, ROWS>> mazeList;

	/// Textures
	// Texture for the wall
	sf::Sprite wallSprite;
	sf::Sprite wallSprite2;
	sf::Sprite wallSprite3;
	sf::Sprite wallSprite4;
	sf::Sprite wallSprite5;

	// Texture for the path
	sf::Sprite pathSprite;
	sf::Sprite pathSprite2;
	sf::Sprite pathSprite2Trap;
	sf::Sprite pathSprite3;
	sf::Sprite pathSprite3Trap;
	sf::Sprite pathSprite4Trap;
	sf::Sprite pathSprite5Trap;

	// Texture for the background
	sf::Sprite backgroundI;

	// Texture for the key
	Animation animKey;
	sf::IntRect rectSourceSpriteKey;
	sf::Sprite keySprite;

	// Texture for the nextLevel icon
	Animation animNextLevel;
	sf::IntRect rectSourceSpriteNextLevel;
	sf::Sprite nextLevelSprite;

	// Texture for the trophy icon
	Animation animTrophy;
	sf::IntRect rectSourceSpriteTrophy;
	sf::Sprite trophySprite;

	/// Text to display the level number
	sf::Text text;
	// Select the font
	sf::Font font;

	// Initialization
	void initVariables();
};

#endif // MAP_H