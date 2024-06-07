#include "Menu.h"
Menu::Menu(float width, float height) {
	if (!font.loadFromFile("Pixel.ttf")) { //[utopiafonts] 1999 free font, 1999 utopiafonts. dale_thorpe@bssc.edu.au, https://www.1001fonts.com/pixel-font.html
		std::cout << "Could not load font of menu.\n";
	}
	//ustawienie dla kazdego napisu po kolei czcionki, napisu, rozmiaru, oraz jego pozycji
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
	menu[2].setString("Exit");
	menu[2].setCharacterSize(64);
	menu[2].setScale(0.4, 0.4);
	menu[2].setPosition(sf::Vector2f(width / 10, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0; //zawsze przy otwieraniu menu chcemy zeby wyswietlona byla 0. pozycja
}

Menu::~Menu() {

}

void Menu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

void Menu::moveUp() { //poruszanie si� do g�ry menu
	if (selectedItemIndex == 0) {
		menu[selectedItemIndex].setFillColor(unmarked);
		selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		menu[selectedItemIndex].setFillColor(marked);
	}
	else {
		menu[selectedItemIndex].setFillColor(unmarked);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(marked);
	}
}
void Menu::moveDown() { //poruszanie si� w d� menu
	if (selectedItemIndex == MAX_NUMBER_OF_ITEMS - 1) {
		menu[selectedItemIndex].setFillColor(unmarked);
		selectedItemIndex = 0;
		menu[selectedItemIndex].setFillColor(marked);
	}
	else {
		menu[selectedItemIndex].setFillColor(unmarked);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(marked);
	}
}

void Menu::closeMenu() { //zamykanie menu
	menu[selectedItemIndex].setFillColor(unmarked);
	selectedItemIndex = 0;
	menu[selectedItemIndex].setFillColor(marked);
}

void Menu::setPosition(sf::Vector2f pos, float size) { //ustawianie pozycji, �eby pod��a�a za graczem, poniewa� ca�y widok pod��a za graczem

	menu[0].setPosition(sf::Vector2f(pos.x - size/2 + size / 10, pos.y - size / 2 + size / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setPosition(sf::Vector2f(pos.x - size / 2 + size/ 10, pos.y - size / 2 +size / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setPosition(sf::Vector2f(pos.x - size / 2 + size / 10, pos.y - size / 2 + size/ (MAX_NUMBER_OF_ITEMS + 1) * 3));
}