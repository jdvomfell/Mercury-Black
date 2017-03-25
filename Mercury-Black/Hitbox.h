#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#define	COLLISIONBOX 0
#define HURTBOX 1
#define DEFENCEBOX 2
#define DAMAGEBOX 3

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
	void draw(sf::RenderWindow *window, std::string textureID);
	void clean();
	
	std::multimap <std::string, Hitbox*> map;
	std::multimap <std::string, Hitbox*> collisionBoxs;
	std::multimap <std::string, Hitbox*> defenceBoxs;
	std::multimap <std::string, Hitbox*> damageBoxs;
	std::multimap <std::string, Hitbox*> hurtBoxs;

	std::multimap <std::string, Hitbox*>::iterator select;
};

#endif