
#include <SFML/Graphics.hpp>

class Lava {
public:
    Lava(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    void Draw(sf::RenderWindow& window);
    void Update(float deltaTime);

    void IncreaseLevel(float amount);
    void ResetPosition();

    sf::FloatRect getBounds() { return body.getGlobalBounds(); }

private:
    sf::RectangleShape body; // Prostokąt reprezentujący lawę
    float speed; // Szybkość podnoszenia się lawy
    sf::Vector2f startPos; // Początkowa pozycja lawy
    sf::Vector2f initialSize; // Początkowy rozmiar lawy
};

#endif // LAVA_H
