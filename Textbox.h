#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>

#define BACKSPACE_KEY 8
#define TAB_KEY 9
#define ENTER_KEY 13

class Textbox{
private:
	sf::Text textbox = {};
	std::ostringstream text = {};
	sf::Color color = {};

	//Box for text
	sf::RectangleShape box;

	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;
	void inputLogic(int charTyped);
	void deleteLastChar();

public:
	Textbox();
	Textbox(int size, sf::Color color, bool sel);
	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f pos);
	void setLimit(bool hasLim);
	void setLimit(bool hasLim, int lim);
	void setSelected(bool sel);
	bool getSelected();
	void setColor(sf::Color col);
	std::string getText();
	void drawTo(sf::RenderWindow& window);
	void textTyped(sf::Event input);
	sf::Vector2f getBoxPosition();
	sf::Vector2f getBoxSize();
};