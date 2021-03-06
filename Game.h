#pragma once

//STD Classes
#include <iostream>
#include <map>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Own classes
#include "Vector.h"
#include "Spioszek.h"
#include "Textbox.h"
#include "Button.h"
#include "ColorBall.h"

class Game{
private:

	//Variables
	int WIDTH; //700
	int HEIGHT; //950
	int firstPointX = 100;
	int firstPointY = 200;
	int spioszekCount = 0;
	int player1Points = 0;
	int player2Points = 0;
	//Which player is drawing
	int playerDrawing = 0;
	sf::CircleShape* headHover;
	sf::Event event;

	//Screens
	bool screen1, screenRules, screenLeaderboard, screenGame, screenEnd = {};

	//Usernames
	std::string username1string, username2string = {};

	//Objects
	sf::CircleShape	points[6][6];
	Spioszek spioszki[9];

	//Files
	std::ofstream fileLeaderboardWrite;
	std::ifstream fileLeaderboardRead;
	sf::String scores = "";
	int lineCount = 1;

	//Time
	sf::Clock clock;
	sf::Time elapsed1, elapsed2 = {};

	//Colors
	sf::Color WHITE = sf::Color::White;
	sf::Color DEFAULT_RED = sf::Color::Red;
	sf::Color RED = sf::Color(186, 45, 11);
	sf::Color LIGHT_BLUE = sf::Color(213, 242, 227);
	sf::Color LIGHT_GREEN = sf::Color(115, 203, 159);
	sf::Color GREEN = sf::Color(0, 62, 31);
	sf::Color LIGHT_BLACK = sf::Color(1, 17, 10);
	sf::Color BLACK = sf::Color::Black;
	sf::Color BLANK = sf::Color(0, 0, 0, 0);
	//Players colors
	sf::Color player1color = BLACK;
	sf::Color player2color = DEFAULT_RED;

	//Background Color
	sf::Color bgColor = sf::Color(150, 145, 140);

	//Color balls
	ColorBall colorBallSet1[5];
	ColorBall colorBallSet2[5];
	void initColorBalls();
	void selectColorBall();

	//Textures
	sf::Image icon;
	sf::Texture logoTexture;

	//Objects
	sf::Sprite LOGO;
	void initLogo();

	//Fonts
	sf::Font fontMain;
	sf::Font fontRules;
	void initFont();

	//Texts
	sf::Text gameOverText, welcomeText, username1, username2, username1display, username2display, RULES, rulesText, playerScores, leaderboardText;
	void initText();

	//Sound buffs and sounds
	sf::SoundBuffer wrongSpioszekBuff;
	sf::Sound wrongSpioszekSound;
	sf::SoundBuffer pointMadeBuff;
	sf::Sound pointMadeSound;
	sf::SoundBuffer gameOverBuff;
	sf::Sound gameOverSound;
	void initSound();

	//TextBoxes
	Textbox usernameBox1;
	Textbox usernameBox2;
	void initTextboxes();
	void checkBoxSelection();

	//Buttons
	Button buttonStart;
	Button buttonRules;
	Button buttonBack;
	Button buttonPlayAgain;
	Button buttonLeaderboard;
	void initButtons();
	void checkButtonClick();

	//Map for point assign
	std::map<std::pair<int, int>, sf::Vector2i> pointAssign = {};

	//Functions
	void initWindow();
	void initVars();
	void initPoints();
	void updateMousePosition();

	//Game logic variables
	sf::Vector2i mousePos = {};

	//Game logic functions
	void checkMouseHover();
	void checkMousePress();
	void drawingStage();
	void drawSpioszki(int spioszekNum);
	bool isCrossing();
	bool isCrossingAtWin(Spioszek checking);
	void checkIfWin();
	void saveScore();
	void getScore();
	void getLines();

	//Help functions
	sf::Vector2i roundCoords(sf::Vector2i coords);
	int determineLineCode(sf::Vector2i a, sf::Vector2i b);
	Vector createShape(int a, int b, int c);
	void addToList(Vector shapeToAdd);
	bool checkIfExists(Vector shape_arg);

public:

	//Variables
	sf::RenderWindow* window;

	//Constructors
	Game();
	virtual ~Game();

	//Getters Accessors
	const bool isWindowOpen();

	//Functions
	void initAll();
	void pollEvents();
	void frameUpdate();
	void render();

};