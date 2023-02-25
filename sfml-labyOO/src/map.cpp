#include "../include/map.h"

void Map::initVariables()
{
	// Init map
	// Create a 2D array to represent the maze
	this->m_maze = {{
			"###############################",
			"#   #     #       #     ##    #",
			"### ########### # # ### ## ## #",
			"# #        #    #   #   #  #  #",
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

	this->m_maze2 = {{
			"###############################",
			"#  #### #  ####  #### ##    ###",
			"# #      # #    # #    #  #   #",
			"# # #### #### # #### #   ## ###",
			"# # #         #    # #  ###  ##",
			"# # ###### #### # #  #######  #",
			"# # #t#    #    # # #   ##    #",
			"#   # # #### # ## # # # ## ####",
			"##### # ### ## ###  ## ##    k#",
			"#     # #    #        # ## # ##",
			"###   ######   ######   ## #  #",
			"#   #      n#  #      #### ## #",
			"################   ###  ##    #",
			"#     ##        #         ## ##",
			"### # ## #####    ## ## #    ##",
			"###############################",
	}};

	this->m_maze3 = {{
			"###############################",
			"#  #### #  ####  #### #      n#",
			"# #    # # #    ##    #########",
			"# # #### #### # ## # #  ##    #",
			"# #           #   t# #  #  ## #",
			"# # ###### #### # # ##### ##  #",
			"# #####    #    # # #k  #   ###",
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

	this->m_maze4 = {{
			"###############################",
			"#      #### ###     #       #k#",
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

	this->m_maze5 = {{
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
			"# #  ###### # ## ### ## # t  ##",
			"#   ####    # #      ##   # ###",
			"######## #### ##  ##### #####e#",
			"###############################",
	}};

	this->m_mazeList = {{"maze", this->m_maze}, {"maze2", this->m_maze2}, {"maze3", this->m_maze3}, {"maze4", this->m_maze4}, {"maze5", this->m_maze5}};
	this->m_levelNum = 1;

	/// Textures via AssetsManager
	// Texture for the wall
	this->m_assetsManager.loadTexture("wallbrick", "images/wallbrick.png");
	this->m_wallSprite.setTexture(this->m_assetsManager.getTexture("wallbrick"));

	this->m_assetsManager.loadTexture("wallbrick2", "images/wallbrick2.png");
	this->m_wallSprite2.setTexture(this->m_assetsManager.getTexture("wallbrick2"));

	this->m_assetsManager.loadTexture("wallbrick3", "images/wallbrick3.png");
	this->m_wallSprite3.setTexture(this->m_assetsManager.getTexture("wallbrick3"));

	this->m_assetsManager.loadTexture("wallbrick4", "images/wallbrick4.png");
	this->m_wallSprite4.setTexture(this->m_assetsManager.getTexture("wallbrick4"));

	this->m_assetsManager.loadTexture("wallbrick5", "images/wallbrick5.png");
	this->m_wallSprite5.setTexture(this->m_assetsManager.getTexture("wallbrick5"));

	// Texture for the path
	this->m_assetsManager.loadTexture("pathtexture", "images/pathtexture.jpg");
	this->m_pathSprite.setTexture(this->m_assetsManager.getTexture("pathtexture"));

	this->m_assetsManager.loadTexture("pathtexture2", "images/pathtexture2.jpg");
	this->m_pathSprite2.setTexture(this->m_assetsManager.getTexture("pathtexture2"));
	this->m_assetsManager.loadTexture("pathtexture2trap", "images/pathtexture2t.jpg");
	this->m_pathSprite2Trap.setTexture(this->m_assetsManager.getTexture("pathtexture2trap"));

	this->m_assetsManager.loadTexture("pathtexture3", "images/pathtexture3.jpg");
	this->m_pathSprite3.setTexture(this->m_assetsManager.getTexture("pathtexture3"));
	this->m_assetsManager.loadTexture("pathtexture3trap", "images/pathtexture3t.jpg");
	this->m_pathSprite3Trap.setTexture(this->m_assetsManager.getTexture("pathtexture3trap"));

	this->m_assetsManager.loadTexture("pathtexture4trap", "images/pathtexture4t.jpg");
	this->m_pathSprite4Trap.setTexture(this->m_assetsManager.getTexture("pathtexture4trap"));

	// Text to display the level number
	this->m_assetsManager.loadFont("arial", "fonts/arial.ttf");
	this->m_text.setFont(this->m_assetsManager.getFont("arial"));

	// Set the string to display
	this->m_text.setString("Level: " + std::to_string(this->m_levelNum));

	// Set the character size (in pixels, not points)
	this->m_text.setCharacterSize(36);

	// Set the m_text style
	this->m_text.setStyle(sf::Text::Bold);

	// Set the color
	this->m_text.setFillColor(sf::Color::White);
}

Map::Map(AssetsManager &assetsManager) : m_assetsManager(assetsManager), m_animKey(60, "images/key.png", Animation::NODIRECTION, 1), m_animNextLevel(60, "images/nextlevel.png", Animation::NODIRECTION, 1), m_animTrophy(60, "images/trophy.png", Animation::NODIRECTION, 1)
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
// Add velocity to the player so it can increase speed

// Get the value of a block in the map
char Map::operator()(int row, int col) const
{
	return this->m_maze[row][col];
}
char &Map::operator()(int row, int col)
{
	return this->m_maze[row][col];
}

void Map::setNewMaze(std::array<std::array<char, COLS>, ROWS> newMaze)
{
	this->m_maze = newMaze;
}
std::array<std::array<char, Map::COLS>, Map::ROWS> &Map::getMazeByName(std::string name)
{
	return this->m_mazeList[name];
}

int Map::getLevel()
{
	return this->m_levelNum;
}

void Map::setLevel(int newLevel)
{
	this->m_levelNum = newLevel;

	// Set the string to display when level change
	this->m_text.setString("Level: " + std::to_string(this->m_levelNum));
}

void Map::update(const float &dt)
{

	m_animKey.update(dt);
	m_animNextLevel.update(dt);
	m_animTrophy.update(dt);
}

void Map::draw(sf::RenderWindow *window)
{

	// Draw the map
	window->draw(this->m_backgroundI);

	float blockSize = gui::scale(BLOCK_SIZE, window);
	float factor = gui::getFactor(60, window);

	this->m_wallSprite.setScale(factor, factor);
	this->m_wallSprite2.setScale(factor, factor);
	this->m_wallSprite3.setScale(factor, factor);
	this->m_wallSprite4.setScale(factor, factor);
	this->m_wallSprite5.setScale(factor, factor);
	this->m_pathSprite.setScale(factor, factor);
	this->m_pathSprite2.setScale(factor, factor);
	this->m_pathSprite3.setScale(factor, factor);
	this->m_pathSprite2Trap.setScale(factor, factor);
	this->m_pathSprite3Trap.setScale(factor, factor);
	this->m_pathSprite4Trap.setScale(factor, factor);

	// Draw maze
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS - 1; col++)
		{

			if (this->m_maze[row][col] == '#')
			{
				if (this->m_levelNum == 1)
				{
					this->m_wallSprite.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_wallSprite);
				}
				else if (this->m_levelNum == 2)
				{
					this->m_wallSprite2.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_wallSprite2);
				}
				else if (this->m_levelNum == 3)
				{
					this->m_wallSprite3.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_wallSprite3);
				}
				else if (this->m_levelNum == 4)
				{
					this->m_wallSprite4.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_wallSprite4);
				}
				else if (this->m_levelNum == 5)
				{
					this->m_wallSprite5.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_wallSprite5);
				}
			}
			else
			{
				if (this->m_levelNum == 1)
				{
					this->m_pathSprite.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_pathSprite);
				}
				else if (this->m_levelNum == 2 || this->m_levelNum == 4)
				{
					this->m_pathSprite2.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_pathSprite2);
				}
				else if (this->m_levelNum == 3 || this->m_levelNum == 5)
				{
					this->m_pathSprite3.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_pathSprite3);
				}
			}

			if (this->m_maze[row][col] == 't')
			{
				if (this->m_levelNum == 2)
				{
					this->m_pathSprite2Trap.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_pathSprite2Trap);
				}
				else if (this->m_levelNum == 3)
				{
					this->m_pathSprite3Trap.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_pathSprite3Trap);
				}
				else if (this->m_levelNum == 4)
				{
					this->m_pathSprite4Trap.setPosition(col * blockSize, row * blockSize);
					window->draw(this->m_pathSprite4Trap);
				}
			}

			if (this->m_maze[row][col] == 'k')
			{
				m_animKey.setPosition(col * blockSize, row * blockSize);
				m_animKey.draw(window);
			}

			if (this->m_maze[row][col] == 'n')
			{
				m_animNextLevel.setPosition(col * blockSize, row * blockSize);
				m_animNextLevel.draw(window);
			}

			if (this->m_maze[row][col] == 'e')
			{
				m_animTrophy.setPosition(col * blockSize, row * blockSize);
				m_animTrophy.draw(window);
			}
		}
	}

	// Draw the text
	this->m_text.setPosition(10, 10);
	window->draw(this->m_text);
}