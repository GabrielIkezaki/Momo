#include "Boss.h"

Boss::Boss(GameScene* scene)
	:Character(5000, sf::Vector2f(415, 400), sf::Vector2f(351,434), "./Sprites/Characters/hanako.png", sf::Vector2f(.7f, .7f), sf::Vector2f(70, 70), sf::Vector2f(-75,-175)) {
	this->scene = scene;

	for (int i = 0; i < totalBullets; i++) {
		bossBullets.push_back(new EnemyBullet(sf::Vector2f(-5000, -5000)));
	}

	bloomObjects.push_back(*new Bloom(this, sf::Vector2f(300, -100)));
	bloomObjects.push_back(*new Bloom(this, sf::Vector2f(-300, -100)));
}

void Boss::Start() {
	DrawBullets();
}

void Boss::DrawBullets() {
	for (int i = 0; i < bossBullets.size(); i++) {
		scene->AddObject(&bossBullets[i]->characterSprite);
	}
}

Bloom::Bloom(Character* boss, sf::Vector2f offset) : Character(10, offset, sf::Vector2f(250, 140.5f), "./Sprites/Characters/BloomSheet.png", sf::Vector2f(1, 1), sf::Vector2f(0, 0), sf::Vector2f(0, 0)) {
	this->boss = boss;
	this->offset = offset;
	this->bossBullets = bossBullets;

	ChangePosition(boss->position + offset);
}


void Bloom::Update() {


	if (wakeUp) {
		bloomEntry.Update(deltaTime);

		ChangePosition(boss->position + offset);

		characterSprite.SwitchSpriteFrame(bloomEntry.uvRect);	
	}

}




void Boss::BloomPattern() {	


	float angle = 0;
	float addAngle = 360 / numberOfBullets;

	const double PI = 3.14159265358979323846;

	for (int i = 0; i < bossBullets.size(); i++) {
		float xDirection = cos((angle * (PI / 180)));
		float yDirection = sin((angle * (PI / 180)));

		sf::Vector2f newDirection = sf::Vector2f(xDirection * 700, yDirection * 700);
		bossBullets[i]->SetDirection(newDirection);

		angle += addAngle;
	}
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

			scene->AddObject(&bloomObjects[0].characterSprite);
			scene->AddObject(&bloomObjects[1].characterSprite);
			bloomObjects[0].wakeUp = true;
			bloomObjects[1].wakeUp = true; 	
			
			BloomPattern();
			DrawBullets();

			canAttack = false;
		}
	}
	if (currentPattern == Pattern::BLOOM) {
		timeBetweenBullets = bulletClock.getElapsedTime();
		
		if (timeBetweenBullets.asSeconds() > 0.4f) {
			for (int i = 0; i < numberOfBullets; i++) {
				int index = i + (currentCircumference * numberOfBullets);
				std::cout << index << std::endl;
				bossBullets[index]->ChangePosition(bloomObjects[0].position);
			}
			
			if (currentCircumference < 3) {
				currentCircumference++;
			}
			else {
				currentCircumference = 0;
			}
			
			bulletClock.restart();
		}

		if (bloomObjects.size() > 0) {
			for (int i = 0; i < bloomObjects.size(); i++) {
				bloomObjects[i].Update();
			}
		}
	}

	for (int i = 0; i < bossBullets.size(); i++) {
		bossBullets[i]->Move(bossBullets[i]->direction);
	}

}

