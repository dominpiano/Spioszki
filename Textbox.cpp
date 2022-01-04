#include "Textbox.h"

//Constructors
Textbox::Textbox() {

}
Textbox::Textbox(int size, sf::Color color, bool sel) {
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	box.setFillColor(sf::Color(200, 200, 200));
	box.setOutlineColor(color);
	box.setOutlineThickness(1.5);
	box.setSize(sf::Vector2f(300, 70));
	isSelected = sel;
	if (sel) {
		textbox.setString("_");
	}
	else {
		textbox.setString("");
	}
}

Textbox::~Textbox(){

}

//Public functions
void Textbox::setFont(sf::Font& font) {
	textbox.setFont(font);
}
void Textbox::setPosition(sf::Vector2f pos) {
	textbox.setPosition(pos);
	box.setPosition(sf::Vector2f(pos.x - 10, pos.y - 5));
}
void Textbox::setLimit(bool hasLim) {
	hasLimit = hasLim;
}
void Textbox::setLimit(bool hasLim, int lim) {
	hasLimit = hasLim;
	limit = lim;
}
void Textbox::setSelected(bool sel) {
	isSelected = sel;
	if (!sel) {
		if (color == sf::Color(213, 242, 227) || color == sf::Color(115, 203, 159)) {
			box.setFillColor(sf::Color(50, 50, 50));
		}
		else {
			box.setFillColor(sf::Color(200, 200, 200));
		}
		std::string str = text.str();
		std::string newStr = "";
		for (int i = 0; i < str.length(); i++) {
			newStr += str[i];
		}
		textbox.setString(newStr);
	}
	else {
		if (color == sf::Color(213, 242, 227) || color == sf::Color(115, 203, 159)) {
			box.setFillColor(sf::Color(80, 80, 80));
		}
		else {
			box.setFillColor(sf::Color(230, 230, 230));
		}
		textbox.setString(text.str() + "_");
	}
}
bool Textbox::getSelected() {
	return isSelected;
}

void Textbox::setColor(sf::Color col) {
	color = col;
	box.setOutlineColor(color);
	textbox.setFillColor(color);
	if (color == sf::Color(213, 242, 227) || color == sf::Color(115, 203, 159)) {
		box.setFillColor(sf::Color(50, 50, 50));
	}
	else {
		box.setFillColor(sf::Color(200, 200, 200));
	}
}
std::string Textbox::getText() {
	return text.str();
}
void Textbox::drawTo(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(textbox);
}
void Textbox::textTyped(sf::Event input) {
	if (isSelected) {
		int charTyped = input.text.unicode;
		if ((charTyped >= 48 && charTyped <= 57) || (charTyped >= 65 && charTyped <= 90) || (charTyped >= 97 && charTyped <= 122) 
			|| charTyped == BACKSPACE_KEY) {
			if (hasLimit) {
				if (text.str().length() <= limit) {
					inputLogic(charTyped);
				}
				else if (text.str().length() > limit && charTyped == BACKSPACE_KEY) {
					deleteLastChar();
				}
			}
			else {
				inputLogic(charTyped);
			}
		}
		else if (charTyped == ENTER_KEY) {
			setSelected(false);
		}
	}
}
sf::Vector2f Textbox::getBoxPosition() {
	return box.getPosition();
}
sf::Vector2f Textbox::getBoxSize() {
	return box.getSize();
}


//Private functions
void Textbox::inputLogic(int charTyped){
	if (charTyped != BACKSPACE_KEY && charTyped != TAB_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if(charTyped == BACKSPACE_KEY){
		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	textbox.setString(text.str() + "_");
}

void Textbox::deleteLastChar(){
	std::string str = text.str();
	std::string newStr = "";
	for (int i = 0; i < str.length() - 1; i++) {
		newStr += str[i];
	}
	text.str("");
	text << newStr;

	textbox.setString(text.str());
}