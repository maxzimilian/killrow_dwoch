#include "hero.h"
#include "platform.h"
#include "item.h"
#include "Menu.h"
#include "lava.h"

static const float VIEW_HEIGHT = 300.0f; // ustawienie wielkości okna

void resizeView(sf::RenderWindow& window, sf::View& view) { // funkcja do skalowania rozmiaru okna
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "My window");
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    Menu menu(VIEW_HEIGHT, VIEW_HEIGHT); // menu gry

    bool menu_is_open = true;    // czy gra ma otwarte okno menu
    bool end = false;            // czy gra już się skończyła
    int points = 0;              // ilość zebranych punktów

    sf::Font font;
    if (!font.loadFromFile("Pixel.ttf")) { //[utopiafonts] 1999 free font, © 1999 utopiafonts. dale_thorpe@bssc.edu.au, https://www.1001fonts.com/pixel-font.html
        return 1;
    }

    sf::Text text;
    // tekst z ilością punktów gracza, która będzie podążać w lewym górnym rogu
    text.setFont(font);
    text.setString("Points : " + std::to_string(points));
    text.setCharacterSize(64);
    text.setScale(0.2, 0.2);
    text.setFillColor(sf::Color(100, 80, 160));
    text.setOutlineColor(sf::Color(73, 5, 55));
    text.setOutlineThickness(3);

    // napis końcowy gry
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

    sf::Text lavaWarning;
    // tekst ostrzeżenia przed lawą
    lavaWarning.setFont(font);
    lavaWarning.setString("Lava is coming!");
    lavaWarning.setCharacterSize(64);  
    lavaWarning.setScale(0.3, 0.3);    
    lavaWarning.setFillColor(sf::Color::Red);
    lavaWarning.setOutlineColor(sf::Color::Black);
    lavaWarning.setOutlineThickness(3);

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

    std::vector<std::vector<int>> allAnims;
    allAnims.push_back(std::vector<int>{0, 1, 1, 2, 2, 1, 1, 0});       // bezczynność
    allAnims.push_back(std::vector<int>{4, 4, 7, 6, 5, 5, 6, 7});       // bieg
    allAnims.push_back(std::vector<int>{3, 3, 3, 3, 3, 3, 3, 3});       // przygotowanie do skoku
    allAnims.push_back(std::vector<int>{4, 4, 4, 4, 4, 4, 4, 4});       // skok
    allAnims.push_back(std::vector<int>{8, 8, 8, 8, 8, 8, 8, 8});       // upadek

    Hero hero(&texture, sf::Vector2u(4, 3), 0.5f, allAnims, 100.0f, 60.0f);

    std::vector<std::vector<int>> monsterAnims;
    monsterAnims.push_back(std::vector<int>{12, 13, 14, 13});

    std::vector<Platform> platforms;
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(512.0f, 160.0f), sf::Vector2f(256.0f, 800.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(144.0f, 800.0f), sf::Vector2f(72.0f, 400.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(144.0f, 800.0f), sf::Vector2f(440.0f, 400.0f)));
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
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(160.0f, 32.0f), sf::Vector2f(256.0f, 32.0f)));
    platforms.push_back(Platform(&tileTexture, sf::Vector2f(128.0f, 128.0f), sf::Vector2f(448.0f, -64.0f)));

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

    std::vector<Item> items;
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(152.0f, 624.0f)));
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(200.0f, 348.0f)));
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(360.0f, 332.0f)));
    items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(120.0f, -10.0f)));

    Platform plane(&planeTexture, sf::Vector2f(72.0f, 36.0f), sf::Vector2f(50.0f, -20.0f));

    Lava lava(&lavaTexture, sf::Vector2f(600.0f, 20.0f), sf::Vector2f(180.0f, 800.0f)); // Początkowa pozycja lawy bliżej startowej pozycji gracza

    float deltaTime = 0.0f; // czas pomiędzy pętlami
    sf::Clock clock;
    window.setFramerateLimit(120); // maksymalna ilość klatek na sekundę

    float idleTime = 0.0f; // czas bez ruchu gracza
    sf::Vector2f previousPosition = hero.getPosition();
    bool showLavaWarning = false; // flaga do kontrolowania wyświetlania ostrzeżenia

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
                        switch (menu.GetPressedItem()) { // po wybraniu opcji menu
                        case 0: // wraca do gry
                            menu_is_open = !menu_is_open;
                            menu.closeMenu();
                            break;
                        case 1: // restartuje grę, poprzez reset punktów, pozycji gracza, vektora itemów oraz zmienienie boola zakończenia gry
                            points = 0;
                            text.setString("Points : " + std::to_string(points));
                            items.clear();
                            items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(152.0f, 624.0f)));
                            items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(200.0f, 348.0f)));
                            items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(360.0f, 332.0f)));
                            items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(120.0f, -10.0f)));
                            hero.restart();
                            menu.closeMenu();
                            end = false;
                            menu_is_open = false;
                            break;
                        case 2: // zamyka okno
                            window.close();
                            break;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    menu_is_open = !menu_is_open;
                    menu.closeMenu();
                }
                break;
            }
        }

        deltaTime = clock.restart().asSeconds();
        sf::Vector2f currentPosition = hero.getPosition();

        if (currentPosition == previousPosition) { // sprawdzanie czy gracz jest w tej samej pozycji
            idleTime += deltaTime;
            if (idleTime >= 2.0f && idleTime < 3.0f) {
                showLavaWarning = true;
            }
            if (idleTime >= 3.0f) { // po 3 sekundach bez ruchu gracza lawa podnosi się
                lava.IncreaseLevel(10.0f); // Przykładowa prędkość podnoszenia lawy
                showLavaWarning = false; // przestaje wyświetlać ostrzeżenie
            }
        } else { // jeżeli gracz się ruszył, resetuje się czas bez ruchu
            idleTime = 0.0f;
            lava.IncreaseLevel(0.0f);
            showLavaWarning = false;
        }

        previousPosition = currentPosition;

        hero.Update(deltaTime, event, text);
        for (Item& item : items) {
            item.Update(deltaTime);
        }

        lava.Update(deltaTime);

        Collider pCollision = hero.GetCollider();
        sf::Vector2f direction;

        for (Platform& p : platforms) {
            if (p.Getcollider().CheckCollison(pCollision, direction, 1.0f)) {
                hero.OnCollision(direction);
            }
        }
        if (plane.Getcollider().CheckCollison(pCollision, direction, 1.0f)) { // jeżeli gracz dotarł do samolotu kończy grę
            end = true;
        }
        for (unsigned int i = 0; i < items.size(); ++i) { // zebrane przedmioty znikają
            if (items[i].Getcollider().CheckCollison(pCollision, direction, 0.0f)) {
                hero.OnCollision(direction);
                items.erase(items.begin() + i);
                ++points;
                text.setString("Points : " + std::to_string(points));
                congrats.setString("Congratulations!!!\n You managed to escape\n and get " + std::to_string(points) + " points.");
            }
        }

        if (end) { // po zakończeniu gry ustawia kamerę na 1000, 1000, gdzie jest napis końcowy
            view.setCenter(1000, 1000);
            menu.setPosition(sf::Vector2f(1000, 1000), 300);
        } else { // kamera podąża za graczem
            view.setCenter(hero.getPosition());
            menu.setPosition(hero.getPosition(), 300);
        }

        window.clear(sf::Color(80, 40, 120)); // kolor tła gry
        window.setView(view);

        for (Platform& p : platforms) {
            p.Draw(window);
        }

        for (Item& item : items) {
            item.Draw(window);
        }

        plane.Draw(window);
        hero.Draw(window);
        lava.Draw(window);

        window.draw(text);
        window.draw(congrats);

        if (showLavaWarning) {
            lavaWarning.setOrigin(lavaWarning.getLocalBounds().width / 2.0f, lavaWarning.getLocalBounds().height / 2.0f);
            lavaWarning.setPosition(view.getCenter());
            window.draw(lavaWarning);
        }

        if (menu_is_open) {
            window.clear(sf::Color(100, 60, 100));
            menu.draw(window);
        }

        window.display();
    }

    return 0;
}
