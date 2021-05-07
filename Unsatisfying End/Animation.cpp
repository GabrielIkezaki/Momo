#include "Animation.h"

//The animation constructor sets the texture, number of collumns and rows, and time between frames of an animation
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	totalTime = 0;	//The timer will start at 0

	currentImage.x = 0;	//The current collumn that will be displayed
	currentImage.y = 0;	//The current row that will be displayed
	uvRect.width = texture->getSize().x / float(imageCount.x);		//Dividing the sprite sheet width by the number of collumns 
	uvRect.height = texture->getSize().y / float(imageCount.y);		//Dividing the sprite sheet height by the number of rows
}

void Animation::Update(float deltaTime) {

	totalTime += deltaTime;		//The timer will start counting, letting the animation switch frames proportionally to deltaTime

	if (totalTime >= switchTime) {	//If the timer reaches the time it takes to switch frames
		totalTime -= switchTime;	//It will reset
		currentImage.x++;		//The rect will move to the next column

		if (currentImage.x >= imageCount.x) {	//If the rect reaches the last sprite on the collumn
			currentImage.x = 0; //The rect will return to the initial column
			currentImage.y++;	//But the row will be set to the next one
		}

		if (currentImage.y >= imageCount.y) {		//If the rect reaches the last column
			currentImage.y = 0;		//The rect will go back to its first cell
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;	//By multiplying the rect width by the collumn number, we get the x coordinte of the current frame
	uvRect.top = currentImage.y * uvRect.height;	//Same goes for multiplying the row number by the height of the frame. 
}