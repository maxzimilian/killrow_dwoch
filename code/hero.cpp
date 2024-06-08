#include "hero.h"

Hero::Hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims, float speed, float jumpHeight)
    : animation(texture, imageCount, switchTime, allAnims), startPos(sf::Vector2f(100.0f, -10.0f)) {
    this->speed = speed;
    this->anim = 0;
    this->jumpHeight = jumpHeight;
    faceLeft = true;
    canJump = false;
    jump = 0;
    isPoweredUp = false; // Inicjalizacja stanu power-up
    powerUpTimer = 0.0f;

    body.setSize(sf::Vector2f(13.0f, 20.f));
    body.setPosition(startPos);
    body.setTexture(texture);
    body.setOrigin(body.getSize() / 2.0f);
}

void Hero::restart() {
    body.setPosition(startPos);
    isPoweredUp = false; // Resetowanie stanu power-up
    powerUpTimer = 0.0f; // Resetowanie timera power-up
    jumpHeight = 60.0f; // Resetowanie wysokości skoku do wartości początkowej
}

void Hero::ApplyPowerUp() {
    isPoweredUp = true;
    powerUpTimer = 10.0f; // Czas trwania power-up
    jumpHeight *= 1.5f; // Wzrost wysokości skoku
}

void Hero::UpdatePowerUp(float deltaTime) {
    if (isPoweredUp) {
        powerUpTimer -= deltaTime;
        if (powerUpTimer <= 0) {
            isPoweredUp = false;
            jumpHeight /= 1.5f; // Resetowanie wysokości skoku po wygaśnięciu power-up
        }
    }
}

void Hero::Update(float deltaTime, sf::Event event, sf::Text& text) {
    if (canJump) {
        velocity.x = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            anim = 2;
            jump += deltaTime;
            jump = std::min(std::max(jump, 0.0f), 1.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                faceLeft = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                faceLeft = false;
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                velocity.x -= speed / 2.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                velocity.x += speed / 2.5f;
            }
            if (velocity.x == 0.0f) {
                anim = 0;
            } else {
                anim = 1;
                faceLeft = velocity.x < 0.0f;
            }
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            canJump = false;
            velocity.y = -sqrtf(2.0f * 98.1f * jumpHeight) * jump;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                velocity.x = (-speed / 2.5) * jump;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                velocity.x = (speed / 2.5) * jump;
            }
        }
    } else {
        jump = 0;
        anim = velocity.y > 0.0f ? 3 : 4;
    }

    velocity.y += 98.1f * deltaTime;

    animation.Update(anim, deltaTime, faceLeft);

    body.setTextureRect(animation.uvRect);
    body.move(velocity * deltaTime);
    canJump = false;
    text.setPosition(sf::Vector2f(body.getPosition().x - 148.0f, body.getPosition().y - 150.0f));
    UpdatePowerUp(deltaTime);
}

void Hero::Draw(sf::RenderWindow& window) {
    window.draw(body);
}

void Hero::OnCollision(sf::Vector2f direction) {
    if (direction.x != 0.0f) {
        velocity.x *= -1.0f;
    }
    if (direction.y < 0.0f) {
        velocity.y = 0.0f;
        canJump = true;
    } else if (direction.y > 0.0f) {
        velocity.y = 0.0f;
    }
}

sf::Vector2f Hero::getPosition() {
    return body.getPosition();
}

bool Hero::CheckCollisionWithLava(const sf::FloatRect& lavaBounds) {
    return body.getGlobalBounds().intersects(lavaBounds);
}
