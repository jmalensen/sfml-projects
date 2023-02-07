#include "../include/game.h"

Game::Game(){

	std::string title = "None";
	int width = 0;
	int height = 0;
	int framerateLimit = 0;


	//Create a SFML window using options from a window.ini file
	std::ifstream ifs("config/window.ini");
	if(ifs.is_open()){
		std::getline(ifs, title);
		ifs >> width >> height;
		ifs >> framerateLimit;
	}
	ifs.close();

	//Create the window
	this->window.create(sf::VideoMode(width, height), title);
	this->window.setFramerateLimit(framerateLimit);

	// vm = sf::VideoMode::getFullscreenModes()[0];
	// // vm = sf::VideoMode::getDesktopMode();
	// window.create(vm, "Resizable Window laby");
	// std::cout << "Window size: " << vm.width << " " << vm.height << std::endl;
	
	// sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x * 2.f, window.getSize().y * 2.f));
	
	// view.setSize(vm.width * 2, vm.height * 2);
	// view.setCenter(vm.width, vm.height);
	// view.zoom(2.f);
	// window.setView(view);
	// window.setFramerateLimit(60);
}

Game::~Game(){
}

void Game::run(){
	this->screensManager.showStartScreen();

	//Background music
	if (!this->music.openFromFile("sounds/musicloop.ogg")){
		std::cout << "Fail to load music file" << std::endl;
	}

	this->music.setVolume(20);
	this->music.setLoop(true);
	this->music.play();

	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;

	//Game loop
	while(this->window.isOpen()){
		sf::Time dt = clock.restart();
		elapsedTime += dt;

		// std::cout << dt.asMilliseconds() << " " << TimePerFrame.asMilliseconds() << std::endl;

		//If we need to check the FPS
		// float currentTime = dt.asSeconds();
		// float fps = 1.0f / currentTime;
		// std::cout << "fps:" << fps << std::endl;

		// while(elapsedTime > TimePerFrame){
			// elapsedTime -= TimePerFrame;

			handleEvents();
			update(dt);
		// }

		draw();

		//Slow down program
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Game::handleEvents(){
	//Handle events
	sf::Event event;
	while(this->window.pollEvent(event)){

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		&& this->screensManager.getCurrentScreen() == ScreensManager::STARTSCREEN){
			this->screensManager.showMenuScreen();
		}

		//Handle enter key press
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		&& this->screensManager.getCurrentScreen() != ScreensManager::STARTSCREEN){
			this->screensManager.showMainScreen();
			this->screensManager.handleEvents(event);
		}

		else if(event.type == sf::Event::Closed
		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				&& this->screensManager.getCurrentScreen() == ScreensManager::ENDSCREEN)
		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
				&& this->screensManager.getCurrentScreen() == ScreensManager::GAMEOVERSCREEN) ){
			this->window.close();
		}

		//Display the menu
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
		&& this->screensManager.getCurrentScreen() != ScreensManager::MENUSCREEN){
			this->screensManager.showMenuScreen();
		}

		// else if (event.type == sf::Event::Resized)
		// {
		// 		view.setSize(event.size.width, event.size.height);
		// 		view.setCenter(event.size.width / 2, event.size.height / 2);
		// 		window.setView(view);
		// }
	}
}

void Game::update(sf::Time TimePerFrame){
	this->screensManager.update(TimePerFrame);
}

void Game::draw(){
	//Clear the window with black color
	this->window.clear(sf::Color::Black);

	//Draw screens
	this->screensManager.draw(this->window);

	//Display the window
	this->window.display();
}