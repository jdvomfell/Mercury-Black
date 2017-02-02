#ifndef GUI_H
#define GUI_H

#include <SFML\Graphics.hpp>
#include "GameEngine.h"

class GUI {

public:
	
	bool isSelected(sf::Vector2f position);

	virtual void interact(GameEngine * engine) {};

	sf::Text text;
	
	GUI() {}

};

#endif