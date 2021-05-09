#pragma once
#include "SpriteObject.h"

extern float deltaTime;		//DeltaTime: calculates the time between one frame to the next, is usually used to keep certain quantities (such as velocity and timers) consistent, regardless of frame rate. The extern prefix makes this variable acessible for all scripts that include "Character.h" 

class Character		//The character class is a set of attributes that makes a character (namely move, take damage, display a sprite)
{
	
public:
	SpriteObject characterSprite;		//Stores this character's sprite
	int health;			//Stores this character's health
	sf::Vector2f position;		//Stores the position of the character
	sf::Vector2f rect;		//Stores the rect of the character (which will be used as a hurt/hitbox)
	sf::Vector2f rectOffset;
	sf::RectangleShape hitBox;

	//Character constructor requires an initial health, position, sprite texture and sprite scale
	Character(int tempHealth, sf::Vector2f position, std::string texture, sf::Vector2f scale, sf::Vector2f rect, sf::Vector2f offset);

	void DefineSprite(std::string spriteTexture, sf::Vector2f spriteScale);		//Changes this character sprite's texture and scale
	void Move(sf::Vector2f velocity);		//Moves the character by adding a velocity value
	void UpdateRect();
	void TakeDamage(int damage);
	
};

