#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

class HealthBar {

public:

	sf::RectangleShape rect;

	HealthBar(sf::View * view, int health, int maxHealth);

	void update(sf::View * view, int health, int maxHealth);
	void draw(sf::RenderWindow * window);

};

#endif