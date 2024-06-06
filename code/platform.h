#ifndef PLATFORM_H
#define PLATFORM_H
#include "collider.h"


class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

	void Draw(sf::RenderWindow& window); //tekstura platformy
	Collider Getcollider() { return Collider(body); } //zwracanie kolizji

private:
	sf::RectangleShape body;
};

#endif // PLATFORM_H
