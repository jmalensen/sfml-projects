#include "../include/map.h"
#include <iostream>

Map::Map(){
	//Initialize the map
	init();
}

void Map::init(){
	//Init map
	//Create a 2D array to represent the maze
	maze = {{
		"#########################",
		"#   #     #       #     #",
		"### ########### # # ### #",
		"# #        #    #   #   #",
		"# # ### ####### # ### ###",
		"# # #      # k# #####   #",
		"# # # ### ## ## #   ## ##",
		"#   # #   #     # #    ##",
		"##### # ### ####### ### #",
		"#     #     #     #   # #",
		"### ### ##### ### ###   #",
		"#   #      #   #      ###",
		"################# #######",
		"#    e##        #    #  #",
		"### #### ########### ## #",
		"#   #       #     ##    #",
		"########### ## ## #### ##",
		"# #    #  #    #    #   #",
		"# ####   ## # ## ## ## ##",
		"#   #  #    #     #    ##",
		"#########################",
	}};
}

//Get the value of a block in the map
char Map::operator()(int row, int col) const{
	return maze[row][col];
};
char& Map::operator()(int row, int col){
	return maze[row][col];
}

void Map::draw(sf::RenderTarget& target){

	//Texture for the wall
	sf::Texture wallTexture;
	if(!wallTexture.loadFromFile("images/wallbrick.png")){
		std::cout << "Failed to load wall texture" << std::endl;
	}
	sf::Sprite wallSprite;
	wallSprite.setTexture(wallTexture);

	//Texture for the path
	sf::Texture texturePath;
	if(!texturePath.loadFromFile("images/pathtexture.png")){
		std::cout << "Failed to load texturePath" << std::endl;
	}
	sf::Sprite pathSprite;
	pathSprite.setTexture(texturePath);

	//Texture for the background
	sf::Texture textureBackground;
	if(!textureBackground.loadFromFile("images/background.jpg")){
		std::cout << "Failed to load background texture" << std::endl;
	}
	sf::Sprite backgroundI(textureBackground);

	//Draw the map
	target.draw(backgroundI);

	//Draw maze
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col < COLS-1; col++){

			sf::RectangleShape block;
			block.setSize({BLOCK_SIZE, BLOCK_SIZE});
			block.setOutlineThickness(1);
			block.setOutlineColor(sf::Color::Black);
			block.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);

			if(maze[row][col] == '#'){
				wallSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				target.draw(wallSprite);
			} else{
				pathSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				target.draw(pathSprite);
			}

			if(maze[row][col] == 'k'){
				block.setFillColor(sf::Color::Black);
				target.draw(block);
			}

			if(maze[row][col] == 'e'){
				block.setFillColor(sf::Color::Green);
				target.draw(block);
			}
		}
	}
}