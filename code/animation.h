#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>


class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims);


	void Update(unsigned int anim, float deltaTime, bool faceLeft);

public:
	sf::IntRect uvRect;  //kwadrat do wyciecia tekstury

private:
	std::vector<std::vector<int>> allAnims; //vektor animacji
	int currentFrame; //numer klatkia

	sf::Vector2u imageCount; //na ile ma podzielic teksture
	sf::Vector2u currentImage; //aktualna klatka

	float totalTime; //ile minelo od ostatniej zmiany klatki
	float switchTime; //ile ma minac pomiedzy klatkami
	unsigned int usedAnim; //uzywana klatka
};

#endif // ANIMATION_H
