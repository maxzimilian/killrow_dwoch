#include "collider.h"

Collider::Collider(sf::RectangleShape& body) : body(body) {

}
//Sprawdzanie kolizji AABB, czyli sprawdzanie od srodka prostokata, jezeli jeden dotknal drugiego
bool Collider::CheckCollison(Collider & other, sf::Vector2f& direction, float push) {
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = sf::Vector2f(other.GetHalfSize().x / 2.0f, other.GetHalfSize().y);
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	//ronica pomiedzy x i y odleglosci
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	//sprawdzanie czy nachodza na siebie wzgledem osi(jezeli odleglosc jest mniejsza niz suma polowek prostokata, to tak)
	float intersectX = fabs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = fabs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	//rozpatrywanie czy nachodza na siebie (musi byc X i Y) oraz z ktorego kierunku
	if (intersectX < 0.0f && intersectY < 0.0f) {
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY) {
			if (deltaX > 0.0f) {
				Move(intersectX * (1.0 - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);

				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else {
				Move(-intersectX * (1.0 - push), 0.0f);
				other.Move(intersectX * push, 0.0f);

				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else {
			if (deltaY > 0.0f) {
				Move(0.0f, intersectY * (1.0 - push));
				other.Move(0.0f, -intersectY * push);

				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else {
				Move(0.0f, -intersectY * (1.0 - push));
				other.Move(0.0f, intersectY * push);

				direction.x = 0.0f;
				direction.y = -1.0f;
			}

		}

		return true;
	}
	return false;
}