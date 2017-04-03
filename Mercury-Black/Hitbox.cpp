#include "Hitbox.h"
#include <fstream>
void HitboxMap::addHitbox(std::string textureID, sf::RectangleShape box, int type) {
	
	std::multimap<std::string, Hitbox *>::iterator it;

	if (box.getSize().x > 5 && box.getSize().y > 5) {
		
		Hitbox *hitbox = new Hitbox;

		hitbox->box = box;
		hitbox->type = type;

		/* Check To See If Box Already Exists */

		for (it = map.lower_bound(textureID); it != map.upper_bound(textureID); it++) {

			if (box.getSize() == it->second->box.getSize()) {
				if (box.getPosition() == it->second->box.getPosition()) {
					return;
				}
			}	

		}

		it = map.insert(std::make_pair(textureID, hitbox));

		switch (type) {
		case HITBOXTYPE_HURT:
			hurtBoxes.insert(std::make_pair(textureID, hitbox));
			break;
		case HITBOXTYPE_COLLISION:
			collisionBoxes.insert(std::make_pair(textureID, hitbox));
			break;
		case HITBOXTYPE_DAMAGE:
			damageBoxes.insert(std::make_pair(textureID, hitbox));
			break;
		case HITBOXTYPE_DEFENCE:
			defenceBoxes.insert(std::make_pair(textureID, hitbox));
			break;
		}
	
	}

}

void HitboxMap::deleteHitbox(std::string textureID) {
	
	std::multimap<std::string, Hitbox *>::iterator it;

	if (select != map.end()) {

		for (it = collisionBoxes.begin(); it != collisionBoxes.end(); it++) {
			if (it->second == select->second) {
				collisionBoxes.erase(it);
				break;
			}
		}
		for (it = defenceBoxes.begin(); it != defenceBoxes.end(); it++) {
			if (it->second == select->second) {
				defenceBoxes.erase(it);
				break;
			}
		}
		for (it = damageBoxes.begin(); it != damageBoxes.end(); it++) {
			if (it->second == select->second) {
				damageBoxes.erase(it);
				break;
			}
		}
		for (it = hurtBoxes.begin(); it != hurtBoxes.end(); it++) {
			if (it->second == select->second) {
				hurtBoxes.erase(it);
				break;
			}
		}

		delete(select->second);

		map.erase(select);
	}

	select = map.end();
}

void HitboxMap::cycleHitbox(std::string textureID) {

	if (select != map.end()) {
		switch (select->second->type) {
		case HITBOXTYPE_COLLISION:
			select->second->box.setOutlineColor(sf::Color::Cyan);
			break;
		case HITBOXTYPE_HURT:
			select->second->box.setOutlineColor(sf::Color::Magenta);
			break;
		case HITBOXTYPE_DEFENCE:
			select->second->box.setOutlineColor(sf::Color::Green);
			break;
		case HITBOXTYPE_DAMAGE:
			select->second->box.setOutlineColor(sf::Color::Red);
			break;
		}
	}

	select++;

	if (select == map.upper_bound(textureID))
		select = map.lower_bound(textureID);

	if(select != map.end())
		select->second->box.setOutlineColor(sf::Color::Yellow);

	return;
}

void HitboxMap::save() {

	std::ofstream ofstream;
	std::multimap<std::string, Hitbox*>::iterator it;
	std::string hitBoxFilename = "hitbox.dat";
	sf::Vector2f position, size;

	ofstream.open(hitBoxFilename, std::ios::out | std::ios::binary);

	for (it = map.begin(); it != map.end(); it++) {
		size = it->second->box.getSize();
		position = it->second->box.getPosition();
		//printf("%s %d %f %f %f %f", it->first.c_str(), it->second->type,
			//position.x, position.y, size.x, size.y);

		ofstream
			<< it->first << std::endl
			<< it->second->type << std::endl
			<< position.x << std::endl
			<< position.y << std::endl
			<< size.x << std::endl
			<< size.y << std::endl;
	}

	ofstream.close();

} 

void HitboxMap::load() {
	
	std::ifstream ifstream;
	std::string hitBoxFilename = "hitbox.dat";
	sf::Vector2f pos, size;
	int t, numBox(0);
	std::string s;
	sf::RectangleShape rect;
	Hitbox * temp = NULL;
	sf::Color color;
	ifstream.open(hitBoxFilename, std::ios::in | std::ios::binary);

	if (!ifstream.is_open()) {
		printf("ERROR: Cannot Open Hitbox File (Possibly No File To Load)\n");
	//	return;
	}

	rect.setOutlineThickness(5);
	rect.setFillColor(sf::Color::Transparent);

	while (ifstream >> s >> t >> pos.x >> pos.y >> size.x >> size.y) {
		rect.setSize(size);
		rect.setPosition(pos);
		
		numBox++;
		
		if (t == HITBOXTYPE_COLLISION)
			rect.setOutlineColor(sf::Color::Cyan);
		else if (t == HITBOXTYPE_HURT)
			rect.setOutlineColor(sf::Color::Magenta);
		else if (t == HITBOXTYPE_DEFENCE)
			rect.setOutlineColor(sf::Color::Green);
		else if (t == HITBOXTYPE_DAMAGE)
			rect.setOutlineColor(sf::Color::Red);

		addHitbox(s, rect, t);

	}

	printf("Loaded %d Hitboxes\n", numBox);
	ifstream.close();
}

void HitboxMap::clean() {

	std::multimap<std::string, Hitbox *>::iterator it;

	for (it = map.begin(); it != map.end();) {
		delete(it->second);
		map.erase(it++);
	}

	for (it = collisionBoxes.begin(); it != collisionBoxes.end();)
		collisionBoxes.erase(it++);
	for (it = defenceBoxes.begin(); it != defenceBoxes.end();)
		defenceBoxes.erase(it++);
	for (it = damageBoxes.begin(); it != damageBoxes.end();)
		damageBoxes.erase(it++);
	for (it = hurtBoxes.begin(); it != hurtBoxes.end();)
		hurtBoxes.erase(it++);

}

void HitboxMap::draw(sf::RenderWindow *window, std::string textureID) {
	std::multimap<std::string, Hitbox*>::iterator it;
	
	for (it = map.lower_bound(textureID); it != map.upper_bound(textureID); it++) {
		window->draw(it->second->box);
	}

}

std::vector<sf::RectangleShape> HitboxMap::getHitboxes(std::string ID, HitboxType type) {

	std::vector<sf::RectangleShape> hitboxes;
	std::multimap<std::string, Hitbox *>::iterator it;

	switch (type) {
	
	case HITBOXTYPE_ALL:
		if ((it = map.find(ID)) != map.end()) {
			while (it != map.upper_bound(ID)) {
				hitboxes.push_back(it->second->box);
				it++;
			}
		}
	case HITBOXTYPE_HURT:
		if ((it = hurtBoxes.find(ID)) != hurtBoxes.end()) {
			while (it != hurtBoxes.upper_bound(ID)) {
				hitboxes.push_back(it->second->box);
				it++;
			}
		}
	case HITBOXTYPE_DAMAGE:
		if ((it = damageBoxes.find(ID)) != damageBoxes.end()) {
			while (it != damageBoxes.upper_bound(ID)) {
				hitboxes.push_back(it->second->box);
				it++;
			}
		}
	case HITBOXTYPE_DEFENCE:
		if ((it = defenceBoxes.find(ID)) != defenceBoxes.end()) {
			while (it != defenceBoxes.upper_bound(ID)) {
				hitboxes.push_back(it->second->box);
				it++;
			}
		}
	case HITBOXTYPE_COLLISION:
		if ((it = collisionBoxes.find(ID)) != collisionBoxes.end()) {
			while (it != collisionBoxes.upper_bound(ID)) {
				hitboxes.push_back(it->second->box);
				it++;
			}
		}
	}

	return hitboxes;

}

std::vector<sf::RectangleShape> HitboxMap::getFlippedHitboxes(std::string ID, HitboxType type) {

	std::vector<sf::RectangleShape> hitboxes;
	std::multimap<std::string, Hitbox *>::iterator it;

	hitboxes = getHitboxes(ID, type);

	for (size_t i = 0; i < hitboxes.size(); i++)
		hitboxes[i].setPosition(-(hitboxes[i].getGlobalBounds().left + hitboxes[i].getGlobalBounds().width), hitboxes[i].getGlobalBounds().top);

	return hitboxes;

}