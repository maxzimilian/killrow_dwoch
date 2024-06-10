#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 4 // Increase the number of items
#define POST_WIN_ITEMS 2 // Number of items in the post-win menu

class Menu {
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    void closeMenu();
    int GetPressedItem() { return selectedItemIndex; }
    void setPosition(sf::Vector2f pos, float size);

    void drawPostWinMenu(sf::RenderWindow &window); // Draw the post-win menu
    void moveUpPostWinMenu();
    void moveDownPostWinMenu();
    int GetPressedPostWinItem() { return selectedPostWinIndex; }

private:
    int selectedItemIndex;
    int selectedPostWinIndex; // Selected item index for the post-win menu
    sf::Color marked = sf::Color::Cyan; // Kolor zaznaczonego elementu
    sf::Color unmarked = sf::Color(50, 50, 50); // Kolor niezaznaczonego elementu
    sf::Font font; // Czcionka
    sf::Text menu[MAX_NUMBER_OF_ITEMS]; // Tablica tekstów menu
    sf::Text postWinMenu[POST_WIN_ITEMS]; // Post-win menu texts
};
