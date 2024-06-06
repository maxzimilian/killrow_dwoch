#include "hero.h"
#include "platform.h"
#include "item.h"
#include "Menu.h"

static const float VIEW_HEIGHT = 300.0f; //ustawienie wielko�ci okna

void resizeView(sf::RenderWindow& window, sf::View& view) { //funkcja do skalowania rozmiaru okna
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
} 

//je�eli gra jest za trudna, to polecam zmieni� pozycj� pocz�tkow� gracza w jego klasie, �eby omin�� trudno�ci

int main() {
	

	// tworzenie okna i widoku
	sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_HEIGHT), "My window");
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	Menu menu(VIEW_HEIGHT, VIEW_HEIGHT);//menu gry

	bool menu_is_open = true;	//czy gra ma otwarte okno menu
	bool end = false;			//czy gra ju� si� sko�czy�a
	int points = 0;				//ilo�� zebranych punkt�w


	sf::Font font;

	if (!font.loadFromFile("Pixel.ttf")) { //[utopiafonts] 1999 free font, � 1999 utopiafonts. dale_thorpe@bssc.edu.au, https://www.1001fonts.com/pixel-font.html
		return 1;
	}


	sf::Text text;
	//tekst z ilo�ci� punkt�w gracza, kt�ra b�dzie pod��a� w lewym g�rnym rogu
	text.setFont(font);
	text.setString("Points : " + std::to_string(points));
	text.setCharacterSize(64);
	text.setScale(0.2, 0.2);
	text.setFillColor(sf::Color(100, 80, 160));
	text.setOutlineColor(sf::Color(73, 5, 55));
	text.setOutlineThickness(3);

	//napis ko�cowy gry
	sf::Text congrats;
	congrats.setFont(font);
	congrats.setString("Contratulations!!!\n You managed to escape\n and get " + std::to_string(points) + " points.");
	congrats.setCharacterSize(64);
	congrats.setScale(0.2, 0.2);
	congrats.setOrigin(sf::Vector2f(500, 250));
	congrats.setPosition(1000, 1000);
	congrats.setFillColor(sf::Color(200, 160, 20));
	congrats.setOutlineColor(sf::Color::Black);
	congrats.setOutlineThickness(3);


	//tekstury do wykorzystania dla gracza, platform oraz "item�w" do zbierania
	sf::Texture texture, planeTexture, tileTexture, sTileTexture, rockTexture, monsterTexture; //all textures are from https://s4m-ur4i.itch.io/huge-pixelart-asset-pack I've got acces on itch.io in one of bundles.

	if (!texture.loadFromFile("textures/hero.png")) {
		return 1;
	}

	if (!sTileTexture.loadFromFile("textures/sTile.png")) {
		return 1;
	}
	if (!tileTexture.loadFromFile("textures/tile.png")) {
		return 1;
	}
	if (!rockTexture.loadFromFile("textures/rock.png")) {
		return 1;
	}
	if (!monsterTexture.loadFromFile("textures/monsters.png")) {
		return 1;
	}
	if (!planeTexture.loadFromFile("textures/plane.png")) {
		return 1;
	}


	std::vector<std::vector<int>> allAnims;								//animacje bohatera
	allAnims.push_back(std::vector<int>{0, 1, 1, 2, 2, 1, 1, 0});		//idle animation frames
	allAnims.push_back(std::vector<int>{4, 4, 7, 6, 5, 5, 6, 7});		//run animation frames
	allAnims.push_back(std::vector<int>{3, 3, 3, 3, 3, 3, 3, 3});       //prepare to jump animation frame
	allAnims.push_back(std::vector<int>{4, 4, 4, 4, 4, 4, 4, 4});       //jump animation frame
	allAnims.push_back(std::vector<int>{8, 8, 8, 8, 8, 8, 8, 8});       //fallanimation frame

	Hero hero(&texture, sf::Vector2u(4, 3), 0.5f, allAnims, 100.0f, 60.0f);

	//animacja "item�w" / potwork�w
	std::vector<std::vector<int>> monsterAnims;
	monsterAnims.push_back(std::vector<int>{12, 13, 14, 13});

	//wektor wszystkich platform, kt�ry u�atwi potem wy�wietlanie i sprawdzanie kolizji
	std::vector<Platform> platforms;
	//tiles
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


	//small Tiles
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

	//rocks
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
	
	
	//wektor itemk�w / potwork�w
	std::vector<Item> items;
	items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(152.0f, 624.0f)));
	items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(200.0f, 348.0f)));
	items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(360.0f, 332.0f)));
	items.push_back(Item(&monsterTexture, sf::Vector2u(4, 48), 0.5f, monsterAnims, sf::Vector2f(16.0f, 16.0f), sf::Vector2f(120.0f, -10.0f)));

	//nasz cel ko�cowy, statek do ucieczki
	Platform plane(&planeTexture, sf::Vector2f(72.0f, 36.0f), sf::Vector2f(50.0f, -20.0f));

	float deltaTime = 0.0f; //czas pomi�dzy p�tlami

	sf::Clock clock;
	window.setFramerateLimit(120); //maksymalna ilo�� klatek na sekund�

	
	// run the program as long as the window is open
	while (window.isOpen()) {
		sf::Event event;
		// check all the window's events that were triggered since the last iteration of the loop
		while (window.pollEvent(event)) {
			// "close requested" event: we close the window
			
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				resizeView(window, view);
				break;
			case sf::Event::KeyReleased:
				if (menu_is_open) { //opcje menu
					switch (event.key.code)
					{

					case sf::Keyboard::W:
						menu.moveUp();
						break;

					case sf::Keyboard::S:
						menu.moveDown();
						break;
					case sf::Keyboard::Return://enter
						switch (menu.GetPressedItem())
						{									//po wybraniu opcji menu
						case 0:								//wraca do gry
							std::cout << "Play\n";			
							menu_is_open = !menu_is_open;
							menu.closeMenu();
							break;
						case 1:								//restartuje gr�, poprzez reset punkt�w, pozycji gracza, vektora item�w oraz zmienienie boola zako�czenia gry
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
						case 2:								//zamyka gr�
							std::cout << "Exit\n";
							window.close();
						default:
							break;
						}
					default:
						break;
					}
				}
				switch (event.key.code)						//escape �eby otworzy�/zamkn�� menu
				{
				case sf::Keyboard::Escape:
					menu_is_open = !menu_is_open;
					menu.closeMenu();
				default:
					break;
				}
			default:
				break;
			}
		}

		deltaTime = clock.restart().asSeconds();			//ile min�o od ostatniej p�tli

		//update all positions
		hero.Update(deltaTime, event, text);
		
		for (Item & item : items) {
			item.Update(deltaTime);
		}



		//check collisions

		Collider pCollision = hero.GetCollider();
		sf::Vector2f direction;

		for (Platform p : platforms) {
			if (p.Getcollider().CheckCollison(pCollision, direction, 1.0f)) {
				hero.OnCollision(direction);
			}
		}
		if (plane.Getcollider().CheckCollison(pCollision, direction, 1.0f)) {
			end = true;
		}


		for (unsigned int i = 0; i < items.size(); ++i) { //end of game - plane
			if (items[i].Getcollider().CheckCollison(pCollision, direction, 0.0f)) {
				hero.OnCollision(direction);
				items.erase(items.begin() + i);
				++points;
				text.setString("Points : " + std::to_string(points));
				congrats.setString("Contratulations!!!\n You managed to escape\n and get " + std::to_string(points) + " points.");
			}
		}

		if (end) {//end scene
			view.setCenter(1000, 1000);
			menu.setPosition(sf::Vector2f(1000, 1000), 300);
		}
		else {
			//set view on hero
			view.setCenter(hero.getPosition());
			menu.setPosition(hero.getPosition(), 300);
		}





		// clear the window with black color
		window.clear(sf::Color(80, 40, 120));
		window.setView(view);

		// draw everything here...
		for (Platform p : platforms) {
			p.Draw(window);
		}

		for (Item item : items) {
			item.Draw(window);
		}

		plane.Draw(window);
		hero.Draw(window);

		window.draw(text);
		window.draw(congrats);

		//menu draw
		if (menu_is_open) {
			window.clear(sf::Color(100, 60, 100));
			menu.draw(window);
		}

		// end the current frame
		window.display();
	}

	return 0;
}
