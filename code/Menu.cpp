#include "Menu.h"

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("Pixel.ttf")) { // Wczytaj czcionkę
        std::cout << "Could not load font of menu.\n";
    }

    menu[0].setFont(font);
    menu[0].setFillColor(marked);
    menu[0].setString("Play");
    menu[0].setCharacterSize(64);
    menu[0].setScale(0.4, 0.4);
    menu[0].setPosition(sf::Vector2f(width / 10, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(unmarked);
    menu[1].setString("Restart");
    menu[1].setCharacterSize(64);
    menu[1].setScale(0.4, 0.4);
    menu[1].setPosition(sf::Vector2f(width / 10, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(unmarked);
    menu[2].setString("Leaderboard");
    menu[2].setCharacterSize(64);
    menu[2].setScale(0.4, 0.4);
    menu[2].setPosition(sf::Vector2f(width / 10, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    menu[3].setFont(font);
    menu[3].setFillColor(unmarked);
    menu[3].setString("Exit");
    menu[3].setCharacterSize(64);
    menu[3].setScale(0.4, 0.4);
    menu[3].setPosition(sf::Vector2f(width / 10, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

    selectedItemIndex = 0; // Zawsze przy otwieraniu menu chcemy, żeby wyświetlona była 0. pozycja
    selectedPostWinIndex = 0; // Initial selected index for the post-win menu

    // Initialize the post-win menu
    postWinMenu[0].setFont(font);
    postWinMenu[0].setFillColor(marked);
    postWinMenu[0].setString("Save");
    postWinMenu[0].setCharacterSize(64);
    postWinMenu[0].setScale(0.4, 0.4);
    postWinMenu[0].setPosition(sf::Vector2f(width / 10, height / (POST_WIN_ITEMS + 1) * 1));

    postWinMenu[1].setFont(font);
    postWinMenu[1].setFillColor(unmarked);
    postWinMenu[1].setString("Exit to Menu");
    postWinMenu[1].setCharacterSize(64);
    postWinMenu[1].setScale(0.4, 0.4);
    postWinMenu[1].setPosition(sf::Vector2f(width / 10, height / (POST_WIN_ITEMS + 1) * 2));
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow &window) {
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]); // Rysuj elementy menu
    }
}

void Menu::drawPostWinMenu(sf::RenderWindow &window) {
    for (int i = 0; i < POST_WIN_ITEMS; i++) {
        window.draw(postWinMenu[i]); // Rysuj elementy menu po wygranej
    }
}

void Menu::moveUp() { // Poruszanie się w górę menu
    if (selectedItemIndex == 0) {
        menu[selectedItemIndex].setFillColor(unmarked);
        selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
        menu[selectedItemIndex].setFillColor(marked);
    } else {
        menu[selectedItemIndex].setFillColor(unmarked);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(marked);
    }
}

void Menu::moveDown() { // Poruszanie się w dół menu
    if (selectedItemIndex == MAX_NUMBER_OF_ITEMS - 1) {
        menu[selectedItemIndex].setFillColor(unmarked);
        selectedItemIndex = 0;
        menu[selectedItemIndex].setFillColor(marked);
    } else {
        menu[selectedItemIndex].setFillColor(unmarked);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(marked);
    }
}

void Menu::moveUpPostWinMenu() { // Poruszanie się w górę post-win menu
    if (selectedPostWinIndex == 0) {
        postWinMenu[selectedPostWinIndex].setFillColor(unmarked);
        selectedPostWinIndex = POST_WIN_ITEMS - 1;
        postWinMenu[selectedPostWinIndex].setFillColor(marked);
    } else {
        postWinMenu[selectedPostWinIndex].setFillColor(unmarked);
        selectedPostWinIndex--;
        postWinMenu[selectedPostWinIndex].setFillColor(marked);
    }
}

void Menu::moveDownPostWinMenu() { // Poruszanie się w dół post-win menu
    if (selectedPostWinIndex == POST_WIN_ITEMS - 1) {
        postWinMenu[selectedPostWinIndex].setFillColor(unmarked);
        selectedPostWinIndex = 0;
        postWinMenu[selectedPostWinIndex].setFillColor(marked);
    } else {
        postWinMenu[selectedPostWinIndex].setFillColor(unmarked);
        selectedPostWinIndex++;
        postWinMenu[selectedPostWinIndex].setFillColor(marked);
    }
}

void Menu::closeMenu() { // Zamykanie menu
    menu[selectedItemIndex].setFillColor(unmarked);
    selectedItemIndex = 0;
    menu[selectedItemIndex].setFillColor(marked);
}

void Menu::setPosition(sf::Vector2f pos, float size) { // Ustawianie pozycji, żeby podążała za graczem, ponieważ cały widok podąża za graczem
    menu[0].setPosition(sf::Vector2f(pos.x - size / 2 + size / 10, pos.y - size / 2 + size / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    menu[1].setPosition(sf::Vector2f(pos.x - size / 2 + size / 10, pos.y - size / 2 + size / (MAX_NUMBER_OF_ITEMS + 1) * 2));
    menu[2].setPosition(sf::Vector2f(pos.x - size / 2 + size / 10, pos.y - size / 2 + size / (MAX_NUMBER_OF_ITEMS + 1) * 3));
    menu[3].setPosition(sf::Vector2f(pos.x - size / 2 + size / 10, pos.y - size / 2 + size / (MAX_NUMBER_OF_ITEMS + 1) * 4));
}
