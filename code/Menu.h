#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 3  //definiowanie ile jest elementów w menu
class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void moveUp();
	void moveDown();
	void closeMenu();
	int GetPressedItem() { return selectedItemIndex; }
	void setPosition(sf::Vector2f pos, float size);

private:
	int selectedItemIndex;
	sf::Color marked = sf::Color::Cyan; //kolor zaznaczonego elementu
	sf::Color unmarked = sf::Color(50, 50, 50); //kolor niezaznaczonego elementru
	sf::Font font; //czcionka
	sf::Text menu[MAX_NUMBER_OF_ITEMS]; //tablica tekstów menu
};

