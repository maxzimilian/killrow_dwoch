#include "lava.h"

Lava::Lava(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
    body.setTexture(texture);
    body.setPosition(position);
    body.setOrigin(size / 2.0f);
    speed = 0.0f;
}

void Lava::Draw(sf::RenderWindow& window) {
    window.draw(body);
}

void Lava::Update(float deltaTime) {
    body.move(0, -speed * deltaTime);
}

void Lava::IncreaseLevel(float amount) {
    speed = amount;
}
