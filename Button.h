#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>

class Button{
public:
	sf::Texture texture;
	sf::Sprite buttonSprite;

	Button();
	virtual ~Button();
	void setTexture(std::string path);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::Vector2i getSize();
	void drawTo(sf::RenderWindow& window);
};