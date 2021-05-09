#include "Boss.h"

Boss::Boss()
	:Character(5000, sf::Vector2f(220, 10), "./Sprites/Characters/hanako.png", sf::Vector2f(.7f, .7f), sf::Vector2f(190, 250), sf::Vector2f(55,60)) {}

void Boss::Update() {
	UpdateRect();
}

