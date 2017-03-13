#ifndef BUTTONS_H
#define BUTTONS_H

#include "GUI.h"
#include "Buttons.h"

class TextButton : public GUI {

public:

    TextButton() {}
    TextButton(std::string name, float x, float y, int size, sf::Font * font, eventFunction funcPtr);
	bool isSelected(sf::Vector2f position);
	void draw(sf::RenderWindow *);
	// A destructor
    ~TextButton(){ m_funcPtr = NULL; }

	sf::Text text;

};

class IconButton : public GUI {

public:

	IconButton() {}
	IconButton(float x, float y, sf::Texture * texture, eventFunction funcPtr);
	bool isSelected(sf::Vector2f position);
	void draw(sf::RenderWindow *);
	// A destructor
	~IconButton() { m_funcPtr = NULL; }

	sf::Sprite sprite;

};

void changeToGame(GameEngine * engine);
void popState(GameEngine * engine);
void changeToEditor(GameEngine * engine);
void changeToHitboxEditor(GameEngine * engine);
void changeToMainMenu(GameEngine * engine);
void quitGame(GameEngine * engine);
void doNothing(GameEngine * engine);
#endif