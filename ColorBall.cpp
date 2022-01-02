#include "ColorBall.h"

ColorBall::ColorBall() {
	
}

void ColorBall::setColor(int color){
	switch (color) {
	case 1:
		ballTexture.loadFromFile("red_ball.png");
		break;
	case 2:
		ballTexture.loadFromFile("light_blue_ball.png");
		break;
	case 3:
		ballTexture.loadFromFile("light_green_ball.png");
		break;
	case 4:
		ballTexture.loadFromFile("green_ball.png");
		break;
	case 5:
		ballTexture.loadFromFile("black_ball.png");
		break;
	}
	ballTexture.setSmooth(true);
	ballSprite.setTexture(ballTexture);
}

void ColorBall::setPosition(sf::Vector2f pos) {
	ballSprite.setPosition(pos);
}

void ColorBall::drawTo(sf::RenderWindow& window) {
	window.draw(ballSprite);
}

sf::Vector2f ColorBall::getPosition() {
	return ballSprite.getPosition();
}