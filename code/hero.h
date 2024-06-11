
#include "animation.h"
#include "collider.h"

class Hero {
public:
    Hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims, float speed, float jumpHeight);

    void Update(float deltaTime, sf::Event event, sf::Text& text);
    void Draw(sf::RenderWindow& window);
    void OnCollision(sf::Vector2f direction);
    void restart();

    bool CheckCollisionWithLava(const sf::FloatRect& lavaBounds); // Sprawdzenie kolizji z lawą
    sf::Vector2f getPosition();
    Collider GetCollider() { return Collider(body); }

    void ApplyPowerUp(); // Zastosowanie power-upu
    void UpdatePowerUp(float deltaTime); // Aktualizacja stanu power-upu

    bool isPoweredUp() const { return poweredUp; } // Sprawdzenie, czy power-up jest aktywny
    float getPowerUpTimeLeft() const { return powerUpTimer; } // Pobranie pozostałego czasu power-upu

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int anim;
    float speed;
    bool faceLeft;
    bool poweredUp;
    float powerUpTimer;

    sf::Vector2f startPos = sf::Vector2f(100.0f, -10.0f); //pozycja startowa
	//(180.0f, 650.0f);    //poczatek gry
	//(100.0f, -10.0f);  //koniec gry (do testowania)
    sf::Vector2f velocity;

    bool canJump;
    float jumpHeight;
    float jump;
};

