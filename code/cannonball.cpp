#include "cannonball.h"
#include "platform.h" // Include the Platform header if not already included

Cannonball::Cannonball(sf::Texture* texture, sf::Vector2f position, sf::Vector2f direction)
    : velocity(direction * 100.0f), hitPlayer(false) {
    body.setSize(sf::Vector2f(10.0f, 10.0f));
    body.setTexture(texture);
    body.setPosition(position);
    body.setOrigin(body.getSize() / 2.0f);
}

void Cannonball::Update(float deltaTime, std::vector<Platform>& platforms) {
    body.move(velocity * deltaTime);

    // Collision with platforms
    Collider collider = GetCollider();
    sf::Vector2f direction;
    for (Platform& platform : platforms) {
        if (platform.Getcollider().CheckCollison(collider, direction, 1.0f)) {
            if (direction.x != 0.0f) velocity.x *= -1.0f;
            if (direction.y != 0.0f) velocity.y *= -1.0f;
        }
    }

    // Check if off screen
    if (body.getPosition().y > 800.0f) {
        hitPlayer = true; // Mark for removal
    }
}

void Cannonball::Draw(sf::RenderWindow& window) {
    window.draw(body);
}

bool Cannonball::isOffScreen() const {
    return body.getPosition().y > 800.0f;
}
