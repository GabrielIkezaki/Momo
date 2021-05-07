#include "Player.h"
/*
Player::Player(sf::Event* tempEv){
	ev = tempEv;
	Set(1, 5, 10, 10);
	DefineSprite("./Sprites/Characters/momo.png", 10, 10, .2f, .2f);
}


void Player::Movement() {

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		xVelocity = -.2f;		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		xVelocity = .2f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		yVelocity = -.2f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		yVelocity = .2f;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		xVelocity = 0;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		yVelocity = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		xVelocity *= 1 / sqrt(2);
		xVelocity *= 1 / sqrt(2);
	}



	/*
	switch (ev->key.code) {

	case 71:
		std::cout << "LEFT" << std::endl;
		xVelocity = -.2f;
		break;
	case 72:
		std::cout << "RIGHT" << std::endl;
		xVelocity = .2f;
		break;
	case 73:
		std::cout << "UP" << std::endl;
		yVelocity = .2f;
		break;
	case 74:
		std::cout << "DOWN" << std::endl;
		yVelocity = -.2f;
		break;

	default:
		xVelocity = 0;
		yVelocity = 0;
		break;
	}


	Move(xVelocity, yVelocity);
}
*/

