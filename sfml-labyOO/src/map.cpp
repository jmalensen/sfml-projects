#include "../include/map.h"

Map::Map(AssetsManager &assetsManager): assetsManager(assetsManager){
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
		"# # ###n####### # ### ###",
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
		"# #      # #    # #    ##",
		"# # #### #### # #### #  #",
		"# # #         #    # #  #",
		"# # ###### #### # # #####",
		"# # #t#    #    # # #k  #",
		"#  n# # #### # ## # # # #",
		"##### # ### ## #### ### #",
		"#     # #   #         # #",
		"###   #####    ######   #",
		"#   #     n#   #      ###",
		"################   ###  #",
		"#     ##        #       #",
		"### # ## ########### ## #",
		"#   #       #     ##    #",
		"########### ## ## #### ##",
		"#      #  #    #    #   #",
		"# ###   ##### ## ## ## ##",
		"# # ### # # #           #",
		"#########################",
	}};

	maze3 = {{
		"#########################",
		"#  #### #  ####  #### #e#",
		"# #    # # #    ##    ###",
		"# # #### #### # ## # #  #",
		"# #           #   t# #  #",
		"# # ###### #### # # #####",
		"# #####    #    # # #k  #",
		"#   # # #### # ## # # # #",
		"# ### # ### ## #### ### #",
		"#     # #   #         # #",
		"###   #####    ######   #",
		"#   #      #   ###    ###",
		"# #   #### #####   ###  #",
		"########        #       #",
		"### # ## ########### ## #",
		"#   #       #     ##    #",
		"##     #### ## ## #### ##",
		"# ######       #    #   #",
		"# #    ###  ##   ## ## ##",
		"# # ### # # #           #",
		"#########################",
	}};

	mazeList = {{"maze", maze}, {"maze2", maze2}, {"maze3", maze3}};
	levelNum = 1;

	///Textures via AssetsManager
	//Texture for the wall
	assetsManager.loadTexture("wallbrick", "images/wallbrick.png");
	wallSprite.setTexture(assetsManager.getTexture("wallbrick"));

	assetsManager.loadTexture("wallbrick2", "images/wallbrick2.png");
	wallSprite2.setTexture(assetsManager.getTexture("wallbrick2"));
	
	assetsManager.loadTexture("wallbrick3", "images/wallbrick3.png");
	wallSprite3.setTexture(assetsManager.getTexture("wallbrick3"));

	//Texture for the path
	assetsManager.loadTexture("pathtexture", "images/pathtexture.jpg");
	pathSprite.setTexture(assetsManager.getTexture("pathtexture"));

	assetsManager.loadTexture("pathtexture2", "images/pathtexture2.jpg");
	pathSprite2.setTexture(assetsManager.getTexture("pathtexture2"));
	assetsManager.loadTexture("pathtexture2trap", "images/pathtexture2t.jpg");
	pathSprite2Trap.setTexture(assetsManager.getTexture("pathtexture2trap"));

	assetsManager.loadTexture("pathtexture3", "images/pathtexture3.jpg");
	pathSprite3.setTexture(assetsManager.getTexture("pathtexture3"));
	assetsManager.loadTexture("pathtexture3trap", "images/pathtexture3t.jpg");
	pathSprite3Trap.setTexture(assetsManager.getTexture("pathtexture3trap"));

	//Texture for the background
	assetsManager.loadTexture("background", "images/background.jpg");
	backgroundI.setTexture(assetsManager.getTexture("background"));

	//Texture for the key
	assetsManager.loadTexture("key", "images/key.png");
	keySprite.setTexture(assetsManager.getTexture("key"));

	//Key animation
	rectSourceSpriteKey.left = 0;
	rectSourceSpriteKey.top = 0;
	rectSourceSpriteKey.width = 60;
	rectSourceSpriteKey.height = 60;
	keySprite.setTextureRect(rectSourceSpriteKey);


	//Texture for the nextLevel icon
	assetsManager.loadTexture("nextlevel", "images/nextlevel.png");
	nextLevelSprite.setTexture(assetsManager.getTexture("nextlevel"));

	//NextLevel animation
	rectSourceSpriteNextLevel.left = 0;
	rectSourceSpriteNextLevel.top = 0;
	rectSourceSpriteNextLevel.width = 60;
	rectSourceSpriteNextLevel.height = 60;
	nextLevelSprite.setTextureRect(rectSourceSpriteNextLevel);


	//Texture for the trophy icon
	assetsManager.loadTexture("trophy", "images/trophy.png");
	trophySprite.setTexture(assetsManager.getTexture("trophy"));

	//Trophy animation
	rectSourceSpriteTrophy.left = 0;
	rectSourceSpriteTrophy.top = 0;
	rectSourceSpriteTrophy.width = 60;
	rectSourceSpriteTrophy.height = 60;
	trophySprite.setTextureRect(rectSourceSpriteTrophy);


	//Text to display the level number
	assetsManager.loadFont("arial", "fonts/arial.ttf");
	text.setFont(assetsManager.getFont("arial"));

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

	//Set the string to display when level change
	text.setString("Level: " + std::to_string(levelNum) );
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
				if(levelNum == 1){
					wallSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					target.draw(wallSprite);
				} else if(levelNum == 2){
					wallSprite2.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					target.draw(wallSprite2);
				} else if(levelNum == 3){
					wallSprite3.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					target.draw(wallSprite3);
				}
			} else{
				if(levelNum == 1){
					pathSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					target.draw(pathSprite);
				} else if(levelNum == 2){
					pathSprite2.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					target.draw(pathSprite2);
				} else if(levelNum == 3){
					pathSprite3.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					target.draw(pathSprite3);
				}
			}

			if(maze[row][col] == 't'){
				if(levelNum == 2){
					pathSprite2Trap.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					target.draw(pathSprite2Trap);
				} else if(levelNum == 3){
					pathSprite3Trap.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					target.draw(pathSprite3Trap);
				}
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