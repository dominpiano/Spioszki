#include "ColorBall.h"

ColorBall::ColorBall() {
	
}

ColorBall::~ColorBall(){
	
}

void ColorBall::setColor(int color){
	switch (color) {
	case 1:
		ballTexture.loadFromFile("resources/red_ball.png");
		selectedBallTexture.loadFromFile("resources/red_ball_selected.png");
		ballColor = sf::Color(186, 45, 11);
		break;
	case 2:
		ballTexture.loadFromFile("resources/light_blue_ball.png");
		selectedBallTexture.loadFromFile("resources/light_blue_ball_selected.png");
		ballColor = sf::Color(213, 242, 227);
		break;
	case 3:
		ballTexture.loadFromFile("resources/light_green_ball.png");
		selectedBallTexture.loadFromFile("resources/light_green_ball_selected.png");
		ballColor = sf::Color(115, 203, 159);
		break;
	case 4:
		ballTexture.loadFromFile("resources/green_ball.png");
		selectedBallTexture.loadFromFile("resources/green_ball_selected.png");
		ballColor = sf::Color(0, 62, 31);
		break;
	case 5:
		ballTexture.loadFromFile("resources/black_ball.png");
		selectedBallTexture.loadFromFile("resources/black_ball_selected.png");
		ballColor = sf::Color(1, 17, 10);
		break;
	}
	ballTexture.setSmooth(true);
	selectedBallTexture.setSmooth(true);
	ballSprite.setTexture(ballTexture);
	selectedBallSprite.setTexture(selectedBallTexture);
}

void ColorBall::setPosition(sf::Vector2f pos) {
	ballSprite.setPosition(pos);
	selectedBallSprite.setPosition(pos);
}

void ColorBall::setSelected(bool sel) {
	isSelected = sel;
}

void ColorBall::setPermSelect(bool permSel) {
	isPermSelected = permSel;
}

bool ColorBall::getSelected() {
	return isSelected;
}

bool ColorBall::getPermSelect() {
	return isPermSelected;
}

bool ColorBall::contains(sf::Vector2i coords) {
	if (ballSprite.getGlobalBounds().contains(coords.x, coords.y)) {
		return true;
	}
	else {
		return false;
	}
}

void ColorBall::drawTo(sf::RenderWindow& window) {
	window.draw(ballSprite);
}

void ColorBall::drawSelectedTo(sf::RenderWindow& window) {
	window.draw(selectedBallSprite);
}

sf::Vector2f ColorBall::getPosition() {
	return ballSprite.getPosition();
}

sf::Color ColorBall::getColor() {
	return ballColor;
}