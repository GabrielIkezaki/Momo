#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
class Animation
{

public:
	sf::IntRect uvRect;		//The rect allows the game to display a rectangular portion of an image, which is very useful for dealing with spritesheets
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);		//Sets the spritesheet that will be animated, the cell count and time between each animation frame

	void Update(float deltaTime);	//Requires deltaTime to switch between frames

private:
	sf::Vector2u imageCount;	//Determines the collumns and rows
	sf::Vector2u currentImage;		//Sets the collumn and row number

	//Sets the current time between animaiton frames and the time it takes to switch frames respectively
	float totalTime, switchTime;
};

