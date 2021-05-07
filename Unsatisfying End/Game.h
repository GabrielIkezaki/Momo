#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML//Window.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "MainGame.h"
#pragma once
class Game		//This class is used as a game engine. It mainly manages scenes and windows
{

private:


	sf::Event ev;	//The ev variable records every event on the window. This may be a mouse click, a cursor displacement, a keypressed, etc.
	MainGame gameScene = MainGame(&ev);	//This is the scene where the game will be played

	void StartGame();
	void PollEvents();		//This function reads the events on screen
	void RenderWindow();	//Sets the width, height, style of the game window	
	
	
public:

	sf::RenderWindow* window;	//The window that will display the game

	bool isGameRunning();
	void Update();
	void Render();	//Renders the current scene, displaying every visual asset on screen
	Game();
	~Game();

};

