#include "EnemyBullet.h"

void EnemyBullet::SetDirection(sf::Vector2f direction) {
	this->direction = direction;
}

void EnemyBullet::CheckCollision() {
	if (hitBox.getPosition().x < (player->hitBox.getPosition().x + (2 * player->rect.x)) && (hitBox.getPosition().x + (2 * rect.x)) >(player->hitBox.getPosition().x)
		&& hitBox.getPosition().y < (player->hitBox.getPosition().y + (2 * player->rect.y)) && (hitBox.getPosition().y + (2 * rect.y)) >(player->hitBox.getPosition().y))
	{
		if (canDealDamage) {
			player->TakeDamage(1);
			std::cout << player->health << std::endl;
			canDealDamage = false;
		}
	}
}

void EnemyBullet::ChangePosition(sf::Vector2f newPosition) {
	Character::ChangePosition(newPosition);
	canDealDamage = true;
}

void EnemyBullet::Update() {
	Move(direction);
	CheckCollision();
	UpdateRect();
}