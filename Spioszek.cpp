#include "Spioszek.h"

//Help functions
sf::Vector2f fineCoords(sf::Vector2i roughCoords) {
	return sf::Vector2f(roughCoords.x, roughCoords.y);
}
int Spioszek::getDir(sf::Vector2i v1, sf::Vector2i v2) {
	sf::Vector2i direction = sf::Vector2i(v2.x - v1.x, v2.y - v1.y);
	if (direction == sf::Vector2i(100, 0)) {
		lineAngle = 0;
		return 1;
	}
	else if(direction == sf::Vector2i(100, 100)){
		lineAngle = 45;
		return 2;
	}
	else if (direction == sf::Vector2i(0, 100)) {
		lineAngle = 90;
		return 3;
	}
	else if (direction == sf::Vector2i(-100, 100)) {
		lineAngle = 135;
		return 4;
	}
	else if (direction == sf::Vector2i(-100, 0)) {
		lineAngle = 180;
		return 5;
	}
	else if (direction == sf::Vector2i(-100, -100)) {
		lineAngle = 225;
		return 6;
	}
	else if (direction == sf::Vector2i(0, -100)) {
		lineAngle = 270;
		return 7;
	}
	else if (direction == sf::Vector2i(100, -100)) {
		lineAngle = 315;
		return 8;
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

	//At this moment there was some fucked up math but the 30th of December 2021 there was a bug with Sourcetree (git GUI)
	//and all my files EXCEPT the class with the most lines of code (Game.cpp) have been PERMANENTLY DELETED and so i had to rewrite them.
	//I did it in 4 hours, drunk as fuck.
	//There is no fucked up math cause I was too drunk to do it again and so i just set the origin and worried no more.
	//Thanks for appreciation of my story of this project.
	//Hope you have a good day!

	lineSize = { lineLenght, lineThic };
	firstLine.setSize(lineSize);
	firstLine.setPosition(fineCoords(headCoords));
	firstLine.setRotation(lineAngle);
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
	secondLine.setRotation(lineAngle);
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
	thirdLine.setRotation(lineAngle);

	return thirdLine;
}