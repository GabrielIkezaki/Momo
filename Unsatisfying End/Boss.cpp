#include "Boss.h"

Boss::Boss(GameScene* scene)
	:Character(5000, sf::Vector2f(180, 10), "./Sprites/Characters/hanako.png", sf::Vector2f(.7f, .7f), sf::Vector2f(70, 70), sf::Vector2f(170,130)) {
	this->scene = scene;
}

Bloom::Bloom(Character* boss, GameScene* scene, sf::Vector2f offset) : Character(10, offset, "./Sprites/Characters/BloomSheet.png", sf::Vector2f(1, 1), sf::Vector2f(0, 0), sf::Vector2f(0, 0)) {
	this->boss = boss;
	this->offset = offset;
	//this.scene
	this->scene = scene;

	GenerateCircumference();
}


void Bloom::GenerateCircumference() {
	int numberOfBullets = 10;

	float angle = 0;
	float addAngle = 360/numberOfBullets;

	const double PI = 3.14159265358979323846;

	for (int i = 0; i < numberOfBullets; i++) {
		float xDirection = cos((angle * (PI / 180)));
		float yDirection = sin((angle * (PI / 180)));

		sf::Vector2f newDirection = sf::Vector2f(xDirection * 100, yDirection * 100);		

		daisyBullets.push_back(new DaisyBullet(this->characterSprite.spriteCenter(bloomEntry.uvRect.width, bloomEntry.uvRect.height), newDirection));

		angle += addAngle;
	}

	for (int i = 1; i < numberOfBullets + 1; i++) {
		std::cout << "BLOOM" << std::endl;
		this->scene->AddObject(&daisyBullets[daisyBullets.size() - i]->characterSprite);
	}

}

void Bloom::Update() {
	timeBetweenCircumference = clock.getElapsedTime();
	bloomEntry.Update(deltaTime);
	position = sf::Vector2f(boss->position.x + offset.x, boss->position.y + offset.y);

	ChangePosition(boss->position + offset);

	characterSprite.SwitchSpriteFrame(bloomEntry.uvRect);

	if (daisyBullets.size() > 0) {

		for (int i = 0; i < daisyBullets.size(); i++) {
			daisyBullets[i]->Character::Move(daisyBullets[i]->direction);
			//std::cout << "BLOOM" << std::endl;

		}
	}

}




void Boss::BloomPattern() {	
	for (int i = 0; i < 1; i++) {
		bloomObjects.push_back(*new Bloom(this, this->scene, sf::Vector2f(0, 0)));
		//bloomObjects.push_back(*new Bloom(this, this->scene, sf::Vector2f(300, 0)));		
	}
	scene->AddObject(&bloomObjects[bloomObjects.size() - 1].characterSprite);
	//scene->AddObject(&bloomObjects[bloomObjects.size() - 2].characterSprite);
}


void Boss::ArcMovement() {
	timer = clock.getElapsedTime();

	Character::Move(sf::Vector2f(ArcXVelocity(), ArcYVelocity()));
	
}

float Boss::ArcYVelocity() {
	float yVelocity = 100 * std::cos(2 * timer.asSeconds());
	velocity.y = yVelocity;
	return yVelocity;
}


float Boss::ArcXVelocity() {
	float yVelocity = 100 * std::cos(timer.asSeconds()/3);
	velocity.x = yVelocity;
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
	patternCooldown = patternClock.getElapsedTime();

	if (blinkTimer.asSeconds() > 0.05f) {
		characterSprite.objectSprite.setColor(sf::Color::White);
	}

	if (patternCooldown.asSeconds() > 2) {
		if (canAttack) {
			currentPattern = Pattern::BLOOM;
			BloomPattern();
			canAttack = false;
		}
	}
	if (currentPattern == Pattern::BLOOM) {

		if (bloomObjects.size() > 0) {
			for (int i = 0; i < bloomObjects.size(); i++) {
				bloomObjects[i].Update();
			}
		}
	}

}

