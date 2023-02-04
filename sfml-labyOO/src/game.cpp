#include "../include/game.h"

Game::Game(){
	//Create the window
	window.create(sf::VideoMode(1500, 1260), "Laby OO");
	window.setFramerateLimit(60);
}

Game::~Game(){
}

void Game::run(){
	screensManager.showStartScreen();

	//Background music
	if (!music.openFromFile("sounds/musicloop.ogg")){
		std::cout << "Fail to load music file" << std::endl;
	}

	music.setVolume(20);
	music.setLoop(true);
	music.play();

	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;

	//Game loop
	while(window.isOpen()){
		sf::Time dt = clock.restart();
		elapsedTime += dt;

		//If we need to check the FPS
		// float currentTime = dt.asSeconds();
		// float fps = 1.0f / currentTime;
		// std::cout << "fps:" << fps << std::endl;

		while(elapsedTime > TimePerFrame){
			elapsedTime -= TimePerFrame;

			handleEvents();
			update(TimePerFrame);
		}

		draw();

		//Slow down program
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Game::handleEvents(){
	//Handle events
	sf::Event event;
	while(window.pollEvent(event)){

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		&& screensManager.getCurrentScreen() == ScreensManager::STARTSCREEN){
			screensManager.showMenuScreen();
		}

		//Handle enter key press
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		&& screensManager.getCurrentScreen() != ScreensManager::STARTSCREEN){
			screensManager.showMainScreen();
			screensManager.handleEvents(event);
		}

		else if(event.type == sf::Event::Closed
		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				&& screensManager.getCurrentScreen() == ScreensManager::ENDSCREEN)
		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				&& screensManager.getCurrentScreen() == ScreensManager::GAMEOVERSCREEN) ){
			window.close();
		}

		//Display the menu
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
		&& screensManager.getCurrentScreen() != ScreensManager::MENUSCREEN){
			screensManager.showMenuScreen();
		}
	}
}

void Game::update(sf::Time TimePerFrame){
	screensManager.update(TimePerFrame);
}

void Game::draw(){
	//Clear the window with black color
	window.clear(sf::Color::Black);

	//Draw screens
	screensManager.draw(window);

	//Display the window
	window.display();
}