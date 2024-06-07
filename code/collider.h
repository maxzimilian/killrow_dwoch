#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
#include <cmath>


class Collider
{
public:
	Collider(sf::RectangleShape& body);

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollison(Collider & other, sf::Vector2f& direction, float push); //push - pushability of the object (nie wiem jak to po polsku opisaæ)
	sf::Vector2f GetPosition() { return body.getPosition(); } 
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

private:
	sf::RectangleShape& body;
};

#endif // COLLIDER_H