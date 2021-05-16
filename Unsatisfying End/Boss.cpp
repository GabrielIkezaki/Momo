#include "Boss.h"

Boss::Boss(GameScene* scene)
	:Character(5000, sf::Vector2f(415, 400), sf::Vector2f(351,434), "./Sprites/Characters/hanako.png", sf::Vector2f(.7f, .7f), sf::Vector2f(70, 70), sf::Vector2f(-75,-175)) {
	this->scene = scene;

//	bloomObjects.push_back(*new Bloom(this, this->scene, sf::Vector2f(xoffset, yoffset)));
//	bloomObjects.push_back(*new Bloom(this, this->scene, sf::Vector2f(-xoffset, yoffset)));

	Start();
}

void Boss::Start() {
	BloomPattern();
}

Bloom::Bloom(Character* boss, GameScene* scene, sf::Vector2f offset) : Character(10, offset, sf::Vector2f(250, 140.5f), "./Sprites/Characters/BloomSheet.png", sf::Vector2f(1, 1), sf::Vector2f(0, 0), sf::Vector2f(0, 0)) {
	this->boss = boss;
	this->offset = offset;

	ChangePosition(boss->position + offset);

	this->scene = scene;
	for (int i = 0; i < totalCircumferences; i++) {
		//std::cout << i << std::endl;
		GenerateCircumference();
	}

}


void Bloom::GenerateCircumference() {

	float angle = 0;
	float addAngle = 360/numberOfBullets;

	const double PI = 3.14159265358979323846;

	for (int i = 0; i < numberOfBullets; i++) {
		float xDirection = cos((angle * (PI / 180)));
		float yDirection = sin((angle * (PI / 180)));

		sf::Vector2f newDirection = sf::Vector2f(xDirection * 700, yDirection * 700);		

		daisyBullets.push_back(new DaisyBullet(sf::Vector2f(-10, -10), newDirection));
		scene->AddObject(&daisyBullets[daisyBullets.size() - 1]->characterSprite);
		angle += addAngle;
	}


	
}

void Bloom::DrawDaisy() {
	for (int i = 0; i < daisyBullets.size(); i++) {
		if (daisyBullets[i]->characterSprite.isVisible == false) {
			scene->AddObject(&daisyBullets[i]->characterSprite);
			daisyBullets[i]->characterSprite.isVisible = true; 
		}
	}


}

void Bloom::Update() {


	if (wakeUp) {
		timeBetweenCircumference = clock.getElapsedTime();
		bloomEntry.Update(deltaTime);

		ChangePosition(boss->position + offset);

		characterSprite.SwitchSpriteFrame(bloomEntry.uvRect);

		if (timeBetweenCircumference.asSeconds() > circumferenceCooldown) {

			DrawDaisy();

			for (int i = 0; i < numberOfBullets; i++) {

				int index = i + (currentCircumference * numberOfBullets);
				daisyBullets[index]->ChangePosition(position);
				daisyBullets[index]->UpdateRect();

			}

			currentCircumference++;
			if (currentCircumference > totalCircumferences - 1) {
				currentCircumference = 0;
			}
			circumferenceCooldown = .4f;

			clock.restart();
		}

		if (daisyBullets.size() > 0) {

			for (int i = 0; i < daisyBullets.size(); i++) {
				daisyBullets[i]->Character::Move(daisyBullets[i]->direction);
			}
		}

		
	}

}




void Boss::BloomPattern() {	

	float xoffset = 300; 
	float yoffset = -150;

	for (int i = 0; i < 1; i++) {
		bloomObjects.push_back(*new Bloom(this, this->scene, sf::Vector2f(xoffset, yoffset)));
		bloomObjects.push_back(*new Bloom(this, this->scene, sf::Vector2f(-xoffset, yoffset)));
	}

	//scene->AddObject(&bloomObjects[0].characterSprite);

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

			//scene->AddObject(&bloomObjects[0].characterSprite);
			//scene->AddObject(&bloomObjects[1].characterSprite);



			//bloomObjects[0].wakeUp = true;
			//bloomObjects[1].wakeUp = true; 
				
			


			

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

