#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

#include "../include/game.h"

int main() {

	// auto window = sf::RenderWindow{ { SCREEN_WIDTH, SCREEN_HEIGHT }, "SFML Labyrinth" };
	// window.setFramerateLimit(60);

	std::cout << "Start? " << std::endl;

	// sf::VideoMode vm = sf::VideoMode::getFullscreenModes()[0];
	// std::cout << "Start after VideoMode? " << std::endl;

	// sf::RenderWindow window;
	// std::cout << "Start after RenderWindow? " << std::endl;

	// window.create(sf::VideoMode(800, 600), "Resizable Window");
	// std::cout << "Window size: " << std::endl;
	// std::cout << "Window size: " << vm.width << " " << vm.height << std::endl;

	// while(window.isOpen()){
	// 	sf::Event event;
	// 	while(window.pollEvent(event)){
	// 		if(event.type == sf::Event::Closed
	// 		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) ){
	// 			window.close();
	// 		}
	// 	}
	// }

	Game game;
	game.run();

	return 0;
}

//Game owns the ScreenManager
//Game make the screen changes
//When player exit, we need to change the screen from Game