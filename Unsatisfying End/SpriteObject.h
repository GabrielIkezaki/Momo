#pragma once

#include <iostream>;

#include "SFML/Graphics.hpp"


class SpriteObject		//A sprite object is a sprite that can move and switch frames
{
public:
	sf::Vector2f position;		//Sets the position of the sprite
	sf::Sprite objectSprite;	//The actual textured sprite of the object
	sf::Texture objectTexture;	//The texture of the sprite of the object	

	virtual void Set(std::string tempTexture, sf::Vector2f position, sf::Vector2f scale);	//Passes down the texture, position and scale of the objectSprite
	void Move(sf::Vector2f position);	//Sets a new position for the sprite
	void SwitchSpriteFrame(sf::IntRect newSprite);	//Sets a new rect for the sprite, allowing it to render different animation frames from a sprite sheet

private:
	std::string textureAddress;		//Loads the sprite from whatever address is stored in this string
	sf::Vector2f scale;		//The scale of the sprite


protected:
	virtual void DefineSprite();		//Defines the texture, position and scale of the object

};

