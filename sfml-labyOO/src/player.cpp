#include "../include/player.h"

Player::Player(Map& maze, AssetsManager &assetsManager): Entity(maze, assetsManager){
	//Initialize the player
	init();
}

Player::~Player(){
}

void Player::init(){
	//Player position
	positionX = 1;
	positionY = 1;

	dead = false;

	///Sounds
	//Movement sound
	assetsManager.loadSound("jump", "sounds/jump.ogg");
	sound = (assetsManager.getSound("jump"));
	sound.setVolume(10);

	//Hurt sound
	assetsManager.loadSound("hitHurt", "sounds/hitHurt.ogg");
	hurtSound = (assetsManager.getSound("hitHurt"));
	hurtSound.setVolume(100);
	trapEnabled = false;

	//Unlock sound
	assetsManager.loadSound("unlock", "sounds/unlock-sound.ogg");
	unlockSound = (assetsManager.getSound("unlock"));
	unlockEnabled = false;

	//Exit level sound
	assetsManager.loadSound("exitlevel", "sounds/exitlevel.ogg");
	exitLevelSound = (assetsManager.getSound("exitlevel"));
	nextLevelEnabled = false;

	exit = false;

	//Texture for the player
	assetsManager.loadTexture("dino", "images/dino.png");
	entity.setTexture(assetsManager.getTexture("dino"));

	//Player animation
	rectSourceSpriteEntity.left = 0;
	rectSourceSpriteEntity.top = 0;
	rectSourceSpriteEntity.width = 104;
	rectSourceSpriteEntity.height = 113;
	entity.setTextureRect(rectSourceSpriteEntity);
	entity.setScale(0.5f, 0.5f);
}

bool Player::getHasExited() const{
	return exit;
}

void Player::justDie(bool newStatus){
	dead = newStatus;
}

bool Player::isDead() const{
	return dead;
}

void Player::update(sf::Time dt){

	///Needed to keep the same clock for the player (not moving too fast)
	//Player speed (pixels/s)
	static const float speed = 40.f;

	//Delay between 2 moves
	static const sf::Time moveDelay = sf::seconds(5.f / speed);

	//Last time player moved
	static sf::Time lastMove = sf::Time::Zero;
	lastMove += dt;

	//getHitBox().intersects(enemy.getHitBox());

	//Handle movement of player
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		if(lastMove >= moveDelay){
			if(maze.operator()(positionY-1, positionX) != '#'){
				std::cout << "Going up" << std::endl;
				positionY--;
				lastMove = sf::Time::Zero;
			}
			else{
				std::cout << "Ouch" << std::endl;
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		if(lastMove >= moveDelay){
			if(maze.operator()(positionY+1, positionX) != '#'){
				std::cout << "Going down" << std::endl;
				positionY++;
				lastMove = sf::Time::Zero;
			}
			else{
				std::cout << "Ouch" << std::endl;
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		if(lastMove >= moveDelay){
			if(maze.operator()(positionY, positionX-1) != '#'){
				std::cout << "Going left" << std::endl;
				positionX--;
				lastMove = sf::Time::Zero;
			}
			else{
				std::cout << "Ouch" << std::endl;
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if(lastMove >= moveDelay){
			if(maze.operator()(positionY, positionX+1) != '#'){
				std::cout << "Going right" << std::endl;
				positionX++;
				lastMove = sf::Time::Zero;
			}
			else{
				std::cout << "Ouch" << std::endl;
			}
		}
	}

	if(maze.operator()(positionY, positionX) == 't' && trapEnabled != true){
		hurtSound.play();

		if(maze.getLevel() == 2){
			maze.operator()(8, 5) = '#';
			maze.operator()(13, 15) = 'k';
		}
		else if(maze.getLevel() == 3){
			maze.operator()(1, 22) = '#';
			maze.operator()(13, 15) = 'k';
		}
		maze.operator()(positionY, positionX) = ' ';
		unlockEnabled = false;
		trapEnabled = true;
	}

	//If case is a key
	if(maze.operator()(positionY, positionX) == 'k' && unlockEnabled != true){
		//Key disappear
		maze.operator()(positionY, positionX) = ' ';

		//Open the path
		if(maze.getLevel() == 1){
			maze.operator()(16, 3) = ' ';
		}
		else if(maze.getLevel() == 2){
			maze.operator()(5, 5) = ' ';
			maze.operator()(8, 5) = ' ';
		}
		else if(maze.getLevel() == 3){
			maze.operator()(1, 22) = ' ';
		}
		unlockSound.play();

		std::cout << "Change content:" << maze.operator()(positionY, positionX) << positionY << positionX << ":P" << std::endl;
		unlockEnabled = true;
	}

	//Next level phase
	if(maze.operator()(positionY, positionX) == 'n' && nextLevelEnabled != true){
		exitLevelSound.play();
		std::cout << "Next level!!" << std::endl;
		nextLevelEnabled = true;

		maze.setLevel(maze.getLevel() + 1);

		//Need to reset the sounds for the next level
		resetSounds();

		//Name of the maze level
		std::string name = "maze"+ std::to_string(maze.getLevel());

		//Set new level
		maze.setNewMaze( maze.getMazeByName(name) );

		positionX = 1;
		positionY = 1;
		entity.setPosition(positionX * maze.getBlockSize()+1, positionY * maze.getBlockSize()+1);
	}

	//Sound of the win for the exit
	if(maze.operator()(positionY, positionX) == 'e' && exit != true){
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
		if (rectSourceSpriteEntity.left == 228){
			rectSourceSpriteEntity.left = 0;
		}
		else{
			rectSourceSpriteEntity.left += 114;
		}

		currentTime = 0;

		std::cout << rectSourceSpriteEntity.left << std::endl;

		//Set the rectangle so we see the movement
		entity.setTextureRect(rectSourceSpriteEntity);
	}
}

void Player::resetSounds(){
	//Reset unlock sound
	unlockEnabled = false;

	//Reset nextlevel sound
	nextLevelEnabled = false;

	//Reset trap sound
	trapEnabled = false;
}

void Player::draw(sf::RenderTarget& target){

	entity.setPosition(positionX * maze.getBlockSize()+1, positionY * maze.getBlockSize()+1);

	//Draw the player
	target.draw(entity);
}