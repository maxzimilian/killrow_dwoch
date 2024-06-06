#ifndef ITEM_H
#define ITEM_H
#include "collider.h"
#include "animation.h"

class Item
{
public:
	Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims, sf::Vector2f size, sf::Vector2f position);

	//dziala podobnie do bohatera, tylko bez poruszania sie i z innymi colliderami i rozmiarami
	void Draw(sf::RenderWindow& window);
	Collider Getcollider() { return Collider(body); }
	void Update(float deltaTime);


private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int anim;
};

#endif // ITEM_H
