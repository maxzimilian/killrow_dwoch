#include "cannon.h"

Cannon::Cannon(sf::Texture* texture, sf::Vector2f position) : shootTimer(0), shootInterval(3.0f) {
    body.setSize(sf::Vector2f(32.0f, 32.0f));
    body.setTexture(texture);
    body.setPosition(position);
    body.setOrigin(body.getSize() / 2.0f);
}

void Cannon::Update(float deltaTime, sf::Vector2f playerPosition, std::vector<Cannonball>& cannonballs, sf::Texture* cannonballTexture) {
    shootTimer += deltaTime;
    if (shootTimer >= shootInterval) {
        shootTimer = 0;
        sf::Vector2f direction = playerPosition - body.getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; // Normalize direction
        cannonballs.push_back(Cannonball(cannonballTexture, body.getPosition(), direction));
    }
}

void Cannon::Draw(sf::RenderWindow& window) {
    window.draw(body);
}
