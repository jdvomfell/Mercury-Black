#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <map>

/* Editing Types */

#define POINT 1
#define OBJECT 2

/* Editing Tools */

#define PLACE 1
#define DELETE 2
#define MOVE 3

class Cursor {

public:

	sf::RectangleShape rect;
	float velX;
	float velY;

};

class Point {

public:

	sf::RectangleShape rect;
	int x;
	int y;

	Point(int x1, int y1) { rect.setSize(sf::Vector2f(5, 5)); rect.setFillColor(sf::Color::Black); x = x1; y = y1; rect.setPosition(sf::Vector2f(x, y)); }

};

class Object {
public:

	int x;
	int y;
	int rotation;
	float scale;
};

class Editor : public GameState {

public:

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvent(GameEngine* engine);
	void update(GameEngine* engine);
	void render(GameEngine* engine);

	void save();
	void load();

	static Editor* instance() { return &editor; }

	sf::View view;

protected:

	Editor() {}

private:

	Cursor cursor;
	static Editor editor;

	Point* tempPoint;
	sf::VertexArray lines;

	std::map<int, Point*> pointMap;
	std::multimap<int, sf::Sprite*> objectMap;

	int mode;
	int tool;

	bool doLeft;
	bool doRight;
	bool doUp;
	bool doDown;
	bool doReturn;
	bool find;
	bool leftReleased;
	bool rightReleased;

	bool showLines;
	bool showPoints;

	sf::Text modeText;
	sf::Text toolText;

	sf::Text xPos;
	sf::Text yPos;

	sf::Font font;

};

#endif
