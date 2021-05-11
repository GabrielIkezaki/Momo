#include "Boss.h"

Boss::Boss()
	:Character(5000, sf::Vector2f(180, 10), "./Sprites/Characters/hanako.png", sf::Vector2f(.7f, .7f), sf::Vector2f(70, 70), sf::Vector2f(170,130)) {}

void Boss::ArcMovement() {
	timer = clock.getElapsedTime();

	Character::Move(sf::Vector2f(ArcXVelocity(), ArcYVelocity()));
	
}

float Boss::ArcYVelocity() {
	float yVelocity = 100 * std::cos(2 * timer.asSeconds());
	return yVelocity;
}


float Boss::ArcXVelocity() {
	float yVelocity = 100 * std::cos(timer.asSeconds()/3);
	return yVelocity;
}

void Boss::TakeDamage(int tempDamage) {
	Character::TakeDamage(tempDamage);

	blinkClock.restart();
	characterSprite.objectSprite.setColor(blinkColor);
}

void Boss::Update() {
	ArcMovement();
	UpdateRect();
	blinkTimer = blinkClock.getElapsedTime();

	if (blinkTimer.asSeconds() > 0.05f) {
		characterSprite.objectSprite.setColor(sf::Color::White);
	}
}

