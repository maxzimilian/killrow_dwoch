#pragma once
#include "collider.h"
#include "animation.h"

class PowerUp {
public:
    PowerUp(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims, sf::Vector2f size, sf::Vector2f position);

    void Draw(sf::RenderWindow& window);
    Collider GetCollider() { return Collider(body); }
    void Update(float deltaTime);
    bool isActive() const { return active && !collected;}
    void collect() { collected = true; } // ustawienie czy zebrane na prawda

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int anim;
    bool active;
    bool collected; // czy zebrane
};
