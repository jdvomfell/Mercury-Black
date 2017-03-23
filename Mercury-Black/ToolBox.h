#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "Buttons.h"
#include <SFML/Graphics.hpp>

const enum Mode {
	PLATFORM = 0,
	OBJECT,
	EVENT,
	WATER
};

const enum Tool {

	PLACE = 0,
	BOX_PLACE,
	GROUND_PLACE,

};

class ToolBox {

public:

	ToolBox() {}
	ToolBox(GameEngine * engine);

	void highlightButtons(sf::Vector2i);
	/* Sets The View!!! */
	void clickButtons(sf::Vector2i);
	/* Sets The View!!! */
	bool contains(sf::Vector2i);

	void selectPlatform(sf::ConvexShape *);
	void selectObject(struct Object *);
	void selectWater(class Water *);

	void update();
	void render();

	void nextMode();
	void nextTool();

	Mode getMode();
	Tool getTool();

	/* Should Probably Be Private */

	sf::Text modeText;
	sf::Text toolText;
	sf::Text morphText1;
	sf::Text morphText2;
	sf::Text morphText3;
	sf::Text morphText4;

private:
	
	GameEngine * engine;

	Mode mode;
	Tool tool;

	sf::View toolBoxView;

	sf::RectangleShape toolBox;
	sf::RectangleShape toolBarShade;

	GUI_Handler guiHandler;

	IconButton boxTool;
	IconButton freeTool;
	IconButton groundTool;
	IconButton eventTool;
	IconButton objectTool;
	IconButton waterTool;

};

#endif