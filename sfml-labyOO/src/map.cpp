#include "../include/map.h"

Map::Map(AssetsManager &assetsManager): assetsManager(assetsManager), animKey(60, "images/key.png", 4, Animation::NODIRECTION, 1), animNextLevel(60, "images/nextlevel.png", 4, Animation::NODIRECTION, 1), animTrophy(60, "images/trophy.png", 4, Animation::NODIRECTION, 1){
	//Initialize the map
	init();
}

Map::~Map(){
}

// Done - Create traps which blocks areas (with resolution)
// traps which kill!!
// Done - Create ennemies
// Done - Create 3 more levels
// Multiplayer coop

void Map::init(){
	//Init map
	//Create a 2D array to represent the maze
	maze = {{
		"#########################",
		"#   #     #       #     #",
		"###n########### # # ### #",
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
		"# #      # #    # #    ##",
		"# # #### #### # #### #  #",
		"# # #         #    # #  #",
		"# # ###### #### # # #####",
		"# # #t#    #    # # #k  #",
		"#   # # #### # ## # # # #",
		"##### # ### ## #### ### #",
		"#     # #    #        # #",
		"###   ######   ######   #",
		"#   #      n#  #      ###",
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
		"#  #### #  ####  #### #n#",
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

	maze4 = {{
		"#########################",
		"#      #### ###     ###k#",
		"###### ##       ### ### #",
		"#      #### #######     #",
		"### ###   # ###     #####",
		"#   ### ### #   ###   ###",
		"# ##    ##  ##         ##",
		"# ## ##### ######### # ##",
		"#     #    ###       #  #",
		"# # #### ##  # ##########",
		"# ####   ## ## ##       #",
		"#      ###     #  ##### #",
		"### ###### ###### #  #  #",
		"###        ###    #    ##",
		"#   #######    #### t####",
		"## #      # ###       ###",
		"## # #### #  ## #########",
		"## #    # ## ## ##   #  #",
		"#  #### #    #  ### #####",
		"##      ######      #  n#",
		"#########################",
	}};

	maze5 = {{
		"#########################",
		"# #     ##     #     #  #",
		"# # # # ## ## ## ### # ##",
		"#   ##  #  #     #   #  #",
		"####   ### ####### #### #",
		"#    ##    ##    #      #",
		"#       ###   ## ## #####",
		"########### ####    #####",
		"#k ####     #############",
		"##      ######     ######",
		"## ######   ## ### #    #",
		"#  #      # #  #   # ## #",
		"# #  ###### # ## ### ## #",
		"#   ####    # ##     ## #",
		"######## #### ######### #",
		"##   ###      ####      #",
		"## #    # ########## ####",
		"## ####  ###            #",
		"##    ##     ## ### # ###",
		"#e#############     # ###",
		"#########################",
	}};

	mazeList = {{"maze", maze}, {"maze2", maze2}, {"maze3", maze3}, {"maze4", maze4}, {"maze5", maze5}};
	levelNum = 1;

	///Textures via AssetsManager
	//Texture for the wall
	assetsManager.loadTexture("wallbrick", "images/wallbrick.png");
	wallSprite.setTexture(assetsManager.getTexture("wallbrick"));

	assetsManager.loadTexture("wallbrick2", "images/wallbrick2.png");
	wallSprite2.setTexture(assetsManager.getTexture("wallbrick2"));
	
	assetsManager.loadTexture("wallbrick3", "images/wallbrick3.png");
	wallSprite3.setTexture(assetsManager.getTexture("wallbrick3"));
	
	assetsManager.loadTexture("wallbrick4", "images/wallbrick4.png");
	wallSprite4.setTexture(assetsManager.getTexture("wallbrick4"));
	
	assetsManager.loadTexture("wallbrick5", "images/wallbrick5.png");
	wallSprite5.setTexture(assetsManager.getTexture("wallbrick5"));

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

	assetsManager.loadTexture("pathtexture4trap", "images/pathtexture4t.jpg");
	pathSprite4Trap.setTexture(assetsManager.getTexture("pathtexture4trap"));

	// //Texture for the background
	// assetsManager.loadTexture("background", "images/background.jpg");
	// backgroundI.setTexture(assetsManager.getTexture("background"));


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

void Map::setNewMaze(std::array<std::array<char, COLS>, ROWS> newMaze){
	maze = newMaze;
}
std::array<std::array<char, Map::COLS>, Map::ROWS>& Map::getMazeByName(std::string name){
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

	// animKey.update(dt);
	// animNextLevel.update(dt);
	// animTrophy.update(dt);

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

void Map::draw(sf::RenderWindow& window){

	//Draw the map
	window.draw(backgroundI);

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
					window.draw(wallSprite);
				} else if(levelNum == 2){
					wallSprite2.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(wallSprite2);
				} else if(levelNum == 3){
					wallSprite3.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(wallSprite3);
				} else if(levelNum == 4){
					wallSprite4.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(wallSprite4);
				} else if(levelNum == 5){
					wallSprite5.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(wallSprite5);
				}
			} else{
				if(levelNum == 1){
					pathSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(pathSprite);
				} else if(levelNum == 2 || levelNum == 4){
					pathSprite2.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(pathSprite2);
				} else if(levelNum == 3 || levelNum == 5){
					pathSprite3.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(pathSprite3);
				}
			}

			if(maze[row][col] == 't'){
				if(levelNum == 2){
					pathSprite2Trap.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(pathSprite2Trap);
				} else if(levelNum == 3){
					pathSprite3Trap.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(pathSprite3Trap);
				} else if(levelNum == 4){
					pathSprite4Trap.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(pathSprite4Trap);
				}
			}

			if(maze[row][col] == 'k'){
				keySprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				window.draw(keySprite);
				// animKey.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				// animKey.draw(window);
			}

			if(maze[row][col] == 'n'){
				nextLevelSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				window.draw(nextLevelSprite);
				// animNextLevel.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				// animNextLevel.draw(window);
			}

			if(maze[row][col] == 'e'){
				trophySprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				window.draw(trophySprite);
				// animTrophy.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				// animTrophy.draw(window);
			}
		}
	}

	//Draw the text
	text.setPosition(10, 10);
	window.draw(text);
}