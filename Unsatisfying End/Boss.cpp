#include "Boss.h"

Boss::Boss(GameScene* scene, Character* player)
	:Character(5000, sf::Vector2f(415, 400), sf::Vector2f(351,434), "./Sprites/Characters/hanako.png", sf::Vector2f(.7f, .7f), sf::Vector2f(70, 70), sf::Vector2f(-75,-175)) {
	this->scene = scene;
	this->player = player;
	
	for (int i = 0; i < totalBullets; i++) {	//The boss character stores all the bullets it's going to use as objects
		bossBullets.push_back(new EnemyBullet(sf::Vector2f(-5000, -5000), player));	
	}

	bloomObjects.push_back(*new Bloom("./Sprites/Characters/BloomSheet.png", this, sf::Vector2f(1,1), sf::Vector2f(300, -100), sf::Vector2f(250, 140.5f)));
	bloomObjects.push_back(*new Bloom("./Sprites/Characters/BloomSheet.png", this, sf::Vector2f(1, 1), sf::Vector2f(-300, -100), sf::Vector2f(250, 140.5f)));

	bloomObjects.push_back(*new SpiralWindow("./Sprites/Characters/SpiralSheet.png", this, sf::Vector2f(.9f, .9f), sf::Vector2f(0, -120)));
}

void Boss::Start() {

	for (int i = 0; i < bloomObjects.size(); i++) {
		scene->AddObject(&bloomObjects[i].characterSprite);
	}
	DrawBullets();

}

void Boss::DrawBullets() {
	for (int i = 0; i < bossBullets.size(); i++) {
		scene->AddObject(&bossBullets[i]->characterSprite);
	}
}

void Boss::RedefineBullets(int numberOfBullets, sf::Vector2f scale) {
	this->numberOfBullets = numberOfBullets;
	for (int i = 0; i < bossBullets.size(); i++) {
		bossBullets[i]->characterSprite.objectSprite.setScale(scale);
	}
}

Bloom::Bloom(std::string textureAddress, Character* boss, sf::Vector2f scale, sf::Vector2f offset, sf::Vector2f origin) : Character(10, offset, origin, textureAddress, scale, sf::Vector2f(0, 0), sf::Vector2f(0, 0)) {
	this->boss = boss;
	this->offset = offset;
	this->bossBullets = bossBullets;

	ChangePosition(sf::Vector2f(-1500, 0));
}


void Bloom::Update() {
	if (wakeUp) {
		bloomEntry.Update(deltaTime);

		ChangePosition(boss->position + offset);
		characterSprite.SwitchSpriteFrame(bloomEntry.uvRect);	
	}

}

void Boss::GenerateCircumference() {	
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


void Boss::BeginPattern(sf::Vector2i indexRange) {		//Used to play the animation of a certain pattern and restart the bulletClock (which marks the time between each bullet fired)

	for (int i = indexRange.x; i < indexRange.y + 1; i++) {
		bloomObjects[i].wakeUp = true;
	}

	bulletClock.restart();
}


void Boss::UpdateBloomPattern() {
	timeBetweenBullets = bulletClock.getElapsedTime();

	if (timeBetweenBullets.asSeconds() > minTimeBetweenBullets) {
		for (int i = 0; i < numberOfBullets; i++) {
			int index = i + (currentCircumference * numberOfBullets);
			std::cout << index << std::endl;
			if (index % 2 == 0) {
				bossBullets[index]->ChangePosition(bloomObjects[0].position);
			}
			else {
				bossBullets[index]->ChangePosition(bloomObjects[1].position);
			}
		}

		if (currentCircumference < 3) {
			currentCircumference++;
		}
		else {
			currentCircumference = 0;
		}
		minTimeBetweenBullets = .4f;
		bulletClock.restart();
	}

	if (bloomObjects.size() > 0) {
		for (int i = 0; i < bloomObjects.size(); i++) {
			bloomObjects[i].Update();
		}
	}
}

void Boss::UpdateSpiralPattern() {
	timeBetweenBullets = bulletClock.getElapsedTime();
	if (timeBetweenBullets.asSeconds() > minTimeBetweenBullets) {
		bossBullets[spiralIndex]->ChangePosition(sf::Vector2f(this->position.x, this->position.y - 120));


		if (spiralIndex < (bossBullets.size() - 1)) {
			spiralIndex++;
		}
		else {
			spiralIndex = 0;
		}

		minTimeBetweenBullets = 0.02f;
		bulletClock.restart();
	}
}

#pragma region Boss Movement

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
	float yVelocity = 100 * std::cos(timer.asSeconds() / 3);
	velocity.x = yVelocity;
	return yVelocity;
}


#pragma endregion


#pragma region Boss Take Damage

void Boss::BlinkOnHit() {
	blinkClock.restart();
	characterSprite.objectSprite.setColor(blinkColor);
}

void Boss::TakeDamage(int tempDamage) {
	Character::TakeDamage(tempDamage);
	BlinkOnHit();
}
#pragma endregion




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
			//currentPattern = Pattern::SPIRAL;
			currentPattern = Pattern::BLOOM;
	
			switch (currentPattern)
			{
			case Pattern::BLOOM:
				
				RedefineBullets(20, sf::Vector2f(.7f, .7f));
				BeginPattern(sf::Vector2i(0, 1));

				GenerateCircumference();
				break;
			case Pattern::SPIRAL:
				RedefineBullets(30, sf::Vector2f(.4f, .4f));
				BeginPattern(sf::Vector2i(2,2));

				GenerateCircumference();

				break;
			default:
				break;
			}


			canAttack = false;
		}
	}

	switch (currentPattern) {
	case Pattern::BLOOM:
		UpdateBloomPattern();
		break;
	case Pattern::SPIRAL:
		UpdateSpiralPattern();
		break;
	}

	for (int i = 0; i < bossBullets.size(); i++) {
		bossBullets[i]->Update();
	}
	if (bloomObjects.size() > 0) {
		for (int i = 0; i < bloomObjects.size(); i++) {
			bloomObjects[2].Update();
		}
	}

}

