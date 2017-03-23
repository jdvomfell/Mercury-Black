#include "GUI.h"

bool GUI::isSelected(sf::Vector2f position) {

	if (text.getGlobalBounds().contains(position)) {

		return true;

	}

	return false;
}