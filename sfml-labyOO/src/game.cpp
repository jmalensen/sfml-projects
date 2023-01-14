#include "../include/game.h"
#include "../include/map.h"
#include "../include/player.h"
#include <iostream>
#include <chrono>
#include <thread>

Game::Game(): map(), player(map){
	//Create the window
	window.create(sf::VideoMode(1000, 840), "Laby OO");
	window.setFramerateLimit(60);
}

void Game::run(){
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
		if(event.type == sf::Event::Closed){
			window.close();
		}
	}
}

void Game::update(sf::Time TimePerFrame){
	//Update the game
	player.update(TimePerFrame);
}

void Game::draw(){
	//Clear the window
	window.clear();

	//Draw map
	map.draw(window);

	//Draw player
	player.draw(window);

	//Display the window
	window.display();
}