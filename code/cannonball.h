#ifndef CANNONBALL_H
#define CANNONBALL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "collider.h"
#include "platform.h" // Include the Platform header

class Cannonball {
public:
    Cannonball(sf::Texture* texture, sf::Vector2f position, sf::Vector2f direction);
    void Update(float deltaTime, std::vector<Platform>& platforms);
    void Draw(sf::RenderWindow& window);
    Collider GetCollider() { return Collider(body); }
    bool isOffScreen() const;
    bool hasHitPlayer() const { return hitPlayer; }
    void markHitPlayer() { hitPlayer = true; }

private:
    sf::RectangleShape body;
    sf::Vector2f velocity;
    bool hitPlayer;
};

#endif // CANNONBALL_H
