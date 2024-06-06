#include "animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims)
{
	this->imageCount = imageCount; 
	this->switchTime = switchTime;
	this->allAnims = allAnims;
	totalTime = 0.0f; 
	currentImage.x = 0;
	currentImage.y = 0;
	currentFrame = 0; 
	usedAnim = 0; 
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}


void Animation::Update(unsigned int anim, float deltaTime, bool faceLeft) {
	currentImage.y = allAnims[anim][currentFrame] / imageCount.x; //wiersz
	currentImage.x = allAnims[anim][currentFrame] % imageCount.x; //kolumna

	totalTime += deltaTime; //ile mineo od ostatniej klatki

	if (usedAnim != anim) { //po zmianie animacji, resetuje
		currentFrame = 0;
		totalTime = 0.0f;
	}
	else if (totalTime >= switchTime / float(allAnims[anim].size())) { //zmiana klatki po odpowiednim czasie
		totalTime -= switchTime / float(allAnims[anim].size()); 
		currentFrame++;

		if (currentFrame >= int(allAnims[anim].size())) {
			currentFrame = 0;
		}
	}
	if (faceLeft) { //ustawianie w pioziome w zaleznosci od kierunku
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else {
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
	usedAnim = anim;
	uvRect.top = currentImage.y * uvRect.height;
}
