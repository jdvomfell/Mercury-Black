#ifndef GUI_H
#define GUI_H

#include <SFML\Graphics.hpp>
#include "GameEngine.h"

class GUI {

public:
	
	bool isSelected(int mouseX, int mouseY);

	virtual void interact(GameEngine * engine) {};

	sf::Text text;
	
	GUI() {}

};

#endif