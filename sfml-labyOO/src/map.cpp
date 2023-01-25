#include "../include/map.h"

Map::Map(AssetsManager &assets): assets(assets){
	//Initialize the map
	init();
}

Map::~Map(){
}

// Create traps which blocks areas (with resolution)
// traps which kill!!
// Create ennemies
// Create 3 more levels
// Multiplayer coop

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
		"# # #         #    # #  #",
		"# # ###### #### # # #####",
		"# # # #    #    # # #k  #",
		"# # # # #### # ## # # # #",
		"##### # ### ## #### ### #",
		"#     # #   #         # #",
		"###   #####    ######   #",
		"#   #     e#   #      ###",
		"################   ###  #",
		"#     ##        #       #",
		"### # ## ########### ## #",
		"#   #       #     ##    #",
		"########### ## ## #### ##",
		"#      #  #    #    #  t#",
		"# ###   ##### ## ## ## ##",
		"# # ### # # #           #",
		"#########################",
	}};

	mazeList = {{"maze", maze}, {"maze2", maze2}};
	levelNum = 1;

	///Textures via AssetsManager
	//Texture for the wall
	assets.loadTexture("wallbrick", "images/wallbrick.png");
	wallSprite.setTexture(assets.getTexture("wallbrick"));

	//Texture for the path
	assets.loadTexture("pathtexture", "images/pathtexture.png");
	pathSprite.setTexture(assets.getTexture("pathtexture"));

	//Texture for the background
	assets.loadTexture("background", "images/background.jpg");
	backgroundI.setTexture(assets.getTexture("background"));

	//Texture for the key
	assets.loadTexture("key", "images/key.png");
	keySprite.setTexture(assets.getTexture("key"));

	//Key animation
	rectSourceSpriteKey.left = 0;
	rectSourceSpriteKey.top = 0;
	rectSourceSpriteKey.width = 60;
	rectSourceSpriteKey.height = 60;

	keySprite.setTextureRect(rectSourceSpriteKey);


	//Texture for the nextLevel icon
	if(!textureNextLevelIcon.loadFromFile("images/nextlevel.png")){
		std::cout << "Failed to load next level icon texture" << std::endl;
	}

	//NextLevel animation
	rectSourceSpriteNextLevel.left = 0;
	rectSourceSpriteNextLevel.top = 0;
	rectSourceSpriteNextLevel.width = 60;
	rectSourceSpriteNextLevel.height = 60;

	nextLevelSprite.setTexture(textureNextLevelIcon);
	nextLevelSprite.setTextureRect(rectSourceSpriteNextLevel);

	//Texture for the trophy icon
	if(!textureTrophyIcon.loadFromFile("images/trophy.png")){
		std::cout << "Failed to load trophy icon texture" << std::endl;
	}

	//Trophy animation
	rectSourceSpriteTrophy.left = 0;
	rectSourceSpriteTrophy.top = 0;
	rectSourceSpriteTrophy.width = 60;
	rectSourceSpriteTrophy.height = 60;

	trophySprite.setTexture(textureTrophyIcon);
	trophySprite.setTextureRect(rectSourceSpriteTrophy);

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

void Map::update(sf::Time dt){

	///Small animation of key
	//Duration of the frame
	static float frameDuration = 0.2f;
	static float frameDurationNL = 0.1f;

	//Current time needed for the delta time
	static float currentTime = 0.0f;
	currentTime += dt.asSeconds();

	static float currentTimeNL = 0.0f;
	currentTimeNL += dt.asSeconds();

	static float currentTimeE = 0.0f;
	currentTimeE += dt.asSeconds();
	
	if(currentTime >= frameDuration){
		//Set rectangle left position
		if (rectSourceSpriteKey.left == 120){
			rectSourceSpriteKey.left = 0;
		}
		else{
			rectSourceSpriteKey.left += 60;
		}

		currentTime = 0;

		//Set the rectangle so we see the movement
		keySprite.setTextureRect(rectSourceSpriteKey);
	}

	if(currentTimeNL >= frameDurationNL){
		//Set rectangle left position
		if (rectSourceSpriteNextLevel.left == 240){
			rectSourceSpriteNextLevel.left = 0;
		}
		else{
			rectSourceSpriteNextLevel.left += 60;
		}

		currentTimeNL = 0;

		//Set the rectangle so we see the movement
		nextLevelSprite.setTextureRect(rectSourceSpriteNextLevel);
	}

	if(currentTimeE >= frameDurationNL){
		//Set rectangle left position
		if (rectSourceSpriteTrophy.left == 300){
			rectSourceSpriteTrophy.left = 0;
		}
		else{
			rectSourceSpriteTrophy.left += 60;
		}

		currentTimeE = 0;

		//Set the rectangle so we see the movement
		trophySprite.setTextureRect(rectSourceSpriteTrophy);
	}
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

			if(maze[row][col] == 't'){
				target.draw(block);
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