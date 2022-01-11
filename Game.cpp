#include "Game.h"
#include <map>

//GLOBAL NOTE
//I HAD TO ADD EVERYWHERE "" TO MAKE IT RESPONSIVE TO EVERY SCREEN

#define right sf::Vector2i(100,0)
#define rightdown sf::Vector2i(100,100)
#define down sf::Vector2i(0,100)
#define leftdown sf::Vector2i(-100,100)
#define left sf::Vector2i(-100,0)
#define leftup sf::Vector2i(-100,-100)
#define up sf::Vector2i(0,-100)
#define rightup sf::Vector2i(100,-100)

//Overload some operators
std::ostream& operator<<(std::ostream& out, const sf::Vector2i v) {
	//out << "[" << (v.x - 100) / 100 + 1 << ", " << (v.y - 200) / 100 + 1 << "]";
	out << "[" << (v.x) << ", " << (v.y - 100) << "]";
	//out << "[" << v.x << ", " << v.y << "]";
	return out;
}
std::ostream& operator<<(std::ostream& out, const sf::Vector2f v) {
	//out << "[" << (v.x - 100) / 100 + 1 << ", " << (v.y - 200) / 100 + 1 << "]";
	out << "[" << (v.x) << ", " << (v.y - 100) << "]";
	//out << "[" << v.x << ", " << v.y << "]";
	return out;
}
sf::Vector2i operator+(sf::Vector2i v1, sf::Vector2i v2) {
	return sf::Vector2i(v1.x + v2.x, v1.y + v2.y);
}

const std::vector<sf::Vector2i> directions = { right, rightdown, down, leftdown, left, leftup, up, rightup };

//Global help variables
bool isDrawing = false;
int clickCount = 0;
bool isMouseClicked = false;
float roundX, roundY;
float tempRad = 15.f; //Radius of the circle
std::vector<sf::Vector2i> coordinatesForHead; //List of coordinates for Heads
std::vector<sf::Vector2i> coordinatesForLine; //List of coordinates for Heads
std::vector<sf::Vector2i> coordinatesForWinningCheck; //List of coordinates for winning but only for starting point
std::vector<sf::Vector2i> coordinatesForWinningCheckLine; //List of coordinates for winning but for lines not heads

//Help variables ONLY FOR CHECKING IF GIVEN SPIOSZEK ISN'T ON THE BOARD
sf::Vector2i tempPosition;
int firstLineCode = 0;
int secondLineCode = 0;
int thirdLineCode = 0;
Vector shape; //This is vector of 3 ints for one shape definition
std::vector<Vector> existingShapes; //This is vector for storing shapes

//Help function ONLY FOR CHECKING IF GIVEN SPIOSZEK ISN'T ON THE BOARD
int Game::determineLineCode(sf::Vector2i a, sf::Vector2i b) {
	sf::Vector2i determineDirection = b - a;

	switch (determineDirection.x) {
	case 100:
		switch (determineDirection.y) {
		case 0:
			return 1;
			break;
		case -100:
			return 8;
			break;
		case 100:
			return 2;
			break;
		}
		break;
	case -100:
		switch (determineDirection.y) {
		case 0:
			return 5;
			break;
		case -100:
			return 6;
			break;
		case 100:
			return 4;
			break;
		}
		break;
	case 0:
		switch (determineDirection.y) {
		case -100:
			return 7;
			break;
		case 100:
			return 3;
			break;
		}
	}


}
Vector Game::createShape(int a, int b, int c) {
	return Vector(a, b, c);
}
void Game::addToList(Vector shapeToAdd) {

	//First shapes
	existingShapes.push_back(shapeToAdd);
	existingShapes.push_back(shapeToAdd + 2);
	existingShapes.push_back(shapeToAdd + 4);
	existingShapes.push_back(shapeToAdd + 6);

	//Mirrored shapes
	existingShapes.push_back(shapeToAdd.mirrorVec());
	existingShapes.push_back(shapeToAdd.mirrorVec() + 2);
	existingShapes.push_back(shapeToAdd.mirrorVec() + 4);
	existingShapes.push_back(shapeToAdd.mirrorVec() + 6);
}
bool Game::checkIfExists(Vector shape_arg) {
	for (auto& item : existingShapes) {
		if (item == shape_arg) {
			return true;
			break;
		}
	}
	return false;
}

//Find in vector function
bool findInAvailablePoints(sf::Vector2i element) {
	if (std::find(coordinatesForLine.begin(), coordinatesForLine.end(), element) != coordinatesForLine.end()) {
		return true;
	}
	else {
		return false;
	}
}
bool findInAvailableDirections(sf::Vector2i element) {
	if (std::find(directions.begin(), directions.end(), element) != directions.end()) {
		return true;
	}
	else {
		return false;
	}
}

//Get x,y pair from complicated vectors
std::pair<int, int> getPair(sf::Vector2i v) {
	return std::pair<int, int>(v.x, v.y);
}

std::map<std::pair<int, int>, sf::Vector2i>::iterator iter1;
std::map<std::pair<int, int>, sf::Vector2i>::iterator iter2;

bool Game::isCrossing() {

	if (secondLineCode == 0) { //If there is only first line
		//Switching first line
		switch (firstLineCode) {
			//In case first line is pointing down right
		case 2:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].headCoords + right));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].headCoords + down));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == leftdown || iter2->second == rightup) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		case 4:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].headCoords + left));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].headCoords + down));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == rightdown || iter2->second == leftup) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		case 6:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].headCoords + left));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].headCoords + up));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == rightup || iter2->second == leftdown) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		case 8:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].headCoords + right));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].headCoords + up));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == leftup || iter2->second == rightdown) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		}
	}
	else if (thirdLineCode == 0) { //If the second line is last drawn
		//Switching second line
		switch (secondLineCode) {
		case 2:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].firstLineCoords + right));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].firstLineCoords + down));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == leftdown || iter2->second == rightup) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		case 4:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].firstLineCoords + left));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].firstLineCoords + down));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == rightdown || iter2->second == leftup) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		case 6:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].firstLineCoords + left));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].firstLineCoords + up));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == rightup || iter2->second == leftdown) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		case 8:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].firstLineCoords + right));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].firstLineCoords + up));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == leftup || iter2->second == rightdown) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		}
	}
	else { //If the third line is last drawn
		//Switching third line
		switch (thirdLineCode) {
		case 2:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].secondLineCoords + right));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].secondLineCoords + down));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == leftdown || iter2->second == rightup) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		case 4:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].secondLineCoords + left));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].secondLineCoords + down));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == rightdown || iter2->second == leftup) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		case 6:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].secondLineCoords + left));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].secondLineCoords + up));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == rightup || iter2->second == leftdown) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		case 8:
			iter1 = pointAssign.find(getPair(spioszki[spioszekCount - 1].secondLineCoords + right));
			iter2 = pointAssign.find(getPair(spioszki[spioszekCount - 1].secondLineCoords + up));
			if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
				if (iter1->second == leftup || iter2->second == rightdown) {
					return true;
				}
				else {
					return false;
				}
			}
			break;
		}
	}

	return false;
}
bool Game::isCrossingAtWin(Spioszek checking) {
	//Switching first line
	switch (determineLineCode(checking.headCoords, checking.firstLineCoords)) {
		//In case first line is pointing down right
	case 2:
		iter1 = pointAssign.find(getPair(checking.headCoords + right));
		iter2 = pointAssign.find(getPair(checking.headCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftdown || iter2->second == rightup) {
				return true;
			}
		}
		break;
	case 4:
		iter1 = pointAssign.find(getPair(checking.headCoords + left));
		iter2 = pointAssign.find(getPair(checking.headCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightdown || iter2->second == leftup) {
				return true;
			}
		}
		break;
	case 6:
		iter1 = pointAssign.find(getPair(checking.headCoords + left));
		iter2 = pointAssign.find(getPair(checking.headCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightup || iter2->second == leftdown) {
				return true;
			}
		}
		break;
	case 8:
		iter1 = pointAssign.find(getPair(checking.headCoords + right));
		iter2 = pointAssign.find(getPair(checking.headCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftup || iter2->second == rightdown) {
				return true;
			}
		}
		break;
	}

	switch (determineLineCode(checking.firstLineCoords, checking.secondLineCoords)) {
		//In case first line is pointing down right
	case 2:
		iter1 = pointAssign.find(getPair(checking.firstLineCoords + right));
		iter2 = pointAssign.find(getPair(checking.firstLineCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftdown || iter2->second == rightup) {
				return true;
			}
		}
		break;
	case 4:
		iter1 = pointAssign.find(getPair(checking.firstLineCoords + left));
		iter2 = pointAssign.find(getPair(checking.firstLineCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightdown || iter2->second == leftup) {
				return true;
			}
		}
		break;
	case 6:
		iter1 = pointAssign.find(getPair(checking.firstLineCoords + left));
		iter2 = pointAssign.find(getPair(checking.firstLineCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightup || iter2->second == leftdown) {
				return true;
			}
		}
		break;
	case 8:
		iter1 = pointAssign.find(getPair(checking.firstLineCoords + right));
		iter2 = pointAssign.find(getPair(checking.firstLineCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftup || iter2->second == rightdown) {
				return true;
			}
		}
		break;
	}

	switch (determineLineCode(checking.secondLineCoords, checking.thirdLineCoords)) {
		//In case first line is pointing down right
	case 2:
		iter1 = pointAssign.find(getPair(checking.secondLineCoords + right));
		iter2 = pointAssign.find(getPair(checking.secondLineCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftdown || iter2->second == rightup) {
				return true;
			}
		}
		break;
	case 4:
		iter1 = pointAssign.find(getPair(checking.secondLineCoords + left));
		iter2 = pointAssign.find(getPair(checking.secondLineCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightdown || iter2->second == leftup) {
				return true;
			}
		}
		break;
	case 6:
		iter1 = pointAssign.find(getPair(checking.secondLineCoords + left));
		iter2 = pointAssign.find(getPair(checking.secondLineCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightup || iter2->second == leftdown) {
				return true;
			}
		}
		break;
	case 8:
		iter1 = pointAssign.find(getPair(checking.secondLineCoords + right));
		iter2 = pointAssign.find(getPair(checking.secondLineCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftup || iter2->second == rightdown) {
				return true;
			}
		}
		break;
	}

	/*

	//Switching secong line
	switch (secondLineCode) {
	case 2:
		iter1 = pointAssign.find(getPair(spioszki[i].firstLineCoords + right));
		iter2 = pointAssign.find(getPair(spioszki[i].firstLineCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftdown || iter2->second == rightup) {
				return true;
			}
			else {
				return false;
			}
		}
		break;
	case 4:
		iter1 = pointAssign.find(getPair(spioszki[i].firstLineCoords + left));
		iter2 = pointAssign.find(getPair(spioszki[i].firstLineCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightdown || iter2->second == leftup) {
				return true;
			}
			else {
				return false;
			}
		}
		break;
	case 6:
		iter1 = pointAssign.find(getPair(spioszki[i].firstLineCoords + left));
		iter2 = pointAssign.find(getPair(spioszki[i].firstLineCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightup || iter2->second == leftdown) {
				return true;
			}
			else {
				return false;
			}
		}
		break;
	case 8:
		iter1 = pointAssign.find(getPair(spioszki[i].firstLineCoords + right));
		iter2 = pointAssign.find(getPair(spioszki[i].firstLineCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftup || iter2->second == rightdown) {
				return true;
			}
			else {
				return false;
			}
		}
		break;
	}

	//Switching third line
	switch (thirdLineCode) {
	case 2:
		iter1 = pointAssign.find(getPair(spioszki[i].secondLineCoords + right));
		iter2 = pointAssign.find(getPair(spioszki[i].secondLineCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftdown || iter2->second == rightup) {
				return true;
			}
			else {
				return false;
			}
		}
		break;
	case 4:
		iter1 = pointAssign.find(getPair(spioszki[i].secondLineCoords + left));
		iter2 = pointAssign.find(getPair(spioszki[i].secondLineCoords + down));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightdown || iter2->second == leftup) {
				return true;
			}
			else {
				return false;
			}
		}
		break;
	case 6:
		iter1 = pointAssign.find(getPair(spioszki[i].secondLineCoords + left));
		iter2 = pointAssign.find(getPair(spioszki[i].secondLineCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == rightup || iter2->second == leftdown) {
				return true;
			}
			else {
				return false;
			}
		}
		break;
	case 8:
		iter1 = pointAssign.find(getPair(spioszki[i].secondLineCoords + right));
		iter2 = pointAssign.find(getPair(spioszki[i].secondLineCoords + up));
		if (iter1 != pointAssign.end() || iter2 != pointAssign.end()) {
			if (iter1->second == leftup || iter2->second == rightdown) {
				return true;
			}
			else {
				return false;
			}
		}
		break;
	}

	*/
	return false;
}

//Global help functions
sf::Vector2i Game::roundCoords(sf::Vector2i coords) {
	roundX = (round(coords.x / (100.f))) * 100.f; //first divide by 100 to get sth like 1.01, 0.96 then round it up to closest whole
	roundY = (round(coords.y / (100.f))) * 100.f; //number, and then multiply by 100 to get even 100's num
	return sf::Vector2i(roundX, roundY);
}

//Constructors & Destructors
Game::Game() {

}
void Game::initAll() {
	initVars();
	initWindow();
	initPoints();
	initLogo();
	initFont();
	initText();
	initColorBalls();
	initSound();
	initTextboxes();
	initButtons();
}
Game::~Game() {
	delete this->window;
}

//Functions

//Getters Accessors
const bool Game::isWindowOpen() {
	return this->window->isOpen();
}

//Private
void Game::initVars() {
	window = nullptr;
	headHover = new sf::CircleShape;
	isDrawing = false;
	playerDrawing = 0;
	spioszekCount = 0;
	player1Points = 0;
	player2Points = 0;
	screenRules, screenGame, screenEnd = false;
	screen1 = true;
	icon.loadFromFile("resources/icon.png");
	getScore();

	//Forbidden shapes:
	addToList(Vector(2, 5, 8));
}
void Game::initWindow() {
	WIDTH = (int)(sf::VideoMode::getDesktopMode().width * 0.365); //700
	HEIGHT = (int)(sf::VideoMode::getDesktopMode().height * 0.88); //950
	//std::cout << scale << std::endl;
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Spioszki", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings::ContextSettings(0, 0, 10, 2, 0));
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window->setFramerateLimit(30);
}
void Game::initLogo() {
	logoTexture.loadFromFile("resources/spioszki_logo.png");
	logoTexture.setSmooth(true);
	LOGO = sf::Sprite(logoTexture);
	sf::Vector2u size = logoTexture.getSize();
	LOGO.setOrigin(size.x / 2, size.y / 2);
	LOGO.setScale(0.4, 0.4);
	LOGO.setPosition(WIDTH / 2.f, 80.f);
}
void Game::initFont() {
	fontMain.loadFromFile("resources/harringt.otf");
	fontRules.loadFromFile("resources/CaviarDreams.ttf");
}
void Game::initText() {
	gameOverText.setFont(fontMain);
	gameOverText.setCharacterSize(96);
	gameOverText.setFillColor(BLACK);
	gameOverText.setString("Koniec gry!");
	gameOverText.setOrigin(215, 0);
	gameOverText.setPosition(WIDTH / 2, 10);

	welcomeText.setFont(fontMain);
	welcomeText.setCharacterSize(40);
	welcomeText.setFillColor(BLACK);
	welcomeText.setString(L"		   Witaj w grze Śpioszki!\nWybierzcie nicki i zaczynamy zabawę!");
	welcomeText.setPosition(60, 200);

	username1.setFont(fontMain);
	username1.setCharacterSize(36);
	username1.setFillColor(BLACK);
	username1.setString("Nick gracza nr 1");
	username1.setPosition(50, 510);

	username2.setFont(fontMain);
	username2.setCharacterSize(36);
	username2.setFillColor(BLACK);
	username2.setString("Nick gracza nr 2");
	username2.setPosition(50, 670);

	username1display.setFont(fontMain);
	username1display.setCharacterSize(36);
	username1display.setFillColor(player1color);
	username1display.setPosition(100, 760);

	username2display.setFont(fontMain);
	username2display.setCharacterSize(36);
	username2display.setFillColor(player2color);
	username2display.setPosition(400, 760);

	RULES.setFont(fontMain);
	RULES.setCharacterSize(69);
	RULES.setFillColor(BLACK);
	RULES.setString("ZASADY");
	RULES.setPosition(230, 20);

	rulesText.setFont(fontRules);
	rulesText.setCharacterSize(25);
	rulesText.setFillColor(BLACK);
	rulesText.setPosition(30, 120);
	sf::String rules = L"Główny cel jest bardzo prosty: w grze trzeba na przemian umieszczać na planszy tytułowe śpioszki. Kto w swojej turze nie będzie w stanie umieścić już żadnej nowej figury – przegrywa. \nW swojej turze gracz rysuje śpioszka: Główka to kropka pola gry otoczona kółkiem, tułów to linia złożona z trzech odcinków – rozpoczynająca się od głowy i łącząca trzy kolejne kropki planszy. O czym trzeba koniecznie pamiętać w trakcie gry? Śpioszki rysujemy tylko na jeszcze wolnych punktach planszy. Żaden śpioszek nie może dotykać innego. Główki śpioszków nie mogą sąsiadować ani w pionie, ani w poziomie. Co ponadto? Każda figura śpioszka może wystąpić w grze tylko jeden raz. Nieważne, czy będziemy chcieli ułożyć tę figurę w innym kierunku (obróconą wedle osi głowy) czy wykorzystać jej lustrzane odbicie – tego nam nie wolno. \n\n\nKontrola: \Lewy Przycisk Myszy - rysowanie śpioszka \Prawy Przycisk Myszy - anulowanie aktualnie rysowanego śpioszka \n";
	sf::String append;
	int counter = 0;
	//This was only to do the fucking carriage return
	for (auto& i : rules) {
		append += i;
		counter++;
		if (i == 10) {
			counter = 0;
		}
		if (counter > 46 && i == 32) {
			append += "\n";
			counter = 0;
		}
	}
	rulesText.setString(append);

	leaderboardText.setFont(fontRules);
	leaderboardText.setCharacterSize(50);
	leaderboardText.setFillColor(BLACK);
	leaderboardText.setString(L"Najwyższe wyniki: ");
	leaderboardText.setPosition(170, 20);

	playerScores.setFont(fontRules);
	playerScores.setCharacterSize(25);
	playerScores.setFillColor(BLACK);
	playerScores.setPosition(30, 120);
}
void Game::initColorBalls() {
	float x = 0;
	float y = 0;
	for (int i = 0; i < 5; i++) {
		colorBallSet1[i] = ColorBall();
		colorBallSet2[i] = ColorBall();
		switch (i) {
		case 0:
			colorBallSet1[i].setColor(1);
			colorBallSet2[i].setColor(1);
			x = 350;
			break;
		case 1:
			colorBallSet1[i].setColor(2);
			colorBallSet2[i].setColor(2);
			x = 410;
			break;
		case 2:
			colorBallSet1[i].setColor(3);
			colorBallSet2[i].setColor(3);
			x = 470;
			break;
		case 3:
			colorBallSet1[i].setColor(4);
			colorBallSet2[i].setColor(4);
			x = 530;
			break;
		case 4:
			colorBallSet1[i].setColor(5);
			colorBallSet2[i].setColor(5);
			x = 590;
			break;
		}
		colorBallSet1[i].setPosition(sf::Vector2f(x, 580));
		colorBallSet2[i].setPosition(sf::Vector2f(x, 740));
	}
}
void Game::selectColorBall() {
	if (spioszekCount == 0) {
		for (int x = 0; x < 5; x++) {
			if (mousePos.x > 350 && mousePos.x < 650) { //To not declick if clicked elsewhere
				if (mousePos.y >= 570 && mousePos.y < 650) { //Check if mouse is on the set1 or set2
					if (colorBallSet1[x].contains(mousePos)) {
						if (!colorBallSet2[x].getPermSelect()) {
							colorBallSet1[x].setSelected(true);
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
								colorBallSet1[x].setPermSelect(true);
								player1color = colorBallSet1[x].getColor();
								username1display.setFillColor(player1color);
								usernameBox1.setColor(player1color);
							}
						}
					}
					else {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							colorBallSet1[x].setPermSelect(false);
						}
						if (!colorBallSet1[x].getPermSelect()) {
							colorBallSet1[x].setSelected(false);
						}
					}
				}
				else if (mousePos.y >= 730 && mousePos.y <= 800) {
					if (colorBallSet2[x].contains(mousePos)) {
						if (!colorBallSet1[x].getPermSelect()) {
							colorBallSet2[x].setSelected(true);
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
								colorBallSet2[x].setPermSelect(true);
								player2color = colorBallSet2[x].getColor();
								username2display.setFillColor(player2color);
								usernameBox2.setColor(player2color);
							}
						}
					}
					else {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							colorBallSet2[x].setPermSelect(false);
						}
						if (!colorBallSet2[x].getPermSelect()) {
							colorBallSet2[x].setSelected(false);
						}
					}
				}
				else {
					colorBallSet1[x].setSelected(false);
					colorBallSet2[x].setSelected(false);
				}
			}
			else {
				colorBallSet1[x].setSelected(false);
				colorBallSet2[x].setSelected(false);
			}
		}
	}
}
void Game::initSound() {
	wrongSpioszekBuff.loadFromFile("resources/wrong_spioszek.wav");
	wrongSpioszekSound.setBuffer(wrongSpioszekBuff);
	pointMadeBuff.loadFromFile("resources/point_made.wav");
	pointMadeSound.setBuffer(pointMadeBuff);
	gameOverBuff.loadFromFile("resources/game_over.wav");
	gameOverSound.setBuffer(gameOverBuff);
}
void Game::initTextboxes() {
	//Username Box 1
	usernameBox1 = Textbox(48, player1color, false);
	usernameBox1.setFont(fontMain);
	usernameBox1.setPosition(sf::Vector2f(350, 500));
	usernameBox1.setLimit(true, 12);

	//Username Box 2
	usernameBox2 = Textbox(48, player2color, false);
	usernameBox2.setFont(fontMain);
	usernameBox2.setPosition(sf::Vector2f(350, 660));
	usernameBox2.setLimit(true, 12);
}
void Game::checkBoxSelection() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//Check for Username Box 1
		if (mousePos.x > usernameBox1.getBoxPosition().x && mousePos.x < usernameBox1.getBoxPosition().x + usernameBox1.getBoxSize().x) {
			if (mousePos.y > usernameBox1.getBoxPosition().y && mousePos.y < usernameBox1.getBoxPosition().y + usernameBox1.getBoxSize().y) {
				usernameBox1.setSelected(true);
			}
			else {
				usernameBox1.setSelected(false);
			}
		}
		else {
			usernameBox1.setSelected(false);
		}

		//Check for Username Box 2
		if (mousePos.x > usernameBox2.getBoxPosition().x && mousePos.x < usernameBox2.getBoxPosition().x + usernameBox2.getBoxSize().x) {
			if (mousePos.y > usernameBox2.getBoxPosition().y && mousePos.y < usernameBox2.getBoxPosition().y + usernameBox2.getBoxSize().y) {
				usernameBox2.setSelected(true);
			}
			else {
				usernameBox2.setSelected(false);
			}
		}
		else {
			usernameBox2.setSelected(false);
		}
	}
}
void Game::initButtons() {
	buttonStart.setTexture("resources/buttonStart.png");
	buttonStart.setPosition(sf::Vector2f((WIDTH / 2 - 150), 820));

	buttonRules.setTexture("resources/buttonRules.png");
	buttonRules.setPosition(sf::Vector2f((WIDTH / 2 - 230), 350));

	buttonBack.setTexture("resources/buttonBack.png");
	buttonBack.setPosition(sf::Vector2f(20, 20));

	buttonPlayAgain.setTexture("resources/buttonPlayAgain.png");
	buttonPlayAgain.setPosition(sf::Vector2f((WIDTH / 2 - 150), 820));

	buttonLeaderboard.setTexture("resources/buttonLeaderboard.png");
	buttonLeaderboard.setPosition(sf::Vector2f((WIDTH / 2 + 30), 350));
}
void Game::checkButtonClick() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (screen1) {
			//Check for Button Start
			if (mousePos.x > buttonStart.getPosition().x && mousePos.x < buttonStart.getPosition().x + buttonStart.getSize().x) {
				if (mousePos.y > buttonStart.getPosition().y && mousePos.y < buttonStart.getPosition().y + buttonStart.getSize().y) {
					username1string = usernameBox1.getText();
					username2string = usernameBox2.getText();
					if (username1string == "") {
						username1string = "Anonymous";
					}
					if (username2string == "") {
						username2string = "Anonymous";
					}
					username1display.setString(username1string + ": " + std::to_string(player1Points));
					username2display.setString(username2string + ": " + std::to_string(player2Points));

					screen1 = false;
					screenGame = true;
				}
			}

			//Check for button Rules
			if (mousePos.x > buttonRules.getPosition().x && mousePos.x < buttonRules.getPosition().x + buttonRules.getSize().x) {
				if (mousePos.y > buttonRules.getPosition().y && mousePos.y < buttonRules.getPosition().y + buttonRules.getSize().y) {
					screen1 = false;
					screenRules = true;
				}
			}
		}

		//Check for button back
		if (screenRules) {
			if (mousePos.x > buttonBack.getPosition().x && mousePos.x < buttonBack.getPosition().x + buttonBack.getSize().x) {
				if (mousePos.y > buttonBack.getPosition().y && mousePos.y < buttonBack.getPosition().y + buttonBack.getSize().y) {
					screenRules = false;
					screen1 = true;
				}
			}
		}

		//Check for button back in game
		if (screenGame) {
			if (mousePos.x > buttonBack.getPosition().x && mousePos.x < buttonBack.getPosition().x + buttonBack.getSize().x) {
				if (mousePos.y > buttonBack.getPosition().y && mousePos.y < buttonBack.getPosition().y + buttonBack.getSize().y) {
					screenGame = false;
					screen1 = true;
				}
			}
		}

		//Check for button back in Leaderboard
		if (screenLeaderboard) {
			if (mousePos.x > buttonBack.getPosition().x && mousePos.x < buttonBack.getPosition().x + buttonBack.getSize().x) {
				if (mousePos.y > buttonBack.getPosition().y && mousePos.y < buttonBack.getPosition().y + buttonBack.getSize().y) {
					screenLeaderboard = false;
					screen1 = true;
				}
			}
		}

		//Check for button Play Again
		if (screenEnd) {
			if (mousePos.x > buttonPlayAgain.getPosition().x && mousePos.x < buttonPlayAgain.getPosition().x + buttonPlayAgain.getSize().x) {
				if (mousePos.y > buttonPlayAgain.getPosition().y && mousePos.y < buttonPlayAgain.getPosition().y + buttonPlayAgain.getSize().y) {
					screenEnd = false;
					screenGame = true;
					spioszekCount = 0;
					coordinatesForHead.clear();
					coordinatesForLine.clear();
					isDrawing = false;
					clickCount = 0;
					pointAssign.clear();
					existingShapes.clear();
					//Forbidden shapes:
					addToList(Vector(2, 5, 8));
				}
			}
		}

		//Check for button Leaderboard
		if (screen1) {
			if (mousePos.x > buttonLeaderboard.getPosition().x && mousePos.x < buttonLeaderboard.getPosition().x + buttonLeaderboard.getSize().x) {
				if (mousePos.y > buttonLeaderboard.getPosition().y && mousePos.y < buttonLeaderboard.getPosition().y + buttonLeaderboard.getSize().y) {
					screen1 = false;
					screenLeaderboard = true;
				}
			}
		}
	}
}
void Game::initPoints() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			points[i][j].setRadius(5.f);
			points[i][j].setFillColor(BLACK);
			points[i][j].setPosition((firstPointX - 5.f + j * 100.f), (firstPointY - 5.f + i * 100.f));
		}
	}
}
void Game::updateMousePosition() {
	mousePos = sf::Mouse::getPosition(*window);
}

//Game logic functions
void Game::checkMouseHover() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			//checking if mouse is in X range <-15, 15> from center of the circle
			if (mousePos.x > (firstPointX - tempRad + j * 100.f) && mousePos.x < (firstPointX + tempRad + j * 100.f)) {
				//checking if mouse is in Y range <-15, 15> from center of the circle
				if (mousePos.y > (firstPointY - tempRad + i * 100.f) && mousePos.y < (firstPointY + tempRad + i * 100.f)) {

					if (spioszekCount != 0) {
						for (int x = 0; x < spioszekCount; x++) {
							//Prevent from head placement
							coordinatesForHead.push_back(spioszki[x].headCoords);
							coordinatesForHead.push_back(spioszki[x].firstLineCoords);
							coordinatesForHead.push_back(spioszki[x].secondLineCoords);
							coordinatesForHead.push_back(spioszki[x].thirdLineCoords);
							coordinatesForHead.push_back(spioszki[x].headCoords + sf::Vector2i(100, 0));
							coordinatesForHead.push_back(spioszki[x].headCoords + sf::Vector2i(0, 100));
							coordinatesForHead.push_back(spioszki[x].headCoords + sf::Vector2i(-100, 0));
							coordinatesForHead.push_back(spioszki[x].headCoords + sf::Vector2i(0, -100));
						}
						if (!(std::find(coordinatesForHead.begin(), coordinatesForHead.end(), roundCoords(mousePos)) != coordinatesForHead.end())) {
							headHover->setRadius(15.f);
							headHover->setFillColor(BLANK);
							switch (playerDrawing) {
							case 0:
								headHover->setOutlineColor(player1color);
								break;
							case 1:
								headHover->setOutlineColor(player2color);
								break;
							}
							headHover->setOutlineThickness(1.5);
							headHover->setPosition((firstPointX - tempRad + j * 100.f), (firstPointY - tempRad + i * 100.f));
							checkMousePress();
						}
					}
					else {
						headHover->setRadius(15.f);
						headHover->setFillColor(BLANK);
						switch (playerDrawing) {
						case 0:
							headHover->setOutlineColor(player1color);
							break;
						case 1:
							headHover->setOutlineColor(player2color);
							break;
						}
						headHover->setOutlineThickness(1.5);
						headHover->setPosition((firstPointX - tempRad + j * 100.f), (firstPointY - tempRad + i * 100.f));
						checkMousePress();
					}
					coordinatesForHead.clear();
				}
			}
		}
	}
}
void Game::checkMousePress() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseClicked == false) {
		isMouseClicked = true;
		spioszekCount++;
		clickCount++;
		isDrawing = true;
		if (spioszekCount >= 10) {
			screenGame = false;
			screenEnd = true;
		}
		else {
			switch (playerDrawing) {
			case 0:
				spioszki[spioszekCount - 1] = Spioszek(roundCoords(mousePos), player1color); //First player in game, draw BLACK
				pointMadeSound.play();
				break;
			case 1:
				spioszki[spioszekCount - 1] = Spioszek(roundCoords(mousePos), player2color); //Second player in game, draw RED
				pointMadeSound.play();
			}
			spioszki[spioszekCount - 1].drawHead();
			tempPosition = roundCoords(mousePos);
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && isMouseClicked) { //"Deactivate" mouse for another frame until we release
		isMouseClicked = false;
	}
}
void Game::drawingStage() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			//checking if mouse is in X range <-15, 15> from center of the circle
			if (mousePos.x > (firstPointX - tempRad + j * 100.f) && mousePos.x < (firstPointX + tempRad + j * 100.f) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) { //Without mouse control bugs happened
				//checking if mouse is in Y range <-15, 15> from center of the circle
				if (mousePos.y > (firstPointY - tempRad + i * 100.f) && mousePos.y < (firstPointY + tempRad + i * 100.f)) {

					//Check if just drawn Spioszek doesn't crush into another Spioszek
					for (int x = 0; x < spioszekCount; x++) {
						//Prevent from line placement
						coordinatesForLine.push_back(spioszki[x].headCoords);
						coordinatesForLine.push_back(spioszki[x].firstLineCoords);
						coordinatesForLine.push_back(spioszki[x].secondLineCoords);
						coordinatesForLine.push_back(spioszki[x].thirdLineCoords);
					}
					if (!(findInAvailablePoints(roundCoords(mousePos)))) {
						//Check for click and draw spioszek
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseClicked == false) {
							isMouseClicked = true;
							//Actually drawing lines
							switch (clickCount) {
							case 1:
								//Draw 1st line
								if (findInAvailableDirections(roundCoords(mousePos) - tempPosition)) { //To check if user isn't clicking on the wrong point
									spioszki[spioszekCount - 1].drawFirstLine(roundCoords(mousePos));
									firstLineCode = determineLineCode(tempPosition, roundCoords(mousePos)); //Determination of the line code of my system
									if (isCrossing()) {
										wrongSpioszekSound.play();
										spioszekCount--;
										isDrawing = false;
										firstLineCode = 0;
										secondLineCode = 0;
										thirdLineCode = 0;
										clickCount = 0;
									}
									else {
										tempPosition = roundCoords(mousePos);
										pointMadeSound.play();
										clickCount++;
									}
									break;
								}
								else {
									break;
								}

							case 2:
								//Draw 2nd line
								if (findInAvailableDirections(roundCoords(mousePos) - tempPosition)) {
									spioszki[spioszekCount - 1].drawSecondLine(roundCoords(mousePos));
									secondLineCode = determineLineCode(tempPosition, roundCoords(mousePos)); //Determination of the line code of my system
									if (isCrossing()) {
										wrongSpioszekSound.play();
										spioszekCount--;
										isDrawing = false;
										firstLineCode = 0;
										secondLineCode = 0;
										thirdLineCode = 0;
										clickCount = 0;
									}
									else {
										tempPosition = roundCoords(mousePos);
										pointMadeSound.play();
										clickCount++;
									}
									break;
								}
								else {
									break;
								}
							case 3:
								//Draw 3rd line
								if (findInAvailableDirections(roundCoords(mousePos) - tempPosition)) {
									spioszki[spioszekCount - 1].drawThirdLine(roundCoords(mousePos));

									thirdLineCode = determineLineCode(tempPosition, roundCoords(mousePos)); //Determination of the line code of my system
									if (isCrossing()) {
										wrongSpioszekSound.play();
										spioszekCount--;
										isDrawing = false;
										firstLineCode = 0;
										secondLineCode = 0;
										thirdLineCode = 0;
										clickCount = 0;
									}
									else {
										shape = createShape(firstLineCode, secondLineCode, thirdLineCode);
										if (checkIfExists(shape) == false) {
											pointMadeSound.play();
											addToList(shape);

											//Adding directions to freshly added points
											pointAssign.insert({ getPair(spioszki[spioszekCount - 1].headCoords), directions[firstLineCode - 1] });
											pointAssign.insert({ getPair(spioszki[spioszekCount - 1].firstLineCoords), directions[secondLineCode - 1] });
											pointAssign.insert({ getPair(spioszki[spioszekCount - 1].secondLineCoords), directions[thirdLineCode - 1] });

											//For winning (clear after checking!)
											for (int x = 0; x < spioszekCount; x++) {
												coordinatesForWinningCheck.push_back(spioszki[x].headCoords);
												coordinatesForWinningCheck.push_back(spioszki[x].firstLineCoords);
												coordinatesForWinningCheck.push_back(spioszki[x].secondLineCoords);
												coordinatesForWinningCheck.push_back(spioszki[x].thirdLineCoords);
												coordinatesForWinningCheck.push_back(spioszki[x].headCoords + sf::Vector2i(100, 0));
												coordinatesForWinningCheck.push_back(spioszki[x].headCoords + sf::Vector2i(0, 100));
												coordinatesForWinningCheck.push_back(spioszki[x].headCoords + sf::Vector2i(-100, 0));
												coordinatesForWinningCheck.push_back(spioszki[x].headCoords + sf::Vector2i(0, -100));

												coordinatesForWinningCheckLine.push_back(spioszki[x].headCoords);
												coordinatesForWinningCheckLine.push_back(spioszki[x].firstLineCoords);
												coordinatesForWinningCheckLine.push_back(spioszki[x].secondLineCoords);
												coordinatesForWinningCheckLine.push_back(spioszki[x].thirdLineCoords);
											}
											checkIfWin();

											//Changing which player is drawing at this moment
											if (playerDrawing == 0) {
												playerDrawing = 1;
											}
											else if (playerDrawing == 1) {
												playerDrawing = 0;
											}
											isDrawing = false;
											firstLineCode = 0;
											secondLineCode = 0;
											thirdLineCode = 0;
											clickCount = 0;
										}
										else {
											wrongSpioszekSound.play();
											spioszekCount--;
											isDrawing = false;
											firstLineCode = 0;
											secondLineCode = 0;
											thirdLineCode = 0;
											clickCount = 0;
										}
									}
								}
								else {
									break;
								}
								break;
							}
						}
					}
					while (isMouseClicked) {      //"Deactivate" mouse for another frame until we release
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false) {
							isMouseClicked = false;
						}
					}
					coordinatesForLine.clear();
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isMouseClicked == false) {
				isMouseClicked = true;
				spioszekCount--;
				isDrawing = false;
				firstLineCode = 0;
				secondLineCode = 0;
				thirdLineCode = 0;
				clickCount = 0;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == false && isMouseClicked) { //"Deactivate" mouse for another frame until we release
				isMouseClicked = false;
			}
		}
	}

}

void Game::drawSpioszki(int spioszekNum) {
	window->draw(spioszki[spioszekNum].head);
	window->draw(spioszki[spioszekNum].firstLine);
	window->draw(spioszki[spioszekNum].secondLine);
	window->draw(spioszki[spioszekNum].thirdLine);
}


//Public

void Game::pollEvents() {

	while (this->window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			saveScore();
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				window->close();
			}
			//if (!usernameBox1.getSelected() || !usernameBox2.getSelected()) {
			//	if (event.key.code == sf::Keyboard::C) {
			//		spioszekCount = 0;
			//		coordinatesForHead.clear();
			//		coordinatesForLine.clear();
			//		isDrawing = false;
			//		clickCount = 0;
			//		playerDrawing = 0;
			//		pointAssign.clear();
			//		existingShapes.clear();
			//		//Forbidden shapes:
			//		addToList(Vector(2, 5, 8));
			//		system("cls");
			//	}
			//	if (event.key.code == sf::Keyboard::A) {
			//		screenGame = false;
			//		screenEnd = true;
			//		elapsed1 = clock.getElapsedTime();
			//		if (playerDrawing == 0) {
			//			player1Points++;
			//		}
			//		else if (playerDrawing == 1) {
			//			player2Points++;
			//		}
			//		username1display.setString(username1string + ": " + to_string(player1Points));
			//		username2display.setString(username2string + ": " + to_string(player2Points));
			//	}
			//}
			break;
		case sf::Event::TextEntered:
			if (usernameBox1.getSelected()) {
				if (event.text.unicode == 9) {
					usernameBox1.setSelected(false);
					usernameBox2.setSelected(true);
					break;
				}
				usernameBox1.textTyped(event);
				break;
			}
			else if (usernameBox2.getSelected()) {
				usernameBox2.textTyped(event);
				break;
			}
		}
	}
}

void Game::frameUpdate() {
	if (screen1) {
		pollEvents();
		updateMousePosition();
		checkBoxSelection();
		checkButtonClick();
		selectColorBall();
	}
	if (screenRules) {
		pollEvents();
		updateMousePosition();
		checkButtonClick();
	}
	if (screenLeaderboard) {
		pollEvents();
		updateMousePosition();
		checkButtonClick();
	}
	if (screenGame) {                                      //While the game is in the play stage
		//Initalize variables & pointers all the time
		headHover = new sf::CircleShape;

		//Actually run functions
		pollEvents();
		updateMousePosition();
		checkButtonClick();

		if (isDrawing == false) {
			checkMouseHover();
		}
		else {
			drawingStage();
		}

	}
	if (screenEnd) {                                                  //The game ended and this is end screen
		pollEvents();
		updateMousePosition();
		checkButtonClick();
	}
}

void Game::render() {
	if (screen1) {
		window->clear(bgColor);
		this->window->draw(LOGO);
		this->window->draw(welcomeText);
		usernameBox1.drawTo(*window);
		usernameBox2.drawTo(*window);
		this->window->draw(username1);
		this->window->draw(username2);
		buttonStart.drawTo(*window);
		buttonRules.drawTo(*window);
		buttonLeaderboard.drawTo(*window);
		for (int i = 0; i < 5; i++) {
			if (colorBallSet1[i].getSelected() || colorBallSet1[i].getPermSelect()) {
				colorBallSet1[i].drawSelectedTo(*window);
			}
			else {
				colorBallSet1[i].drawTo(*window);
			}

			if (colorBallSet2[i].getSelected() || colorBallSet2[i].getPermSelect()) {
				colorBallSet2[i].drawSelectedTo(*window);
			}
			else {
				colorBallSet2[i].drawTo(*window);
			}
		}

		window->display();
	}
	if (screenRules) {
		window->clear(bgColor);
		this->window->draw(RULES);
		this->window->draw(rulesText);
		buttonBack.drawTo(*window);
		window->display();
	}
	if (screenLeaderboard) {
		window->clear(bgColor);
		//List of the best people after closing an app is getting bigger and bigger
		this->window->draw(playerScores);
		this->window->draw(leaderboardText);
		buttonBack.drawTo(*window);
		window->display();
	}
	if (screenGame) {
		this->window->clear(bgColor);
		//Logo of Spioszki
		this->window->draw(LOGO);
		
		//Button back
		buttonBack.drawTo(*window);

		//Texts
		this->window->draw(username1display);
		this->window->draw(username2display);

		//Draw objects
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				window->draw(points[i][j]);
			}
		}
		for (int i = 0; i < spioszekCount; i++) {
			drawSpioszki(i);
		}
		window->draw(*headHover);

		delete headHover;
		this->window->display();

	}
	if (screenEnd) { //Game ended
		elapsed2 = clock.getElapsedTime();
		if (elapsed2.asSeconds() - elapsed1.asSeconds() <= 2) {
			if (elapsed2.asMilliseconds() - elapsed1.asMilliseconds() < 300 ||
				(elapsed2.asMilliseconds() - elapsed1.asMilliseconds() > 600 && elapsed2.asMilliseconds() - elapsed1.asMilliseconds() < 900) ||
				(elapsed2.asMilliseconds() - elapsed1.asMilliseconds() > 1200 && elapsed2.asMilliseconds() - elapsed1.asMilliseconds() < 1500)) {
				this->window->clear(bgColor);
				this->window->draw(gameOverText);

				//Texts
				this->window->draw(username1display);
				this->window->draw(username2display);
			}
			else {
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 6; j++) {
						window->draw(points[i][j]);
					}
				}
				for (int i = 0; i < spioszekCount; i++) {
					drawSpioszki(i);
				}
			}
			this->window->display();
		}
		else if (elapsed2.asSeconds() - elapsed1.asSeconds() > 2) {
			this->window->clear(bgColor);
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					window->draw(points[i][j]);
				}
			}
			for (int i = 0; i < spioszekCount; i++) {
				drawSpioszki(i);
			}
			this->window->draw(gameOverText);

			//Texts
			this->window->draw(username1display);
			this->window->draw(username2display);

			//Buttons
			buttonPlayAgain.drawTo(*window);

			this->window->display();
		}
	}
}

//Here is function to save scores
void Game::saveScore() {
	if (player1Points != 0 || player2Points != 0) {
		getLines();
		if (player1Points > player2Points) {
			fileLeaderboardWrite.open("leaderboard.dat", std::ios::out | std::ios::app);
			fileLeaderboardWrite << lineCount << ". " << username1string << " - " << player1Points << " pkt" << std::endl;
		}
		else {
			fileLeaderboardWrite.open("leaderboard.dat", std::ios::out | std::ios::app);
			fileLeaderboardWrite << lineCount << ". " << username2string << " - " << player2Points << " pkt" << std::endl;
		}
		fileLeaderboardWrite.close();
	}
}

void Game::getScore() {
	fileLeaderboardRead.open("leaderboard.dat", std::ios::in);
	std::string line = "";
	if (fileLeaderboardRead.is_open()) {
		while (std::getline(fileLeaderboardRead, line)) {
			scores += line + "\n";
		}
		fileLeaderboardRead.close();
	}
	playerScores.setString(scores);
}

void Game::getLines() {
	fileLeaderboardRead.open("leaderboard.dat", std::ios::in);
	std::string line = "";
	if (fileLeaderboardRead.is_open()) {
		while (std::getline(fileLeaderboardRead, line)) {
			lineCount++;
		}
		fileLeaderboardRead.close();
	}
}



//HERE IS AN ALGORITHM FOR CHECKING IF SOMEBODY WON THE GAME

bool isAvailableHead(sf::Vector2i point) {
	//If point isn't the head or isn't right by the head or the line
	if (!(std::find(coordinatesForWinningCheck.begin(), coordinatesForWinningCheck.end(), point) != coordinatesForWinningCheck.end())) {
		return true;
	}
	else {
		return false;
	}
}

bool isAvailable(sf::Vector2i point) {
	//If point isn't the head or isn't right by the head or the line
	if (!(std::find(coordinatesForWinningCheckLine.begin(), coordinatesForWinningCheckLine.end(), point) != coordinatesForWinningCheckLine.end())) {
		return true;
	}
	else {
		return false;
	}
}

sf::Vector2i marker1;
sf::Vector2i marker2;
sf::Vector2i marker3;
bool isPossible = false;

void Game::checkIfWin() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			sf::Vector2i point = sf::Vector2i((firstPointX + j * 100), (firstPointY + i * 100));
			//If point isn't the head or isn't right by the head or isn't a line
			marker1 = point;
			if (isAvailableHead(marker1)) {
				//First Lines Possibilities
				for (int i = 0; i < 8; i++) {
					if ((marker1 + directions[i]).x < 100 || (marker1 + directions[i]).y < 200 || (marker1 + directions[i]).x > 600 || (marker1 + directions[i]).y > 700) {
						continue;
					}
					if (isAvailable(marker1 + directions[i])) {
						//Second Lines Possibilities
						marker2 = marker1 + directions[i];
						for (int j = 0; j < 8; j++) {
							if ((marker2 + directions[j]).x < 100 || (marker2 + directions[j]).y < 200 || (marker2 + directions[j]).x > 600 || (marker2 + directions[j]).y > 700) {
								continue;
							}
							if (marker2 + directions[j] == marker1) {
								continue;
							}
							if (isAvailable(marker2 + directions[j])) {
								//Third Lines Possibilities
								marker3 = marker2 + directions[j];
								for (int x = 0; x < 8; x++) {
									if ((marker3 + directions[x]).x < 100 || (marker3 + directions[x]).y < 200 || (marker3 + directions[x]).x > 600 || (marker3 + directions[x]).y > 700) {
										continue;
									}
									if (marker3 + directions[x] == marker1 || marker3 + directions[x] == marker2) {
										continue;
									}
									if (isAvailable(marker3 + directions[x])) {
										if (isCrossingAtWin(Spioszek(marker1, marker2, marker3, directions[x]))) {
											isPossible = false;
										}
										else {
											if (checkIfExists(createShape(determineLineCode(marker1, marker2), determineLineCode(marker2, marker3), determineLineCode(marker3, marker3 + directions[x])))) {
												isPossible = false;
											}
											else {
												isPossible = true;
											}
										}
									}
									else {
										isPossible = false;
									}
									if (isPossible) {
										break;
									}
								}
							}
							if (isPossible) {
								break;
							}
						}
					}
					if (isPossible) {
						break;
					}
				}
			}
			if (isPossible) {
				break;
			}
		}
		if (isPossible) {
			break;
		}
	}
	if (!isPossible) {
		screenGame = false;
		screenEnd = true;
		elapsed1 = clock.getElapsedTime();
		if (playerDrawing == 0) {
			player1Points++;
			playerDrawing = 0;
		}
		else if (playerDrawing == 1) {
			player2Points++;
			playerDrawing = 1;
		}
		username1display.setString(username1string + ": " + std::to_string(player1Points));
		username2display.setString(username2string + ": " + std::to_string(player2Points));
		isPossible = false;
		coordinatesForWinningCheck.clear();
		coordinatesForWinningCheckLine.clear();
		gameOverSound.play();
	}
	isPossible = false;
	coordinatesForWinningCheck.clear();
	coordinatesForWinningCheckLine.clear();
}
