#include "powerup.h"

PowerUp::PowerUp(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims, sf::Vector2f size, sf::Vector2f position)
    : animation(texture, imageCount, switchTime, allAnims), active(true), collected(false) {
    this->anim = 0;

    body.setSize(size);
    body.setPosition(position);
    body.setTexture(texture);
    body.setOrigin(body.getSize() / 2.0f);
}

void PowerUp::Draw(sf::RenderWindow& window) {
    if (!collected) { // pokaż tylko jeśli nie zebrane
        window.draw(body);
    }
}

void PowerUp::Update(float deltaTime) {
    if (!collected) { // jeśli nie zebrane, to animuj
        animation.Update(anim, deltaTime, false);
        body.setTextureRect(animation.uvRect);
    }
}
