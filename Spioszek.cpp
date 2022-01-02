#include "Spioszek.h"

//Help functions
sf::Vector2f fineCoords(sf::Vector2i roughCoords) {
	return sf::Vector2f(roughCoords.x, roughCoords.y);
}
int getDir(sf::Vector2i v1, sf::Vector2i v2) {
	sf::Vector2i direction = sf::Vector2i(v2.x - v1.x, v2.y - v1.y);
	if (direction == sf::Vector2i(100, 0)) {
		return 1;
	}
	else if(direction == sf::Vector2i(100, 100)){
		return 2;
	}
	else if (direction == sf::Vector2i(0, 100)) {
		return 3;
	}
	else if (direction == sf::Vector2i(-100, 100)) {
		return 4;
	}
	else if (direction == sf::Vector2i(-100, 0)) {
		return 5;
	}
	else if (direction == sf::Vector2i(-100, -100)) {
		return 6;
	}
	else if (direction == sf::Vector2i(0, -100)) {
		return 7;
	}
	else if (direction == sf::Vector2i(100, -100)) {
		return 8;
	}
}
int getAngle(int dir) {
	switch (dir) {
	case 1:
		return 0;
		break;
	case 2:
		return 45;
		break;
	case 3:
		return 90;
		break;
	case 4:
		return 135;
		break;
	case 5:
		return 180;
		break;
	case 6:
		return 225;
		break;
	case 7:
		return 270;
		break;
	case 8:
		return 315;
		break;
	}
}

//Constructors and destructors
Spioszek::Spioszek() {

}
Spioszek::Spioszek(sf::Vector2i coords, sf::Color color) {
	headCoords = coords;
	spioszekColor = color;
}
Spioszek::Spioszek(sf::Vector2i head, sf::Vector2i first, sf::Vector2i second, sf::Vector2i direction) {
	headCoords = head;
	firstLineCoords = first;
	secondLineCoords = second;
	thirdLineCoords = second + direction;
}
Spioszek::~Spioszek() {

}

//Functions
sf::CircleShape Spioszek::drawHead() {
	head.setOrigin(sf::Vector2f(headRadius, headRadius));
	head.setPosition(fineCoords(headCoords));
	head.setFillColor(sf::Color(0, 0, 0, 0));
	head.setOutlineColor(spioszekColor);
	head.setOutlineThickness(2.f);
	head.setRadius(headRadius);
	return head;
}

sf::RectangleShape Spioszek::drawFirstLine(sf::Vector2i firstCoords) {

	firstLineCoords = firstCoords;

	//First some style
	firstLine.setFillColor(spioszekColor);
	firstLine.setOrigin(-15.f, lineThic / 2.f);
	if (getDir(headCoords, firstLineCoords) % 2 == 0) {
		lineLenght = 100.f * sqrt(2.f) - 15.f;
	}
	else {
		lineLenght = 85.f;
	}

	lineSize = { lineLenght, lineThic };
	firstLine.setSize(lineSize);
	firstLine.setPosition(fineCoords(headCoords));
	firstLine.setRotation(getAngle(getDir(headCoords, firstLineCoords)));
	return firstLine;
}

sf::RectangleShape Spioszek::drawSecondLine(sf::Vector2i secCoords) {

	secondLineCoords = secCoords;

	//First some style
	secondLine.setFillColor(spioszekColor);
	secondLine.setOrigin(0, lineThic / 2.f);
	if (getDir(firstLineCoords, secondLineCoords) % 2 == 0) {
		lineLenght = 100.f * sqrt(2.f);
	}
	else {
		lineLenght = 100.f;
	}

	lineSize = { lineLenght, lineThic };
	secondLine.setSize(lineSize);
	secondLine.setPosition(fineCoords(firstLineCoords));
	secondLine.setRotation(getAngle(getDir(firstLineCoords, secondLineCoords)));
	return secondLine;
}

sf::RectangleShape Spioszek::drawThirdLine(sf::Vector2i thirdCoords) {

	thirdLineCoords = thirdCoords;

	//First some style
	thirdLine.setFillColor(spioszekColor);
	thirdLine.setOrigin(0, lineThic / 2.f);
	if (getDir(secondLineCoords, thirdLineCoords) % 2 == 0) {
		lineLenght = 100.f * sqrt(2.f);
	}
	else {
		lineLenght = 100.f;
	}

	lineSize = { lineLenght, lineThic };
	thirdLine.setSize(lineSize);
	thirdLine.setPosition(fineCoords(secondLineCoords));
	thirdLine.setRotation(getAngle(getDir(secondLineCoords, thirdLineCoords)));

	return thirdLine;
}
