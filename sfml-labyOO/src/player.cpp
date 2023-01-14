#include "../include/player.h"
#include "../include/map.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <array>

Player::Player(Map& maze): maze(maze){
	//Initialize the player
	init();
}

void Player::init(){
	//Player position
	playerX = 1;
	playerY = 1;

	///Sounds
	//Movement sound
	if (!buffer.loadFromFile("sounds/jump.wav")){
		std::cout << "Fail to load sound file" << std::endl;
	}
	sound.setBuffer(buffer);

	//Unlock sound
	if (!buffer2.loadFromFile("sounds/unlock-sound.wav")){
		std::cout << "Fail to load unlock sound file" << std::endl;
	}
	unlockSound.setBuffer(buffer2);
	unlockSoundPlayed = false;

	//Win sound
	if (!buffer3.loadFromFile("sounds/win.wav")){
		std::cout << "Fail to load win sound file" << std::endl;
	}
	winSound.setBuffer(buffer3);
	exit = false;

	//Texture for the player
	if(!texturePlayer.loadFromFile("images/dino.png")){
		std::cout << "Failed to load dino texture" << std::endl;
	}

	//Player animation
	rectSourceSpritePlayer.left = 0;
	rectSourceSpritePlayer.top = 0;
	rectSourceSpritePlayer.width = 104;
	rectSourceSpritePlayer.height = 113;

	player.setTexture(texturePlayer);
	player.setTextureRect(rectSourceSpritePlayer);
	player.setScale(0.33f, 0.33f);
}

//Getters
int Player::getPlayerX() const{
	return playerX;
}
int Player::getPlayerY() const{
	return playerY;
}

//Setters
void Player::setPlayerX(int newX){
	playerX = newX;
}
void Player::setPlayerY(int newY){
	playerY = newY;
}

bool Player::getExited() const{
	return exit;
}

void Player::update(sf::Time dt){

	///Needed to keep the same clock for the player (not moving too fast)
	//Player speed (pixels/s)
	static const float speed = 40.f;

	//Delay between 2 moves
	static const sf::Time moveDelay = sf::seconds(10.f / speed);

	//Last time player moved
	static sf::Time lastMove = sf::Time::Zero;
	lastMove += dt;

	//Handle movement of player
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		if(lastMove >= moveDelay){
			std::cout << "Going up" << std::endl;
			sound.play();
			if(maze.operator()(playerY-1, playerX) != '#'){
				playerY--;
				lastMove = sf::Time::Zero;
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		if(lastMove >= moveDelay){
			std::cout << "Going down" << std::endl;
			sound.play();
			if(maze.operator()(playerY+1, playerX) != '#'){
				playerY++;
				lastMove = sf::Time::Zero;
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		if(lastMove >= moveDelay){
			std::cout << "Going left" << std::endl;
			sound.play();
			if(maze.operator()(playerY, playerX-1) != '#'){
				playerX--;
				lastMove = sf::Time::Zero;
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if(lastMove >= moveDelay){
			std::cout << "Going right" << std::endl;
			sound.play();
			if(maze.operator()(playerY, playerX+1) != '#'){
				playerX++;
				lastMove = sf::Time::Zero;
			}
		}
	}

	//If case is a key
	if(maze.operator()(playerY, playerX) == 'k' && unlockSoundPlayed != true){
		maze.operator()(playerY, playerX) = ' ';
		maze.operator()(16, 3) = ' ';
		unlockSound.play();
		std::cout << "Change content:" << maze.operator()(playerY, playerX) << ":P" << std::endl;
		unlockSoundPlayed = true;
	}

	std::cout << playerY << " " << playerX << std::endl;

	//Sound of the win for the exit
	if(maze.operator()(playerY, playerX) == 'e' && exit != true){
		winSound.play();
		std::cout << "Exit!!" << std::endl;
		//exit = true;

		maze.setNewMaze( maze.getMaze2() );

		//reset unlock sound
		unlockSoundPlayed = false;
	}


	///Small animation of dino
	//Duration of the frame
	static float frameDuration = 0.4f;

	//Current time needed for the delta time
	static float currentTime = 0.0f;
	currentTime += dt.asSeconds();
	
	if(currentTime >= frameDuration){
		//Set rectangle left position
		if (rectSourceSpritePlayer.left == 228){
			rectSourceSpritePlayer.left = 0;
		}
		else{
			rectSourceSpritePlayer.left += 114;
		}

		currentTime = 0;

		std::cout << rectSourceSpritePlayer.left << std::endl;

		//Set the rectangle so we see the movement
		player.setTextureRect(rectSourceSpritePlayer);
	}
}

void Player::draw(sf::RenderTarget& target){

	player.setPosition(playerX * maze.getBlockSize()+1, playerY * maze.getBlockSize()+1);

	//Draw the player
	target.draw(player);
}