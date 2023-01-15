#include "../include/player.h"
#include "../include/map.h"

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
	sound.setVolume(10);

	//Hurt sound
	if (!bufferHurt.loadFromFile("sounds/hitHurt.wav")){
		std::cout << "Fail to load hurt sound file" << std::endl;
	}
	hurtSound.setBuffer(bufferHurt);
	hurtSound.setVolume(10);

	//Unlock sound
	if (!buffer2.loadFromFile("sounds/unlock-sound.wav")){
		std::cout << "Fail to load unlock sound file" << std::endl;
	}
	unlockSound.setBuffer(buffer2);
	unlockSoundPlayed = false;

	//Exit level sound
	if (!buffer3.loadFromFile("sounds/exitlevel.wav")){
		std::cout << "Fail to load exit level sound file" << std::endl;
	}
	exitLevelSound.setBuffer(buffer3);
	nextLevelPlayed = false;

	//Win sound
	if (!buffer4.loadFromFile("sounds/win.wav")){
		std::cout << "Fail to load win sound file" << std::endl;
	}
	winSound.setBuffer(buffer4);
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
	player.setScale(0.5f, 0.5f);
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
			if(maze.operator()(playerY-1, playerX) != '#'){
				std::cout << "Going up" << std::endl;
				sound.play();
				playerY--;
				lastMove = sf::Time::Zero;
			}
			else{
				std::cout << "Ouch" << std::endl;
				hurtSound.play();
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		if(lastMove >= moveDelay){
			if(maze.operator()(playerY+1, playerX) != '#'){
				std::cout << "Going down" << std::endl;
				sound.play();
				playerY++;
				lastMove = sf::Time::Zero;
			}
			else{
				std::cout << "Ouch" << std::endl;
				hurtSound.play();
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		if(lastMove >= moveDelay){
			if(maze.operator()(playerY, playerX-1) != '#'){
				std::cout << "Going left" << std::endl;
				sound.play();
				playerX--;
				lastMove = sf::Time::Zero;
			}
			else{
				std::cout << "Ouch" << std::endl;
				hurtSound.play();
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if(lastMove >= moveDelay){
			if(maze.operator()(playerY, playerX+1) != '#'){
				std::cout << "Going right" << std::endl;
				sound.play();
				playerX++;
				lastMove = sf::Time::Zero;
			}
			else{
				std::cout << "Ouch" << std::endl;
				hurtSound.play();
			}
		}
	}

	//If case is a key
	if(maze.operator()(playerY, playerX) == 'k' && unlockSoundPlayed != true){
		//Key disappear
		maze.operator()(playerY, playerX) = ' ';

		//Open the path
		if(maze.getLevel() == 1){
			maze.operator()(16, 3) = ' ';
		}
		else if(maze.getLevel() == 2){
			maze.operator()(5, 5) = ' ';
		}
		unlockSound.play();

		std::cout << "Change content:" << maze.operator()(playerY, playerX) << ":P" << std::endl;
		unlockSoundPlayed = true;
	}

	//Next level phase
	if(maze.operator()(playerY, playerX) == 'n' && nextLevelPlayed != true){
		exitLevelSound.play();
		std::cout << "Next level!!" << std::endl;
		nextLevelPlayed = true;

		maze.setLevel(maze.getLevel() + 1);

		//Need to reset the sounds for the next level
		resetSounds();

		maze.setNewMaze( maze.getMazeByName("maze2") );
	}

	//Sound of the win for the exit
	if(maze.operator()(playerY, playerX) == 'e' && exit != true){
		winSound.play();
		std::cout << "Exit!!" << std::endl;
		exit = true;
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

void Player::resetSounds(){
	//reset unlock sound
	unlockSoundPlayed = false;

	//reset nextlevel sound
	nextLevelPlayed = false;
}

void Player::draw(sf::RenderTarget& target){

	player.setPosition(playerX * maze.getBlockSize()+1, playerY * maze.getBlockSize()+1);

	//Draw the player
	target.draw(player);
}