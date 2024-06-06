#include "hero.h"

//konstruktor z przekazaniem animacji i ustawieniem podstawowych parametrow
Hero::Hero(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, std::vector<std::vector<int>> allAnims, float speed, float jumpHeight) : animation(texture, imageCount, switchTime, allAnims) {
	this->speed = speed;
	this->anim = 0;
	this->jumpHeight = jumpHeight;
	faceLeft = true;
	canJump = false;
	jump = 0;

	body.setSize(sf::Vector2f(13.0f, 20.f));
	body.setPosition(startPos);
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.0f);
}

void Hero::restart() {
	body.setPosition(startPos);  //reset pozycji
}

void Hero::Update(float deltaTime, sf::Event event, sf::Text& text) {
	if (canJump) { //jeżeli jest na platformie, to może przygotowac sie do skoku i wyskoczyc, albo chodzic prawo-lewo
		velocity.x = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {//przygotowanie sie do skoku
			anim = 2;
			jump += deltaTime;
			jump = std::min(std::max(jump, 0.0f), 1.0f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				faceLeft = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				faceLeft = false;
			}
		}
		else {//chodzenie
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				velocity.x -= speed / 4.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				velocity.x += speed / 4.0f;
			}
			if (velocity.x == 0.0f) {
				anim = 0;
			}
			else {
				anim = 1;

				if (velocity.x > 0.0f) {
					faceLeft = false;
				}
				else {
					faceLeft = true;
				}
			}
		}
		//pow zwolnieniu przycisku spacji, skok
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
			canJump = false;
			velocity.y = -sqrtf(2.0f * 98.1f * jumpHeight) * jump;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				velocity.x = (-speed / 4.0)*jump;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				velocity.x = (speed / 4.0)*jump;
			}

		}
	}
	else { //jezeli jest w powietrzu, to w zaleznosci czy spada czy wznosi sie, dajemy odpowiednia animacje
		jump = 0;
		if (velocity.y > 0.0f) {
			anim = 3;
		}
		else if (velocity.y < 0.0f) {
			anim = 4;
		}
	}

	velocity.y += 98.1f * deltaTime; //grawitacja

	animation.Update(anim, deltaTime, faceLeft); //aktualizowanie animacji

	body.setTextureRect(animation.uvRect); //ustawianie odpowiedniej klatki tekstury
	body.move(velocity * deltaTime); //poruszanie bohatera
	canJump = false; 
	text.setPosition(sf::Vector2f(body.getPosition().x - 148.0f, body.getPosition().y - 150.0f)); //tekst punktow
}

void Hero::Draw(sf::RenderWindow& window) {
	window.draw(body);
}


void Hero::OnCollision(sf::Vector2f direction) {
	if (direction.x != 0.0f) {
		//kolizja po bokach
		velocity.x *= -1.0f;
	}
	if (direction.y < 0.0f) {
		//kolizja od dolu
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f) {
		//kolizja z gory
		velocity.y = 0.0f;
	}
}


sf::Vector2f Hero::getPosition() {
	return body.getPosition();
}
