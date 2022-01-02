#pragma once

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class ColorBall {
private:
	sf::Texture ballTexture;
	sf::Sprite ballSprite;
public:
	ColorBall();
	void setColor(int color);
	void setPosition(sf::Vector2f pos);
	void drawTo(sf::RenderWindow& window);
	sf::Vector2f getPosition();
};

