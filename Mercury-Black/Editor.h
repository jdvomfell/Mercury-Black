#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include <map>

#include "CollisionMap.h"
#include "ObjectMap.h"
#include "GameState.h"
#include "PlatformMap.h"

/* Editing Types */

#define POINT 1
#define OBJECT 2
#define PLATFORM 3

/* Editing Tools */

#define PLACE 1
#define DELETE 2
#define MOVE 3
#define BOX 4
#define GROUND 5

class Selector {

public:

	Selector();

	sf::RectangleShape rect;

};

class Editor : public GameState {

public:

	sf::View view;

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static Editor* instance(GameEngine * engine) { editor.engine = engine; return &editor; }

	/* Utility Functions */

	void rotateMode();
	void rotateTool();

	/* Object */

	/* Point */

protected:

	Editor() {}

private:

	Selector selector;
	static Editor editor;

	ObjectMap objectMap;
	PlatformMap platformMap;
	PlatformPoints platformPoints;

	int mode;
	int tool;

	bool doLeft;
	bool doRight;
	bool doUp;
	bool doDown;

	bool showLines;

	float viewVelX;
	float viewVelY;

	float zoom;

	sf::Vector2f corner1;
	sf::Vector2f corner2;
	sf::RectangleShape rect;

	sf::Text modeText;
	sf::Text toolText;
	sf::Text textureText;

};

#endif
