#ifndef OBJECTMAP_H
#define OBJECTMAP_H

#include "TextureManager.h"

#include <map>

struct Object {

	float scale;
	float rotation;
	std::string type;
	sf::Vector2f position;

};

class ObjectMap {

public:

	void save();
	void load();

	void add();
	void remove();

	void changeObject();
	void selectObject();

	ObjectMap() {}
	ObjectMap(TextureManager *);

	TextureManager * textureManager;

	Object object;
	std::map<float, Object> objectMap;

};

#endif