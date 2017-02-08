#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include <vector>

class Hitboxes {

	std::vector<sf::RectangleShape *> attackBoxes;
	std::vector<sf::RectangleShape *> hurtBoxes;

};

class HitboxMap {

	std::map<std::string, Hitboxes> map;

	void addHitboxes(std::string ID, Hitboxes);

	void addHitbox(std::string ID, sf::FloatRect hitbox);
	
	void removeHitbox(std::string ID, );

};

#endif