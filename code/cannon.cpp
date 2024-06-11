#include "cannon.h"
#include <cmath> // For std::sqrt

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

        // Calculate the spawn position as the top-left corner of the cannon
        sf::Vector2f spawnPosition = body.getPosition() - sf::Vector2f(body.getSize().x / 2.0f, body.getSize().y / 2.0f);

        // Calculate the direction from the spawn position to the player's position
        sf::Vector2f direction = playerPosition - spawnPosition;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; // Normalize direction

        cannonballs.push_back(Cannonball(cannonballTexture, spawnPosition, direction));
    }
}

void Cannon::Draw(sf::RenderWindow& window) {
    window.draw(body);
}
