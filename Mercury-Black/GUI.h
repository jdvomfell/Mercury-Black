#ifndef GUI_H
#define GUI_H

#include <SFML\Graphics.hpp>

class GUI {

public:
	
	bool isSelected(int mouseX, int mouseY);

	virtual void interact() {};

	sf::Text text;
	
	GUI() {}

};

#endif