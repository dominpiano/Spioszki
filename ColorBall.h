#pragma once

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class ColorBall {
private:
	bool isSelected;
	bool isPermSelected;
	sf::Color ballColor;
	sf::Texture ballTexture;
	sf::Texture selectedBallTexture;
	sf::Sprite ballSprite;
	sf::Sprite selectedBallSprite;
public:
	ColorBall();
	void setColor(int color);
	void setPosition(sf::Vector2f pos);
	void setSelected(bool sel);
	void setPermSelect(bool permSel);
	bool getSelected();
	bool getPermSelect();
	bool contains(sf::Vector2i coords);
	void drawTo(sf::RenderWindow& window);
	void drawSelectedTo(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	sf::Color getColor();
};