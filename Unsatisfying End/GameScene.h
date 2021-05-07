#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Character.h"




class GameScene
{
protected:
	sf::Event* localEv;	//This pointer inherits the ev event variable from the Game.cpp file
	sf::RenderWindow* window;	//This pointer inherits the window that is displaying the game in the Game.cpp file
public:
	//SpriteObject enemy;

	bool isCurrentlyDisplayed;	//This bool will be used to determine which scene is currently being displayed, but it's currently not in use
	std::vector<SpriteObject*> spritesInDisplay;		//Stores all the sprites being displayed in the current scene

	void Display(sf::RenderWindow* tempwindow);		//Is called by the Game file, in the Render function. It displays all the sprites in the scene
	void AddObject(SpriteObject* newCharacter);		//Adds an object to be displayed in the scene
	virtual void Update() {};		//This function does nothing by itself, it's meant to be overriden by this class' children
	
	GameScene(sf::Event* tempEvent);	//The constructor of the Gamescene gets the event variable of the game, which will allow the scene to read player inputs
};

