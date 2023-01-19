#include "../include/game.h"
#include "../include/startscreen.h"
#include "../include/mainscreen.h"

Game::Game(){
	//Create the window
	window.create(sf::VideoMode(1500, 1260), "Laby OO");
	window.setFramerateLimit(60);
}

void Game::run(){
	startScreen.active = true;
	mainScreen.active = false;

	//Background music
	sf::Music music;
	if (!music.openFromFile("sounds/musicloop.wav")){
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
		//Handle enter key press
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
			startScreen.active = false;
			mainScreen.active = true;
		}

		if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
		}
	}
}

void Game::update(sf::Time TimePerFrame){
	if(startScreen.active){
		startScreen.update(TimePerFrame);
	}
	else if(mainScreen.active){
		mainScreen.update(TimePerFrame);
	}
}

void Game::draw(){
	//Clear the window with black color
	window.clear(sf::Color::Black);

	//Draw screens
	if(startScreen.active){
		// std::cout << "Load splash screen" << std::endl;
		startScreen.draw(window);
	}
	else if(mainScreen.active){
		// std::cout << "Load main screen" << std::endl;
		mainScreen.draw(window);
	}

	//Display the window
	window.display();
}