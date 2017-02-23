#ifndef OBJECTMAP_H
#define OBJECTMAP_H

#include "TextureManager.h"

#include <map>

struct Object {

	sf::Vector2f position;
	std::string textureName;

	sf::Sprite sprite;

};

class ObjectMap {

public:

	void save();
	void load();
	void clean();

	void insert(sf::Vector2f position);
	void remove();

	void draw(sf::RenderWindow * window);

	std::map <float, Object *>::iterator findClosest(sf::Vector2f);
	std::map <float, Object *>::iterator findRight(float x);
	std::map <float, Object *>::iterator findLeft(float x);

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