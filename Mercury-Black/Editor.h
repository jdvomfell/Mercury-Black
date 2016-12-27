#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include "CollisionMap.h"
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

	Cursor();

	sf::RectangleShape rect;

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

	void rotateMode();
	void rotateTool();

	static Editor* instance() { return &editor; }

	sf::View view;

protected:

	Editor() {}

private:

	Cursor cursor;
	static Editor editor;

	std::multimap<int, sf::Sprite*> objectMap;

	CollisionMap collisionMap;

	int mode;
	int tool;

	bool doLeft;
	bool doRight;
	bool doUp;
	bool doDown;

	bool showLines;

	float viewVelX;
	float viewVelY;

	sf::Text modeText;
	sf::Text toolText;

	sf::Font font;

};

#endif
