#ifndef BUTTONS_H
#define BUTTONS_H

#include "GUI.h"

class GUI_NewGame : public GUI {

public:

	GUI_NewGame() {}
	GUI_NewGame(float x, float y, sf::Color color, int size, sf::Font * font);

};

class GUI_LoadGame : public GUI {

public:

	GUI_LoadGame() {}
	GUI_LoadGame(float x, float y, sf::Color color, int size, sf::Font * font);

};

class GUI_Editor : public GUI {

public:

	GUI_Editor() {}
	GUI_Editor(float x, float y, sf::Color color, int size, sf::Font * font);

};

class GUI_Options : public GUI {

public:

	GUI_Options() {}
	GUI_Options(float x, float y, sf::Color color, int size, sf::Font * font);

};

class GUI_Quit : public GUI {

public:

	GUI_Quit() {}
	GUI_Quit(float x, float y, sf::Color color, int size, sf::Font * font);

};

#endif