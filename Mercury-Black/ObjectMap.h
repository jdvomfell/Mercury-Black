#ifndef OBJECTMAP_H
#define OBJECTMAP_H

#include "TextureManager.h"

#include <map>

struct Object {

	float x;
	float y;
	float rotation;
	float scale;
	std::string type;

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