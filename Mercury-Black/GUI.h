#ifndef GUI_H
#define GUI_H

#include <SFML\Graphics.hpp>
#include "GameEngine.h"

class GUI {

public:

	typedef void(*eventFunction)(GameEngine *);

	// Invokes the registered function
	void interact(GameEngine * engine);
	virtual void draw(sf::RenderWindow *) = 0;
	virtual bool isSelected(sf::Vector2f position) = 0;

	GUI() {}

protected:
	eventFunction m_funcPtr;

};

class GUI_Handler {

public:

	std::vector<GUI *> buttons;

	void addButton(GUI * button);
	void isSelected(sf::Vector2f position);
	void interact(sf::Vector2f position, GameEngine * engine);
	void draw(sf::RenderWindow * window);

};

#endif