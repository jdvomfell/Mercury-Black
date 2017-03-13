#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include <map>

#include "CollisionMap.h"
#include "ObjectMap.h"
#include "GameState.h"
#include "PlatformMap.h"
#include "GUI.h"
#include "Buttons.h"

/* Editing Types */

#define OBJECT 1
#define PLATFORM 2
#define EVENT 3

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

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static Editor* instance(GameEngine * engine) { editor.engine = engine; return &editor; }

	/* Utility Functions */

	void rotateMode();
	void rotateTool();
	void deselect();

	/* Object */

	/* Point */

protected:

	Editor() {}

private:

	Selector selector;
	static Editor editor;

	ObjectMap objectMap;
	PlatformMap platformMap;

	int mode;
	int tool;

	bool doSpeedUp;
	bool doLeft;
	bool doRight;
	bool doUp;
	bool doDown;

	float viewVelX;
	float viewVelY;

	float zoom;

	sf::View view;
	sf::View toolBoxView;

	sf::Vector2f corner1;
	sf::Vector2f corner2;

	sf::Text modeText;
	sf::Text toolText;
	sf::Text textureText;
	sf::Text morphText;

	GUI_Handler guiHandler;
	sf::RectangleShape toolBox;
	IconButton boxTool;
	IconButton freeTool;
	IconButton groundTool;

};

#endif
