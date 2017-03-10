#ifndef OBJECTMAP_H
#define OBJECTMAP_H

#include "TextureManager.h"

#include <map>

struct Object {

	int layer;
	sf::Vector2f position;
	std::string textureName;

	sf::Sprite sprite;

	//key: flipx 0 means no flip.
	bool flipx = false;

	//rotate 'rotate' degrees
	float rotate = 0;

	//scaling as a multiplier of the size (1 is natural scale);
	float scale = 1;

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
	
	void flipx();
	void flipy();

	void rotate(float);
	void scale(float);

	ObjectMap() {}
	ObjectMap(TextureManager *);

	TextureManager * textureManager;

	Object object;
	std::map<float, Object *> map;
	std::multimap<int, Object *> layerMap;
	std::map<float, Object *>::iterator selected;
};

#endif