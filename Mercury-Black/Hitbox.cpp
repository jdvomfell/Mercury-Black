#include "Hitbox.h"
#include <fstream>
void HitboxMap::addHitbox(std::string textureID, sf::RectangleShape box, int type) {
	
	if (box.getSize().x > 5 && box.getSize().y > 5) {
		Hitbox *hitbox = new Hitbox;

		hitbox->box = box;
		hitbox->type = type;
		printf("Added");
		for (select = map.lower_bound(textureID); select != map.upper_bound(textureID); select++) {
			if (box.getSize() == select->second->box.getSize()) {
				if (box.getPosition() == select->second->box.getPosition()) {
					return;
				}
			}	
		}
		select = map.insert(std::pair<std::string, Hitbox*>(textureID, hitbox));
	}
}

void HitboxMap::deleteHitbox(std::string textureID) {
	delete select->second;
	map.erase(select);
	select = map.lower_bound(textureID);
}

void HitboxMap::cycleHitbox(std::string textureID) {

	if (select != map.end()) {
		switch (select->second->type) {
		case COLLISIONBOX:
			select->second->box.setOutlineColor(sf::Color::Cyan);
			break;
		case HURTBOX:
			select->second->box.setOutlineColor(sf::Color::Magenta);
			break;
		case DEFENCEBOX:
			select->second->box.setOutlineColor(sf::Color::Green);
			break;
		case DAMAGEBOX:
			select->second->box.setOutlineColor(sf::Color::Red);
			break;
		}
	}

	if (select != map.upper_bound(textureID)) {
		printf("Upper\n");
		select++;
		//printf("Not upper");
	} else {
		printf("lower");
		select = map.lower_bound(textureID);
		//printf("Lower\n");
	}
	printf("ohh yes\n");
	if(select != map.end())
		select->second->box.setOutlineColor(sf::Color::Yellow);
	printf("Oh noooo\n");
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
		
		if (t == 0)
			rect.setOutlineColor(sf::Color::Cyan);
		else if (t == 1)
			rect.setOutlineColor(sf::Color::Magenta);
		else if (t == 2)
			rect.setOutlineColor(sf::Color::Green);
		else if (t == 3)
			rect.setOutlineColor(sf::Color::Red);
		addHitbox(s, rect, t);
	}

	printf("Loaded %d Hitboxes\n", numBox);
	ifstream.close();
}

void HitboxMap::draw(sf::RenderWindow *window, std::string textureID) {
	std::multimap<std::string, Hitbox*>::iterator it;
	
	for (it = map.lower_bound(textureID); it != map.upper_bound(textureID); it++) {
		window->draw(it->second->box);
	}

}