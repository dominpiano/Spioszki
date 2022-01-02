#include "Button.h"

Button::Button() {

}

void Button::setTexture(std::string path) {
	texture.loadFromFile(path);
	buttonSprite.setTexture(texture);
}

void Button::setPosition(sf::Vector2f pos) {
	buttonSprite.setPosition(pos);
}

sf::Vector2f Button::getPosition() {
	return buttonSprite.getPosition();
}

sf::Vector2i Button::getSize() {
	return sf::Vector2i(buttonSprite.getGlobalBounds().width, buttonSprite.getGlobalBounds().height);
}

void Button::drawTo(sf::RenderWindow& window) {
	window.draw(buttonSprite);
}