#include "hero.h"
#include "powerup.h"
#include "platform.h"
#include "item.h"
#include "Menu.h"
#include "lava.h"

static const float VIEW_HEIGHT = 300.0f; // ustawienie wielkosci okna

void resizeView(sf::RenderWindow& window, sf::View& view) { // funkcja do skalowania rozmiaru okna
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

// funkcja do resetowania gry
void resetGame(Hero& hero, std::vector<Item>& items, Lava& lava, std::vector<Platform>& platforms, sf::Texture& monsterTexture, const std::vector<std::vector<int>>& monsterAnims, int& points, sf::Text& text, PowerUp& powerUp) {
    points = 0;
    text.setString("Points : " + std::to_string(points));
    items.clear();
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(152.0f, 624.0f)));
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(200.0f, 348.0f)));
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(360.0f, 332.0f)));
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(120.0f, -10.0f)));
    hero.restart();
    lava.ResetPosition();
    powerUp = PowerUp(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(240.0f, 200.0f)); // Resetowanie power-up
}

int main() {
    sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "Jumping timber");
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    Menu menu(VIEW_HEIGHT, VIEW_HEIGHT); // menu gry
    bool menu_is_open = true; // czy gra ma otwarte okno menu
    bool end = false; // czy gra juz sie skonczyla
    bool died = false; // czy gracz umarl
    int points = 0; // ilosc zebranych punktow

    sf::Font font;
    if (!font.loadFromFile("Pixel.ttf")) { // [utopiafonts] 1999 free font, 1999 utopiafonts. dale_thorpe@bssc.edu.au, https://www.1001fonts.com/pixel-font.html
        return 1;
    }
    
    // tekst z iloscia punktow gracza, ktory bedzie podawany w lewym gornym rogu
    sf::Text text;
    text.setFont(font);
    text.setString("Points : " + std::to_string(points));
    text.setCharacterSize(64);
    text.setScale(0.2, 0.2);
    text.setFillColor(sf::Color(100, 80, 160));
    text.setOutlineColor(sf::Color(73, 5, 55));
    text.setOutlineThickness(3);

    // tekst z czasem trwania power-upu
    sf::Text powerUpTimerText;
    powerUpTimerText.setFont(font);
    powerUpTimerText.setString("Power-Up Time: 0");
    powerUpTimerText.setCharacterSize(64);
    powerUpTimerText.setScale(0.2, 0.2);
    powerUpTimerText.setFillColor(sf::Color(255, 255, 0));
    powerUpTimerText.setOutlineColor(sf::Color(73, 5, 55));
    powerUpTimerText.setOutlineThickness(3);

    // globalny timer gry
    sf::Text gameTimerText;
    gameTimerText.setFont(font);
    gameTimerText.setString("Time: 0");
    gameTimerText.setCharacterSize(64);
    gameTimerText.setScale(0.2, 0.2);
    gameTimerText.setFillColor(sf::Color::White);
    gameTimerText.setOutlineColor(sf::Color::Black);
    gameTimerText.setOutlineThickness(3);

    // napis koncowy gry
    sf::Text congrats;
    congrats.setFont(font);
    congrats.setString("Congratulations!!!\n You managed to escape\n and get " + std::to_string(points) + " points.");
    congrats.setCharacterSize(64);
    congrats.setScale(0.2, 0.2);
    congrats.setOrigin(sf::Vector2f(500, 250));
    congrats.setPosition(1000, 1000);
    congrats.setFillColor(sf::Color(200, 160, 20));
    congrats.setOutlineColor(sf::Color::Black);
    congrats.setOutlineThickness(3);

    // napis o smierci gracza
    sf::Text deathMessage;
    deathMessage.setFont(font);
    deathMessage.setString("You Died!\nBetter luck next time!\n You collected " + std::to_string(points) + " points.");
    deathMessage.setCharacterSize(64);
    deathMessage.setScale(0.2, 0.2);
    deathMessage.setOrigin(sf::Vector2f(500, 250));
    deathMessage.setPosition(1000, 1000);
    deathMessage.setFillColor(sf::Color::Red);
    deathMessage.setOutlineColor(sf::Color::Black);
    deathMessage.setOutlineThickness(3);

    // napis o nadchodzacej lawie
    sf::Text lavaWarning;
    lavaWarning.setFont(font);
    lavaWarning.setString("Lava is coming!");
    lavaWarning.setCharacterSize(64);
    lavaWarning.setScale(0.3, 0.3);
    lavaWarning.setFillColor(sf::Color::Red);
    lavaWarning.setOutlineColor(sf::Color::Black);
    lavaWarning.setOutlineThickness(3);

    // power-up message
    sf::Text powerUpMessage;
    float powerUpMessageTimer = 0.0f;
    powerUpMessage.setFont(font);
    powerUpMessage.setString("Power-Up Collected!");
    powerUpMessage.setCharacterSize(64);
    powerUpMessage.setScale(0.3, 0.3);
    powerUpMessage.setFillColor(sf::Color::Green); // Set a different color
    powerUpMessage.setOutlineColor(sf::Color::Black);
    powerUpMessage.setOutlineThickness(3);

    // tekstury do wykorzystania dla gracza, platform oraz "itemow" do zbierania
    sf::Texture texture, planeTexture, tileTexture, sTileTexture, rockTexture, monsterTexture, lavaTexture;
    if (!texture.loadFromFile("textures/hero.png") ||
        !sTileTexture.loadFromFile("textures/sTile.png") ||
        !tileTexture.loadFromFile("textures/tile.png") ||
        !rockTexture.loadFromFile("textures/rock.png") ||
        !monsterTexture.loadFromFile("textures/monsters.png") ||
        !planeTexture.loadFromFile("textures/plane.png") ||
        !lavaTexture.loadFromFile("textures/lava.png")) {
        return 1;
    }

    std::vector<std::vector<int>> allAnims; // animacje bohatera
    allAnims.push_back(std::vector<int>{0, 1, 1, 2, 2, 1, 1, 0}); // animacja bezruchu
    allAnims.push_back(std::vector<int>{4, 4, 7, 6, 5, 5, 6, 7}); // animacja biegu
    allAnims.push_back(std::vector<int>{3, 3, 3, 3, 3, 3, 3, 3}); // animacja przygotowania do skoku
    allAnims.push_back(std::vector<int>{4, 4, 4, 4, 4, 4, 4, 4}); // animacja skoku
    allAnims.push_back(std::vector<int>{8, 8, 8, 8, 8, 8, 8, 8}); // animacja spadania

    Hero hero(&texture, sf::Vector2u(4, 3), 0.5f, allAnims, 100.0f, 60.0f);

    // animacja "itemow" / potworkow
    std::vector<std::vector<int>> monsterAnims;
    monsterAnims.push_back(std::vector<int>{12, 13, 14, 13});

    // wektor wszystkich platform, ktory ulatwi potem wyswietlanie i sprawdzanie kolizji
    std::vector<Platform> platforms;
    // tiles
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(512.0f, 160.0f), sf::Vector2f(256.0f, 800.0f))); // dolna ściana
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(288.0f, 1000.0f), sf::Vector2f(0.0f, 500.0f))); //lewa 144 800  72 400 - stara
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(288.0f, 1000.0f), sf::Vector2f(512.0f, 400.0f))); //prawa
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(32.0f, 128.0f), sf::Vector2f(160.0f, 704.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(208.0f, 656.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(32.0f, 32.0f), sf::Vector2f(288.0f, 704.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(48.0f, 32.0f), sf::Vector2f(344.0f, 656.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(152.0f, 600.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(32.0f, 16.0f), sf::Vector2f(240.0f, 536.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(168.0f, 504.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(306.0f, 536.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(360.0f, 504.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(96.0f, 128.0f), sf::Vector2f(256.0f, 400.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(64.0f, 80.0f), sf::Vector2f(224.0f, 296.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(312.0f, 410.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(360.0f, 360.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(32.0f, 80.0f), sf::Vector2f(352.0f, 264.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(32.0f, 16.0f), sf::Vector2f(272.0f, 264.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(200.0f, 370.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(152.0f, 264.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(160.0f, 32.0f), sf::Vector2f(256.0f, 32.0f))); //najwyzsza platforma przy statku - stara
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(128.0f, 128.0f), sf::Vector2f(448.0f, -64.0f)));

    // small Tiles
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(290.0f, 600.0f)));
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(200.0f, 558.0f)));
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(324.0f, 450.0f)));
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(155.0f, 320.0f)));
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(184.0f, 210.0f)));
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(200.0f, 180.0f)));
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(250.0f, 165.0f)));
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(290.0f, 165.0f)));
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(360.0f, 110.0f)));
    platforms.push_back(Platform(&sTileTexture, sf::Vector2f(8.0f, 8.0f), sf::Vector2f(340.0f, 55.0f)));

    // rocks
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(3.0f, 64.0f), sf::Vector2f(256.0f, 650.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(3.0f, 8.0f), sf::Vector2f(340.0f, 415.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(6.0f, 4.0f), sf::Vector2f(340.0f, 360.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(6.0f, 4.0f), sf::Vector2f(310.0f, 290.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(3.0f, 4.0f), sf::Vector2f(185.0f, 450.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(3.0f, 4.0f), sf::Vector2f(165.0f, 430.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(3.0f, 4.0f), sf::Vector2f(185.0f, 450.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(3.0f, 4.0f), sf::Vector2f(180.0f, 400.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(6.0f, 4.0f), sf::Vector2f(165.0f, 370.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(3.0f, 32.0f), sf::Vector2f(175.0f, 310.0f)));
    platforms.push_back(Platform(&rockTexture, sf::Vector2f(3.0f, 16.0f), sf::Vector2f(340.0f, 150.0f)));

    // wektor itemow / potworkow
    std::vector<Item> items;
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(152.0f, 624.0f)));
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(200.0f, 348.0f)));
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(360.0f, 332.0f)));
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(120.0f, -10.0f)));

    // nasz cel koncowy, statek do ucieczki
    Platform plane(&planeTexture, sf::Vector2f(72.0f, 36.0f), sf::Vector2f(50.0f, -20.0f));

    // lawa, ktora bedzie sie podnosic
    Lava lava(&lavaTexture, sf::Vector2f(600.0f, 800.0f), sf::Vector2f(180.0f, 800.0f)); // Initial height 0, expands upwards

    //power up skoku
    PowerUp powerUp(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(240.0f, 200.0f));  

    float deltaTime = 0.0f; // czas pomiedzy petlami

    sf::Clock clock;
    sf::Clock gameClock; // global timer clock
    window.setFramerateLimit(120); // maksymalna ilosc klatek na sekunde

    float idleTime = 0.0f;
    sf::Vector2f previousPosition = hero.getPosition();
    bool showLavaWarning = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizeView(window, view);
                break;
            case sf::Event::KeyReleased:
                if (menu_is_open) { // opcje menu
                    switch (event.key.code) {
                    case sf::Keyboard::W:
                        menu.moveUp();
                        break;
                    case sf::Keyboard::S:
                        menu.moveDown();
                        break;
                    case sf::Keyboard::Return: // enter
                        switch (menu.GetPressedItem()) { // po wybraniu opcji z menu
                        case 0: // wraca do gry
                            menu_is_open = !menu_is_open;
                            menu.closeMenu();
                            if (died || end) {
                                resetGame(hero, items, lava, platforms, monsterTexture, monsterAnims, points, text, powerUp);
                                gameClock.restart(); // Restart global timer
                                end = false;
                                died = false;
                            }
                            break;
                        case 1: // restartuje gre, poprzez reset punktow, pozycji gracza, wektora itemow oraz zmienienie boola zakonczenia gry
                            resetGame(hero, items, lava, platforms, monsterTexture, monsterAnims, points, text, powerUp);
                            gameClock.restart(); // Restart global timer
                            menu.closeMenu();
                            end = false;
                            died = false;
                            menu_is_open = false;
                            break;
                        case 2: // zamyka gre
                            window.close();
                            break;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Escape) { // escape zeby otworzyc/zamknac menu
                    menu_is_open = !menu_is_open;
                    menu.closeMenu();
                }
                break;
                
            }
        }

        deltaTime = clock.restart().asSeconds(); // ile minelo od ostatniej petli

        // Update the power-up message timer
        if (powerUpMessageTimer > 0.0f) {
            powerUpMessageTimer -= deltaTime;
        }

        // Update global game timer
        sf::Time gameTime = gameClock.getElapsedTime();
        gameTimerText.setString("Time: " + std::to_string(static_cast<int>(gameTime.asSeconds())));

        // update pozycji
        sf::Vector2f currentPosition = hero.getPosition();

        if (currentPosition == previousPosition) {
            idleTime += deltaTime;
            if (idleTime >= 2.0f && idleTime < 3.0f) {
                showLavaWarning = true;
            }
            if (idleTime >= 3.0f) {
                lava.IncreaseLevel(10.0f);
                showLavaWarning = false;
            }
        } else {
            idleTime = 0.0f;
            lava.IncreaseLevel(0.0f);
            showLavaWarning = false;
        }

        previousPosition = currentPosition;

        hero.Update(deltaTime, event, text);
        for (Item& item : items) {
            item.Update(deltaTime);
        }

        powerUp.Update(deltaTime);  

        lava.Update(deltaTime);

        // Update the power-up timer text
        if (hero.isPoweredUp()) {
            powerUpTimerText.setString("Power-Up Time: " + std::to_string(static_cast<int>(hero.getPowerUpTimeLeft())));
            powerUpTimerText.setPosition(text.getPosition().x, text.getPosition().y + 20);
        } else {
            powerUpTimerText.setString("");
        }

        // sprawdzenie kolizji
        Collider pCollision = hero.GetCollider();
        sf::Vector2f direction;

        for (Platform& p : platforms) {
            if (p.Getcollider().CheckCollison(pCollision, direction, 1.0f)) {
                hero.OnCollision(direction);
            }
        }

        if (plane.Getcollider().CheckCollison(pCollision, direction, 1.0f)) {
            end = true;
        }

        for (unsigned int i = 0; i < items.size(); ++i) {
            if (items[i].Getcollider().CheckCollison(pCollision, direction, 0.0f)) {
                hero.OnCollision(direction);
                items.erase(items.begin() + i);
                ++points;
                text.setString("Points : " + std::to_string(points));
                congrats.setString("Congratulations!!!\n You managed to escape\n and get " + std::to_string(points) + " points.");
                deathMessage.setString("You Died!\nBetter luck next time!\n You collected " + std::to_string(points) + " points.");
            }
        }

        if (powerUp.isActive() && powerUp.GetCollider().CheckCollison(pCollision, direction, 0.0f)) {
            hero.ApplyPowerUp();
            powerUp.collect(); // Mark as collected
            powerUpMessageTimer = 2.0f; // Show message for 2 seconds
        }

        if (hero.CheckCollisionWithLava(lava.getBounds())) {
            end = true;
            died = true;
        }

        if (end) { // scena koncowa
            view.setCenter(1000, 1000);
            menu.setPosition(sf::Vector2f(1000, 1000), 300);
        } else {
            // ustawianie widoku na gracza
            view.setCenter(hero.getPosition());
            menu.setPosition(hero.getPosition(), 300);

            // Update the position of the global game timer text
            gameTimerText.setPosition(view.getCenter().x - gameTimerText.getGlobalBounds().width / 2, view.getCenter().y - view.getSize().y / 2 + 10);
        }

        // czyscimy okno
        window.clear(sf::Color(80, 40, 120));
        window.setView(view);

        // rysujemy wszystko
        for (Platform& p : platforms) {
            p.Draw(window);
        }

        for (Item& item : items) {
            item.Draw(window);
        }

        plane.Draw(window);
        hero.Draw(window);
        lava.Draw(window);
        powerUp.Draw(window);

        window.draw(text);
        window.draw(powerUpTimerText); // Draw the power-up timer text
        window.draw(gameTimerText); // Draw the global game timer
        if (died) {
            window.draw(deathMessage);
        } else {
            window.draw(congrats);
        }

        if (showLavaWarning) {
            lavaWarning.setOrigin(lavaWarning.getLocalBounds().width / 2.0f, lavaWarning.getLocalBounds().height / 2.0f);
            lavaWarning.setPosition(view.getCenter());
            window.draw(lavaWarning);
        }

        if (powerUpMessageTimer > 0.0f) {
            powerUpMessage.setOrigin(powerUpMessage.getLocalBounds().width / 2.0f, powerUpMessage.getLocalBounds().height / 2.0f);
            powerUpMessage.setPosition(view.getCenter());
            window.draw(powerUpMessage);
        }

        if (menu_is_open) {
            window.clear(sf::Color(100, 60, 100));
            menu.draw(window);
        }

        window.display();
    }

    return 0;
}
