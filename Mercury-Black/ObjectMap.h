#ifndef OBJECTMAP_H
#define OBJECTMAP_H

#include "TextureManager.h"

#include <map>

struct Object {

	float scale;
	float rotation;
	sf::Sprite sprite;
	sf::Vector2f position;
	std::string textureName;

};

class ObjectMap {

public:

	void save();
	void load();
	void clean();

	void insert(sf::Vector2f position);
	void remove(float xPos);

	void changeObject();
	void selectObject(std::string textureName);

	ObjectMap() {}
	ObjectMap(TextureManager *);

	TextureManager * textureManager;

	Object object;
	std::map<float, Object *> map;
	std::map<float, Object *>::iterator selected;

};

#endif