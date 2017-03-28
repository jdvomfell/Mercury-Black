#ifndef EDITOR_H
#define EDITOR_H

#include <SFML/Graphics.hpp>
#include <map>

#include "Water.h"
#include "CollisionMap.h"
#include "ObjectMap.h"
#include "GameState.h"
#include "PlatformMap.h"
#include "GUI.h"
#include "Buttons.h"
#include "ToolBox.h"

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
	WaterHandler waterHandler;

	bool doSpeedUp;
	bool doLeft;
	bool doRight;
	bool doUp;
	bool doDown;

	float viewVelX;
	float viewVelY;

	float zoom;

	ToolBox toolBox;

	sf::View view;

	sf::RectangleShape previewBox;

	sf::Vector2f zoomPosition;
	sf::Vector2f corner1;
	sf::Vector2f corner2;

};

#endif
