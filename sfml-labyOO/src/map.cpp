#include "../include/map.h"

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
		"#    n##        #    #  #",
		"### #### ########### ## #",
		"#   #       #     ##    #",
		"########### ## ## #### ##",
		"# #    #  #    #    #   #",
		"# ####   ## # ## ## ## ##",
		"#   #  #    #     #    ##",
		"#########################",
	}};

	maze2 = {{
		"#########################",
		"#  #### #  ####  #### ###",
		"# #    # # #    # #    ##",
		"# # #### #### # #### #  #",
		"# # #    #    #    # #  #",
		"# # # #### #### # # #####",
		"# # # #    #    # # #   #",
		"# # # # #### #### # # # #",
		"##### # ### ## #### ### #",
		"#     #     #         # #",
		"###   #####    ######   #",
		"#   #     e#   #      ###",
		"################   ###  #",
		"#     ##        #       #",
		"### # ## ########### ## #",
		"#   #       #     ##    #",
		"########### ## ## #### ##",
		"#      #  #    #    #  k#",
		"# ###   ##### ## ## ## ##",
		"# # ### # # #           #",
		"#########################",
	}};

	mazeList = {{"maze", maze}, {"maze2", maze2}};
	levelNum = 1;

	//Texture for the wall
	if(!wallTexture.loadFromFile("images/wallbrick.png")){
		std::cout << "Failed to load wall texture" << std::endl;
	}
	wallSprite.setTexture(wallTexture);

	//Texture for the path
	if(!texturePath.loadFromFile("images/pathtexture.png")){
		std::cout << "Failed to load texturePath" << std::endl;
	}
	pathSprite.setTexture(texturePath);

	//Texture for the background
	if(!textureBackground.loadFromFile("images/background.jpg")){
		std::cout << "Failed to load background texture" << std::endl;
	}
	backgroundI.setTexture(textureBackground);

	//Texture for the key
	if(!textureKey.loadFromFile("images/key.png")){
		std::cout << "Failed to load key texture" << std::endl;
	}
	keySprite.setTexture(textureKey);

	//Texture for the nextLevel icon
	if(!textureNextLevelIcon.loadFromFile("images/nextlevel.png")){
		std::cout << "Failed to load next level icon texture" << std::endl;
	}
	nextLevelSprite.setTexture(textureNextLevelIcon);

	//Texture for the trophy icon
	if(!textureTrophyIcon.loadFromFile("images/trophy.png")){
		std::cout << "Failed to load trophy icon texture" << std::endl;
	}
	trophySprite.setTexture(textureTrophyIcon);

	//Text to display the level number
	if (!font.loadFromFile("fonts/arial.ttf")){
		std::cout << "Failed to load font" << std::endl;
	}
	text.setFont(font);

	//Set the string to display
	text.setString("Level: " + std::to_string(levelNum) );

	//Set the character size (in pixels, not points)
	text.setCharacterSize(36);

	//Set the text style
	text.setStyle(sf::Text::Bold);

	//Set the color
	text.setFillColor(sf::Color::White);
}

//Get the value of a block in the map
char Map::operator()(int row, int col) const{
	return maze[row][col];
};
char& Map::operator()(int row, int col){
	return maze[row][col];
}

void Map::setNewMaze(std::array<std::array<char, 26>, 21> newMaze){
	maze = newMaze;
}
std::array<std::array<char, 26>, 21>& Map::getMazeByName(std::string name){
	return mazeList[name];
}

int Map::getLevel(){
	return levelNum;
}

void Map::setLevel(int newLevel){
	levelNum = newLevel;
}

void Map::draw(sf::RenderTarget& target){

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
				keySprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				target.draw(keySprite);
			}

			if(maze[row][col] == 'n'){
				nextLevelSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				target.draw(nextLevelSprite);
			}

			if(maze[row][col] == 'e'){
				trophySprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				target.draw(trophySprite);
			}
		}
	}

	//Draw the text
	text.setPosition(10, 10);
	target.draw(text);
}