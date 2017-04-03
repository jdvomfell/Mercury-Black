#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

const enum HitboxType {

	HITBOXTYPE_ALL,
	HITBOXTYPE_COLLISION,
	HITBOXTYPE_DEFENCE,
	HITBOXTYPE_DAMAGE,
	HITBOXTYPE_HURT

};

struct Hitbox {
public:
	sf::RectangleShape box;
	int type;
};

class HitboxMap {

public:
	
	void addHitbox(std::string textureID, sf::RectangleShape box, int type);
	void deleteHitbox(std::string textureID);
	void cycleHitbox(std::string textureID);
	
	void save();
	void load();
	void clean();

	void draw(sf::RenderWindow *window, std::string textureID);

	std::vector<sf::RectangleShape> getHitboxes(std::string textureID, HitboxType type);
	std::vector<sf::RectangleShape> getFlippedHitboxes(std::string textureID, HitboxType type);
	
	std::multimap <std::string, Hitbox*> map;
	std::multimap <std::string, Hitbox*> collisionBoxes;
	std::multimap <std::string, Hitbox*> defenceBoxes;
	std::multimap <std::string, Hitbox*> damageBoxes;
	std::multimap <std::string, Hitbox*> hurtBoxes;

	std::multimap <std::string, Hitbox*>::iterator select;
};

#endif