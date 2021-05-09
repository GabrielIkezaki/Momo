#include "MainGame.h"

//The player constructor will pass variables to the Character constructor (namely health and position), however, the texture and sprite scale will always remain the same
MainGame::Player::Player(sf::Event* tempEv, MainGame* tempScene, int tempHealth, sf::Vector2f position):
	Character(tempHealth, position,"./Sprites/Characters/momo.png", sf::Vector2f(.2f, .2f), sf::Vector2f(15, 20), sf::Vector2f(15, 10)) {
	ev = tempEv;
	currentScene = tempScene;
}

void MainGame::Player::Movement(){

	//I decided not to use switch statements, because I wanted the player to move for whatever direction the player is holding as opposed to the last direction they'd pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x = -250;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x = 250;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y = -250;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y = 250;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x = 0;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y = 0;
	}

	Character::Move(velocity);	//Whatever x and y values are set in this frame, they'll be passed down  to the Move velocity of the Character class
}


void MainGame::Player::Shoot() {

	//As long as the player is holding down space and the fire cooldown is over the required limit (0.07 seconds)
	if (isShooting && fireRate.asSeconds() > .07f) {
		
		allBullets.push_back(new PlayerBullet(1, characterSprite.position));	//The player will add a new bullet to its list
		currentScene->GameScene::AddObject(&allBullets[allBullets.size() - 1]->characterSprite);		//The player will pass down the new bullet to the scene, so that it may be displayed


		clock.restart();		//The fire cooldown will restart
	}

	if (allBullets.size() != 0) {	//As long as there is at least 1 bullet
		for (int i = 0; i < allBullets.size(); i++) {	//For every bullet in the list
			allBullets[i]->Character::Move(sf::Vector2f(0, -1000));		//The player will make the bullets Move
			allBullets[i]->Character::UpdateRect();
			allBullets[i]->CheckBossCollision(&currentScene->hanako);
		}	
	}

}

void MainGame::Player::Update() {
	Movement();		//The player will always check for movement and update its position accordingly
	Character::UpdateRect();
	fireRate = clock.getElapsedTime();	//The fire rate will be constantly increasing. It will, however, be reset if a bullet is shot
	Shoot();		//The player will check for new fired bullets each frame as well
}



MainGame::MainGame(sf::Event* tempEvent) : GameScene(tempEvent) {	//The event pointer will be passed down to the gamescene constructor


	//Right as the game starts, the background's sprite will be defined
	backGround.Set("./Sprites/Bgrounds/BgroundSheet.png", sf::Vector2f(0,0), sf::Vector2f(3.5f, 3.5f));

	//The background will add a new animation, which will be its only one too. This animation will take the image of the same texture as the background's sprite, the sheet will have 1 column and 3 rows, and the switch time for each proceeding frame is .2f
	backgroundAnimations.push_back(new Animation(&backGround.objectTexture, sf::Vector2u(1, 3), .2f));	

	GameScene::AddObject(&backGround);	//The bacground will be the first sprite added to the spritesindisplay list, as it needs to be rendered first (behind everything else)
	GameScene::AddObject(&hanako.characterSprite);
	GameScene::AddObject(&player.characterSprite);	//The player will then be added to the spritesindisplay list
}

void MainGame::ControlPlayer(sf::Event* tempEvent) {	//FThis function is called in the pollevents function of the Game.cpp file, it reads the player's input and control the player character

	if (tempEvent->key.code == sf::Keyboard::Space && tempEvent->type == sf::Event::KeyPressed) {	//If the user's input was a key press, and the pressed key was the space bar 
		std::cout << "PRESS" << std::endl;
		player.isShooting = true;		//The player will start shooting	
	}
	else if(tempEvent->key.code == sf::Keyboard::Space && tempEvent->type == sf::Event::KeyReleased){	//However, if the player releases the space
		player.isShooting = false;	//The player will stop shooting
	}

}

void MainGame::Update() {
	player.Update();
	hanako.Update();
	backgroundAnimations[0]->Update(deltaTime);	//The backgroundanimation will count the switchtime according to the external deltaTime variable
	backGround.SwitchSpriteFrame(backgroundAnimations[0]->uvRect);	//The background will change frame accordingly
//	window->draw(player.rectangle);
}
 
