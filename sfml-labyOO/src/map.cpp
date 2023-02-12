#include "../include/map.h"

void Map::initVariables()
{
	// Init map
	// Create a 2D array to represent the maze
	this->maze = {{
			"###############################",
			"#   #     #       #     ##    #",
			"### ########### # # ### ## ## #",
			"# #n       #    #   #   #  #  #",
			"# # ### ####### # ### ### ## ##",
			"# # #      # k# #####     ##  #",
			"# # # ### ## ## #   ######### #",
			"#   # #   #     # #    ###    #",
			"##### # ### ####### ### ### ###",
			"#     #     #     #   # ###  ##",
			"### ### ##### ### ###   #### ##",
			"#   # n#   #   #      # ## # ##",
			"####  ###########  ####   ## ##",
			"#   ####        ##   # ##  # ##",
			"###      ######    # ## ##   ##",
			"###############################",
	}};

	this->maze2 = {{
			"###############################",
			"#  #### #  ####  #### ##    ###",
			"# #      # #    # #    #  #   #",
			"# # #### #### # #### #   ## ###",
			"# # #         #    # #  ###  ##",
			"# # ###### #### # #  #######  #",
			"# # #t#    #    # # #   ##    #",
			"#n  # # #### # ## # # # ## ####",
			"##### # ### ## ###  ## ##    k#",
			"#     # #    #        # ## # ##",
			"###   ######   ######   ## #  #",
			"#   #      n#  #      #### ## #",
			"################   ###  ##    #",
			"#     ##        #         ## ##",
			"### # ## #####    ## ## #    ##",
			"###############################",
	}};

	this->maze3 = {{
			"###############################",
			"#  #### #  ####  #### #      n#",
			"# #    # # #    ##    #########",
			"# # #### #### # ## # #  ##    #",
			"# #           #   t# #  #  ## #",
			"# # ###### #### # # ##### ##  #",
			"#n#####    #    # # #k  #   ###",
			"#   # # #### # ## # # # ###  ##",
			"# ### # ### ## #### ### ##    #",
			"#     # #   #           ## # ##",
			"###   #####    #######     #  #",
			"#   #      #   ###    #### # ##",
			"# #   #### #####   ###  #    ##",
			"########        #       #### ##",
			"### # ## ######   ## ##       #",
			"###############################",
	}};

	this->maze4 = {{
			"###############################",
			"#    n #### ###     #       #k#",
			"###### ##       ### ### # # # #",
			"#      #### #######     # #   #",
			"### ###   # ###     ###########",
			"#   ### ### #   ###   #    ####",
			"# ##    ##  ##          ## #  #",
			"# ## ##### ######### # ##  # ##",
			"#     #    ###       #  # #   #",
			"# # #### ##  # ##########   # #",
			"# ####   ## ## ##       ## ## #",
			"#      ###     #  ##### ##    #",
			"##########t ##### #  #  #### ##",
			"####        ##    #    #   #  #",
			"#n  ########   ####  #   #    #",
			"###############################",
	}};

	this->maze5 = {{
			"###############################",
			"# #     ##     #     #    #   #",
			"# # # # ## ## ## ### # ##   # #",
			"#   ##  #  #     #   #  #######",
			"####   ### ####### #### ##    #",
			"#    ##    ##    #      ##  # #",
			"#       ###   ## ## ### ####  #",
			"########### ####    #   ##    #",
			"#k ####     #########      ####",
			"##      ######     ## #########",
			"## ######   ## ### #    #    ##",
			"#  #      # #  #   # ## # ## ##",
			"# #  ###### # ## ### ## #    ##",
			"#   ####    # #      ##   # ###",
			"######## #### ##  ##### #####e#",
			"###############################",
	}};

	this->mazeList = {{"maze", this->maze}, {"maze2", this->maze2}, {"maze3", this->maze3}, {"maze4", this->maze4}, {"maze5", this->maze5}};
	this->levelNum = 1;

	/// Textures via AssetsManager
	// Texture for the wall
	this->assetsManager.loadTexture("wallbrick", "images/wallbrick.png");
	this->wallSprite.setTexture(this->assetsManager.getTexture("wallbrick"));

	this->assetsManager.loadTexture("wallbrick2", "images/wallbrick2.png");
	this->wallSprite2.setTexture(this->assetsManager.getTexture("wallbrick2"));

	this->assetsManager.loadTexture("wallbrick3", "images/wallbrick3.png");
	this->wallSprite3.setTexture(this->assetsManager.getTexture("wallbrick3"));

	this->assetsManager.loadTexture("wallbrick4", "images/wallbrick4.png");
	this->wallSprite4.setTexture(this->assetsManager.getTexture("wallbrick4"));

	this->assetsManager.loadTexture("wallbrick5", "images/wallbrick5.png");
	this->wallSprite5.setTexture(this->assetsManager.getTexture("wallbrick5"));

	// Texture for the path
	this->assetsManager.loadTexture("pathtexture", "images/pathtexture.jpg");
	this->pathSprite.setTexture(this->assetsManager.getTexture("pathtexture"));

	this->assetsManager.loadTexture("pathtexture2", "images/pathtexture2.jpg");
	this->pathSprite2.setTexture(this->assetsManager.getTexture("pathtexture2"));
	this->assetsManager.loadTexture("pathtexture2trap", "images/pathtexture2t.jpg");
	this->pathSprite2Trap.setTexture(this->assetsManager.getTexture("pathtexture2trap"));

	this->assetsManager.loadTexture("pathtexture3", "images/pathtexture3.jpg");
	this->pathSprite3.setTexture(this->assetsManager.getTexture("pathtexture3"));
	this->assetsManager.loadTexture("pathtexture3trap", "images/pathtexture3t.jpg");
	this->pathSprite3Trap.setTexture(this->assetsManager.getTexture("pathtexture3trap"));

	this->assetsManager.loadTexture("pathtexture4trap", "images/pathtexture4t.jpg");
	this->pathSprite4Trap.setTexture(this->assetsManager.getTexture("pathtexture4trap"));

	// Text to display the level number
	this->assetsManager.loadFont("arial", "fonts/arial.ttf");
	this->text.setFont(this->assetsManager.getFont("arial"));

	// Set the string to display
	this->text.setString("Level: " + std::to_string(this->levelNum));

	// Set the character size (in pixels, not points)
	this->text.setCharacterSize(36);

	// Set the text style
	this->text.setStyle(sf::Text::Bold);

	// Set the color
	this->text.setFillColor(sf::Color::White);
}

Map::Map(AssetsManager &assetsManager) : assetsManager(assetsManager), animKey(60, "images/key.png", Animation::NODIRECTION, 1), animNextLevel(60, "images/nextlevel.png", Animation::NODIRECTION, 1), animTrophy(60, "images/trophy.png", Animation::NODIRECTION, 1)
{
	// Initialize the map
	this->initVariables();
}

Map::~Map()
{
}

// Done - Create traps which blocks areas (with resolution)
// traps which kill!!
// Done - Create ennemies
// Done - Create 3 more levels
// Multiplayer coop

// Get the value of a block in the map
char Map::operator()(int row, int col) const
{
	return this->maze[row][col];
}
char &Map::operator()(int row, int col)
{
	return this->maze[row][col];
}

void Map::setNewMaze(std::array<std::array<char, COLS>, ROWS> newMaze)
{
	this->maze = newMaze;
}
std::array<std::array<char, Map::COLS>, Map::ROWS> &Map::getMazeByName(std::string name)
{
	return this->mazeList[name];
}

int Map::getLevel()
{
	return this->levelNum;
}

void Map::setLevel(int newLevel)
{
	this->levelNum = newLevel;

	// Set the string to display when level change
	this->text.setString("Level: " + std::to_string(this->levelNum));
}

void Map::update(const float &dt)
{

	animKey.update(dt);
	animNextLevel.update(dt);
	animTrophy.update(dt);
}

void Map::draw(sf::RenderWindow *window)
{

	// Draw the map
	window->draw(this->backgroundI);

	// Draw maze
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS - 1; col++)
		{

			sf::RectangleShape block;
			block.setSize({BLOCK_SIZE, BLOCK_SIZE});
			block.setOutlineThickness(1);
			block.setOutlineColor(sf::Color::Black);
			block.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);

			if (this->maze[row][col] == '#')
			{
				if (this->levelNum == 1)
				{
					this->wallSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->wallSprite);
				}
				else if (this->levelNum == 2)
				{
					this->wallSprite2.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->wallSprite2);
				}
				else if (this->levelNum == 3)
				{
					this->wallSprite3.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->wallSprite3);
				}
				else if (this->levelNum == 4)
				{
					this->wallSprite4.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->wallSprite4);
				}
				else if (this->levelNum == 5)
				{
					this->wallSprite5.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->wallSprite5);
				}
			}
			else
			{
				if (this->levelNum == 1)
				{
					this->pathSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->pathSprite);
				}
				else if (this->levelNum == 2 || this->levelNum == 4)
				{
					this->pathSprite2.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->pathSprite2);
				}
				else if (this->levelNum == 3 || this->levelNum == 5)
				{
					this->pathSprite3.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->pathSprite3);
				}
			}

			if (this->maze[row][col] == 't')
			{
				if (this->levelNum == 2)
				{
					this->pathSprite2Trap.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->pathSprite2Trap);
				}
				else if (this->levelNum == 3)
				{
					this->pathSprite3Trap.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->pathSprite3Trap);
				}
				else if (this->levelNum == 4)
				{
					this->pathSprite4Trap.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window->draw(this->pathSprite4Trap);
				}
			}

			if (this->maze[row][col] == 'k')
			{
				animKey.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				animKey.draw(window);
			}

			if (this->maze[row][col] == 'n')
			{
				animNextLevel.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				animNextLevel.draw(window);
			}

			if (this->maze[row][col] == 'e')
			{
				animTrophy.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
				animTrophy.draw(window);
			}
		}
	}

	// Draw the text
	this->text.setPosition(10, 10);
	window->draw(this->text);
}