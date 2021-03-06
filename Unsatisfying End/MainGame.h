#pragma once
#include "GameScene.h"
#include "Animation.h"
#include "Boss.h"


class MainGame: public GameScene		//This is the scene where the actual game will run
{

	class PlayerBullet : //The bullets fired by the player
		public Character {

	private:
		bool canDealDamage = true;
	public:
		PlayerBullet(int tempHealth, sf::Vector2f position):		//Uses the same constructor as the Character class, but the texture and scale will always be the same for all bullets
			Character(tempHealth, position, sf::Vector2f(25,25), "./Sprites/Projectiles/PlayerBullet.png", sf::Vector2f(1,1), sf::Vector2f(5, 15), sf::Vector2f(-5,-15)) {}
		
		void CheckBossCollision(Character* boss) {
			if (hitBox.getPosition().x < (boss->hitBox.getPosition().x + (2 * boss->rect.x)) && (hitBox.getPosition().x + (2*rect.x)) > (boss->hitBox.getPosition().x)
			&& hitBox.getPosition().y < (boss->hitBox.getPosition().y + (2 * boss->rect.y)) && (hitBox.getPosition().y + (2 * rect.y)) >(boss->hitBox.getPosition().y)) 
			{
				if (canDealDamage) {
					boss->TakeDamage(1);
					canDealDamage = false;
				}
			}
		}

		void ChangePosition(sf::Vector2f newPosition) override {
			Character::ChangePosition(newPosition);
			canDealDamage = true;
		};
	};


	class Player : public Character
	{

	private:
		sf::Event* ev;		//This pointer allows the player character to get the playere's inputs and behave as needed
		sf::Vector2f velocity;	//Determines the current x and y velocity of the player
		
	public:

		std::vector<PlayerBullet*> allBullets;		//Stores all the instantiated bullets, making it easier to move all of the and execute functions for all bullets
		int currentBullet = 0;
		int maxBullets = 16;
		MainGame* currentScene;		//This pointer allows the player to access the game scene, and add each instantiated bullets to the spritesindisplay vector
		
		Player(sf::Event* tempEv, MainGame* tempScene, int tempHealth, sf::Vector2f position);	//These are the parameters required by the player

		bool isShooting = false;	//This boolean allows the player to hold space to spam projectiles, while also setting a time limit for the fire rate, this way the projectile spam doesn't take place every single frame
		sf::Clock clock;		//Clock used to calculate the cooldown between each fired bullet
		sf::Time fireRate;		//Time that counts the time passed between each bullet, regulating the player's fire rate

		void Movement();	//Moves the player
		void Shoot();		//Instatiate bullets 
		void Update();		//Is called by the scene to update the player object
		void DrawBullets();
	};

public:

	Player player = Player(localEv, this, 1, sf::Vector2f(450, 800));	//Player character inherits the same event pointer as the scene, making inputs consistent between object and scene
	Boss hanako = Boss(this, &this->player);

	SpriteObject backGround;		//The background will be just a sprite with no actual character attribute
	std::vector<Animation*> backgroundAnimations;		//Background animation
	sf::Clock clock;		//This clock will count the deltaTime  

	void Update() override;		//The update function for each scene will likely be different, which is why we override this function
	void ControlPlayer(sf::Event* tempEvent);		//Allows the scene to pass the inputs down to the player
	MainGame(sf::Event* tempEvent);

};

