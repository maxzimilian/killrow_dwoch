#ifndef LAVA_H
#define LAVA_H

#include <SFML/Graphics.hpp>

class Lava {
public:
    Lava(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    void Draw(sf::RenderWindow& window);
    void Update(float deltaTime);

    void IncreaseLevel(float amount);

    sf::FloatRect getBounds() { return body.getGlobalBounds(); }

private:
    sf::RectangleShape body;
    float speed;
};

#endif // LAVA_H