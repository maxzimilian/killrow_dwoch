#include "lava.h"

Lava::Lava(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
    initialSize = size;
    body.setSize(sf::Vector2f(size.x, 0)); 
    body.setTexture(texture); 
    body.setPosition(position); 
    body.setOrigin(size.x / 2.0f, 0.0f); 
    speed = 0.0f;
    startPos = position; 
}

void Lava::Draw(sf::RenderWindow& window) {
    window.draw(body); 
}

void Lava::Update(float deltaTime) {
    body.setSize(sf::Vector2f(initialSize.x, body.getSize().y + speed * deltaTime));
    body.setPosition(startPos.x, startPos.y - body.getSize().y); // Przemieszczanie lawy w górę
}

void Lava::IncreaseLevel(float amount) {
    speed = amount; 
}

void Lava::ResetPosition() {
    body.setPosition(startPos); // Resetowanie pozycji lawy
    body.setSize(sf::Vector2f(initialSize.x, 0));  // Resetowanie rozmiaru lawy (wysokość 0)
    speed = 0.0f; // Resetowanie szybkości
}
