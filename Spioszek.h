#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Spioszek{
private:
	float headRadius = 15.f;
	sf::Vector2f lineSize;
	float lineLenght;
	float lineThic = 4.f;
	int lineAngle;
	int getDir(sf::Vector2i v1, sf::Vector2i v2);
public:
	sf::Vector2i headCoords, firstLineCoords, secondLineCoords, thirdLineCoords;
	sf::CircleShape head;
	sf::Color spioszekColor;
	sf::RectangleShape firstLine, secondLine, thirdLine;

	Spioszek();
	Spioszek(sf::Vector2i coords, sf::Color color);
	Spioszek(sf::Vector2i head, sf::Vector2i first, sf::Vector2i second, sf::Vector2i direction);
	~Spioszek();

	sf::CircleShape drawHead();
	sf::RectangleShape drawFirstLine(sf::Vector2i firstCoords);
	sf::RectangleShape drawSecondLine(sf::Vector2i secCoords);
	sf::RectangleShape drawThirdLine(sf::Vector2i thirdCoords);
};

