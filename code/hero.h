// hero.h

#ifndef HERO_H
#define HERO_H
#include "animation.h"
#include "collider.h"

class Hero {
public:
    Hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims, float speed, float jumpHeight);

    void Update(float deltaTime, sf::Event event, sf::Text& text);
    void Draw(sf::RenderWindow& window);
    void OnCollision(sf::Vector2f direction);
    void restart();

    bool CheckCollisionWithLava(const sf::FloatRect& lavaBounds); // Add this line
    sf::Vector2f getPosition();
    Collider GetCollider() { return Collider(body); }

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int anim;
    float speed;
    bool faceLeft;

    sf::Vector2f startPos = sf::Vector2f(180.0f, 650.0f);

    sf::Vector2f velocity;
    bool canJump;
    float jumpHeight;
    float jump;
};

#endif // HERO_H
