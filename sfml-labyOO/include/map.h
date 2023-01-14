#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <array>

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
	std::array<std::array<char, 26>, 21>& getMaze2();

	//Initialization
	void init();

	//Draw the map
	void draw(sf::RenderTarget& target);

	private:
	static constexpr int ROWS = 21;
	static constexpr int COLS = 26;
	static constexpr int BLOCK_SIZE = 40;

	std::array<std::array<char, COLS>, ROWS> maze;
	std::array<std::array<char, COLS>, ROWS> maze2;
};

#endif // MAP_H