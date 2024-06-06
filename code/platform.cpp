#include "platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	//ustawianie podstawowych parametrow
	body.setSize(size);
	body.setTexture(texture);
	body.setPosition(position);
	body.setOrigin(size / 2.0f); //ustawienia punktu odniesienia. Normalnie jest to lewy gorny rog, ale zeby kolizja AABB dzialala, potrzebne jest ustawienie tego po srodku.
	int a = int(size.x), b = int(size.y);
	//ustawianie odpowiedniej "klatki" platformy i ustawnienie na powtarzanie sie, zeby platformy lepiej wygladaly i laczly sie wizualnie
	body.setTextureRect(sf::IntRect(0, 0, a, b));
	texture->setRepeated(true);
}


void Platform::Draw(sf::RenderWindow& window) {
	window.draw(body);
}
