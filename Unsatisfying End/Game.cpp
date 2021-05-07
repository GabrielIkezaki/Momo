#include "Game.h"


void Game::RenderWindow() {
	//VideoMode defines the size of the window, "Unsatisfying End" is the title of the window, Titlebar includes a title bar with a Close button
	this->window = new sf::RenderWindow(sf::VideoMode(900, 1000), "Unsatisfying End", sf::Style::Titlebar | sf::Style::Close);
}


bool Game::isGameRunning(){		//As long as the window is opened, this variable will signalize that the game is still running
	return window->isOpen();
}

void Game:: StartGame() {
	this->window = nullptr;		//The window pointer will start as a null pointer (so that there aren't access exceptions at first)
}

Game::Game() {
	StartGame();
	RenderWindow();	//Once the game is started, the window will be rendered
}

Game::~Game() {
	delete this->window;	//If the game is closed, the game window will be deleted 
}

void Game::PollEvents() {
	while (window->pollEvent(ev)) {	//pollEvent returns wether there are currently actions being performed on screen or not (mouseclick, key press, etc.)
		
		switch (ev.type)	//This switch statement will evaluate the type of event that is currently happening on screen
		{
		case sf::Event::Closed:		//If the event is a mouse click on the close button on the titlebar
			window->close();		//The window will closed	
			break;
		case sf::Event::KeyPressed:	//If a key is either pressed or released, the gameScene will control the player according to the input
		case sf::Event::KeyReleased:
			gameScene.ControlPlayer(&ev);	//The key press/release will be passed down as the window event
		}				
	}
}

void Game::Update() {
	PollEvents();	//The game will be constantly checking for events
	gameScene.Update();		//The gameScene will be updating accordingly

}

void Game::Render() {		//This is how the game is rendered
	window->clear();	//The previous frame is erased
	gameScene.Display(window);		//The game scene will draw every sprite in it
	window->draw(gameScene.player.hitBox);
	if (gameScene.player.allBullets.size() > 0) {
		for (int i = 0; i < gameScene.player.allBullets.size(); i++) {
			window->draw(gameScene.player.allBullets[i]->hitBox);
		}
	}
	window->display();	//The window will display whatever was drawn on the previous lines 
}
