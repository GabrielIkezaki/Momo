#include "GameScene.h"

void GameScene::Display(sf::RenderWindow* tempwindow) {		//The window that had been passed down will draw all items in the sprites list
	window = tempwindow;

	
	for (int i = 0; i < spritesInDisplay.size(); i++) {	
		tempwindow->draw(spritesInDisplay[i]->objectSprite);
	}
}

void GameScene::AddObject(SpriteObject* newCharacter) {		//Adds a anew sprite to the sprites to be displayed in the scene
	spritesInDisplay.push_back(newCharacter);
}

GameScene::GameScene(sf::Event* tempEvent){	//Gets the Game event
	localEv = tempEvent;
}

