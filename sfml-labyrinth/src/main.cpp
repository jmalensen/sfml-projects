#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <array>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 840;
const int ROWS = 21;
const int COLS = 26;
const int BLOCK_SIZE = 40;

int main() {

	auto window = sf::RenderWindow{ { SCREEN_WIDTH, SCREEN_HEIGHT }, "SFML Labyrinth" };
	window.setFramerateLimit(60);

	//Create a 2D array to represent the maze
	std::array<std::array<char, COLS>, ROWS> maze {{
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

	sf::Texture wallTexture;
	if(!wallTexture.loadFromFile("images/wallbrick.png")){
		std::cout << "Failed to load wall texture" << std::endl;
		return 1;
	}
	sf::Sprite wallSprite;
	wallSprite.setTexture(wallTexture);

	//Texture for the background
	sf::Texture textureBackground;
	if(!textureBackground.loadFromFile("images/background.jpg")){
		std::cout << "Failed to load background texture" << std::endl;
		return 1;
	}
	sf::Sprite backgroundI(textureBackground);

	//Player position
	int playerX = 1;
	int playerY = 1;

	// //Texture for the player
	// sf::Texture texturePlayer;
	// if(!texturePlayer.loadFromFile("images/player.png")){
	// 	std::cout << "Failed to load player texture" << std::endl;
	// 	return 1;
	// }
	// sf::Sprite player(texturePlayer);


	//Texture for the player
	sf::Texture texturePlayer;
	if(!texturePlayer.loadFromFile("images/dino.png")){
		std::cout << "Failed to load dino texture" << std::endl;
		return 1;
	}
	sf::IntRect rectSourceSprite(0, 0, 104, 113);
	sf::Sprite player(texturePlayer, rectSourceSprite);
	player.setScale(0.33f, 0.33f);
	sf::Clock clock;

	//Sounds
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sounds/jump.wav")){
		return -1;
	}
	sf::Sound sound;
	sound.setBuffer(buffer);


	//Background music
	sf::Music music;
	music.openFromFile("sounds/musicloop.wav");
	music.setVolume(30);
	music.setLoop(true);

	music.play();
	// run the program as long as the window is open
	while (window.isOpen()) {

		// check all the window's events that were triggered since the last iteration of the loop
		for (auto event = sf::Event{}; window.pollEvent(event);) {

			if (event.type == sf::Event::Closed) {
				window.close();
				music.stop();
			}

			//Listen to keys pressed
			else if (event.type == sf::Event::KeyPressed){

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
					std::cout << "Going up" << std::endl;
					sound.play();
					if(maze[playerY-1][playerX] != '#'){
						playerY--;
					}
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
					std::cout << "Going down" << std::endl;
					sound.play();
					if(maze[playerY+1][playerX] != '#'){
						playerY++;
					}
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					std::cout << "Going left" << std::endl;
					sound.play();
					if(maze[playerY][playerX-1] != '#'){
						playerX--;
					}
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
					std::cout << "Going right" << std::endl;
					sound.play();
					if(maze[playerY][playerX+1] != '#'){
						playerX++;
					}
				}

				//If case is a key
				if(maze[playerY][playerX] == 'k'){
					maze[16][3] = ' ';
					std::cout << "Change content:" << maze[16][3] << ":P" << std::endl;
				}

				std::cout << playerY << " " << playerX << std::endl;

				if(maze[playerY][playerX] == 'e'){
					std::cout << "Exit!!" << std::endl;
					music.stop();
					window.close();
				}
			}
		}

		//Small animation of dino
		if (clock.getElapsedTime().asSeconds() > 0.40f){
      if (rectSourceSprite.left == 228)
        rectSourceSprite.left = 0;
      else
        rectSourceSprite.left += 114;

			std::cout << rectSourceSprite.left << std::endl;
      player.setTextureRect(rectSourceSprite);
      clock.restart();
    }

		window.clear();

		/// draw in window /////////////
		window.draw(backgroundI);

		//Draw walls
		for(int row = 0; row < ROWS; row++){
			for(int col = 0; col < COLS-1; col++){

				sf::RectangleShape block;
				block.setSize({BLOCK_SIZE, BLOCK_SIZE});
				block.setOutlineThickness(1);
				block.setOutlineColor(sf::Color::Black);
				block.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);

				if(maze[row][col] == '#'){
					//block.setFillColor(sf::Color::White);
					wallSprite.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					window.draw(wallSprite);
					//window.draw(block);
				} else{
					block.setFillColor(sf::Color::Cyan);
					window.draw(block);
				}

				if(maze[row][col] == 'k'){
					block.setFillColor(sf::Color::Black);
					window.draw(block);
				}

				if(maze[row][col] == 'e'){
					block.setFillColor(sf::Color::Green);
					window.draw(block);
				}

				if(maze[row][col] == '#'){

					// //Top walls
					// if(maze[row-1][col] != '#'){
					// 	wallSpriteTB.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					// 	window.draw(wallSpriteTB);
					// }
					// //Bottom walls
					// if(maze[row+1][col] != '#'){
					// 	wallSpriteTB.setPosition(col * BLOCK_SIZE, (row * BLOCK_SIZE)-2);
					// 	window.draw(wallSpriteTB);
					// }

					// //Left walls
					// if(maze[row][col-1] != '#'){
					// 	wallSpriteLR.setPosition(col * BLOCK_SIZE, row * BLOCK_SIZE);
					// 	window.draw(wallSpriteLR);
					// }
					// //Right walls
					// if(maze[row][col+1] != '#'){
					// 	wallSpriteLR.setPosition((col * BLOCK_SIZE)-2, row * BLOCK_SIZE);
					// 	window.draw(wallSpriteLR);
					// }
				}
			}
		}

		//Draw the player
		player.setPosition(playerX * BLOCK_SIZE+1, playerY * BLOCK_SIZE+1);
		window.draw(player);

		window.display();
	}

	return 0;
}