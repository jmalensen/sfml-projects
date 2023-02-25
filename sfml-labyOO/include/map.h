#ifndef MAP_H
#define MAP_H

#include "stdHeader.h"
#include "assetsmanager.h"
#include "animation.h"
#include "gui.h"

class AssetsManager;
class Animation;

class Map
{
public:
	// Constructor and destructor
	Map(AssetsManager &assetsManager);
	~Map();

	static constexpr int ROWS = 16; // 21;
	static constexpr int COLS = 32; // 26;
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
	void update(const float &dt);

	// Draw the map
	void draw(sf::RenderWindow *window);

private:
	AssetsManager &m_assetsManager;

	std::array<std::array<char, COLS>, ROWS> m_maze;
	std::array<std::array<char, COLS>, ROWS> m_maze2;
	std::array<std::array<char, COLS>, ROWS> m_maze3;
	std::array<std::array<char, COLS>, ROWS> m_maze4;
	std::array<std::array<char, COLS>, ROWS> m_maze5;

	int m_levelNum;

	// Store the multiple mazes (dynamic names aren't possible in c++)
	std::unordered_map<std::string, std::array<std::array<char, COLS>, ROWS>> m_mazeList;

	/// Textures
	// Texture for the wall
	sf::Sprite m_wallSprite;
	sf::Sprite m_wallSprite2;
	sf::Sprite m_wallSprite3;
	sf::Sprite m_wallSprite4;
	sf::Sprite m_wallSprite5;

	// Texture for the path
	sf::Sprite m_pathSprite;
	sf::Sprite m_pathSprite2;
	sf::Sprite m_pathSprite2Trap;
	sf::Sprite m_pathSprite3;
	sf::Sprite m_pathSprite3Trap;
	sf::Sprite m_pathSprite4Trap;
	sf::Sprite m_pathSprite5Trap;

	// Texture for the background
	sf::Sprite m_backgroundI;

	// Texture for the key
	Animation m_animKey;

	// Texture for the nextLevel icon
	Animation m_animNextLevel;

	// Texture for the trophy icon
	Animation m_animTrophy;

	/// Text to display the level number
	sf::Text m_text;

	// Initialization
	void initVariables();
};

#endif // MAP_H