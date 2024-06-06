#ifndef HERO_H
#define HERO_H
#include "animation.h"
#include "collider.h"


class Hero
{
public:
	Hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims, float speed, float jumpHeight);


	void Update(float deltaTime, sf::Event event, sf::Text& text);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void restart();

	sf::Vector2f getPosition();
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body; //obiekt na ktorym bedzie animacja
	Animation animation; //animacje
	unsigned int anim; //numer aktualniej animacji
	float speed; //szybkosc bohatera
	bool faceLeft; //zwrot w poziomie

	sf::Vector2f startPos = sf::Vector2f(180.0f, 650.0f); //pozycja startowa
	//(180.0f, 650.0f);    //poczatek gry
	//(100.0f, -10.0f);  //koniec gry (do testowania)

	sf::Vector2f velocity; //predkosc
	bool canJump; //czy dotyka ziemi i moze skoczyc
	float jumpHeight; //wysokosc skoku
	float jump; //ladowanie skoku (im dluzej trzymasz tym wyzej skaczesz)

};

#endif // HERO_H
