#include "Character.h"

void Character::Move(sf::Vector2f velocity) {		//This function is what causes the player to move
	this->position.x += velocity.x*deltaTime;		//We add the current position value to the velocity value, and multiply it by deltaTime to keep a consistency
	this->position.y += velocity.y *deltaTime;

	characterSprite.Move(position);		//Consequently, the sprite will also move to the character's new position
}

void Character::ChangePosition(sf::Vector2f newPosition) {
	position = newPosition;
	characterSprite.Move(position);
}

Character::Character(int tempHealth, sf::Vector2f position, std::string texture, sf::Vector2f scale, sf::Vector2f rect, sf::Vector2f offset) {
	health = tempHealth;
	this->position = position;
	this->rect = rect;
	this->rectOffset = offset;

	rect.x = characterSprite.objectTexture.getSize().x / 2;
	rect.y = characterSprite.objectTexture.getSize().y / 2;
	DefineSprite(texture, scale);		//As soon as the character is initialized, it will define its sprite right away
}

void Character::DefineSprite(std::string spriteTexture, sf::Vector2f spriteScale) {
	characterSprite.Set(spriteTexture,this->position, spriteScale);		//The character's sprite executes the Set fucntion, which defines the texture, position and scale of the character sprite

}

void Character::TakeDamage(int damage) {
	health -= damage;
	std::cout << health << std::endl;
}

void Character::UpdateRect() {
		
	hitBox.setSize(sf::Vector2f(rect.x * 2, rect.y * 2));
	hitBox.setOutlineColor(sf::Color::Red);
	hitBox.setOutlineThickness(2);
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setPosition(characterSprite.position.x + rectOffset.x, characterSprite.position.y + rectOffset.y);
	//hitBox.setPosition(0, 0);

}