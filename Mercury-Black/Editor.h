#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include <map>

#include "CollisionMap.h"
#include "ObjectMap.h"
#include "GameState.h"

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

class Editor : public GameState {

public:

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	void rotateMode();
	void rotateTool();

	static Editor* instance(GameEngine * engine) { editor.engine = engine; return &editor; }

	sf::View view;

protected:

	Editor() {}

private:

	Cursor cursor;
	static Editor editor;

	CollisionMap collisionMap;
	ObjectMap objectMap;

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
