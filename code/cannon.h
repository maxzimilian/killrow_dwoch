#ifndef CANNON_H
#define CANNON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "cannonball.h"

class Cannon {
public:
    Cannon(sf::Texture* texture, sf::Vector2f position);
    void Update(float deltaTime, sf::Vector2f playerPosition, std::vector<Cannonball>& cannonballs, sf::Texture* cannonballTexture);
    void Draw(sf::RenderWindow& window);

private:
    sf::RectangleShape body;
    float shootTimer;
    float shootInterval;
};

#endif // CANNON_H