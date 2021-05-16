#include "SpriteObject.h"


void SpriteObject::Move(sf::Vector2f position) {		//This function requires a position to which the sprite will move
	this->position = position;
	objectSprite.setPosition(this->position);		//The sprite of the object will then set its position to the current position
}

void SpriteObject::DefineSprite() {		//This function sets the sprite's values to the ones that were stored in the Set function
	objectSprite.setTexture(objectTexture);	
	objectSprite.setOrigin(this->origin);
	objectSprite.setPosition(this->position);
	objectSprite.setScale(this->scale);
}

void SpriteObject::SwitchSpriteFrame(sf::IntRect newSprite) {
	objectSprite.setTextureRect(newSprite);		//Changes the rect of the texture image, essentially chaning frames to whatever is specified in the parameter
}

void SpriteObject::Set(std::string tempTexture, sf::Vector2f position, sf::Vector2f origin, sf::Vector2f scale) {		//Storing the sprite's values

	textureAddress = tempTexture;
	this->origin = origin;

	this->position = position;
	this->scale = scale;

	objectTexture.loadFromFile(textureAddress);

	DefineSprite();
}