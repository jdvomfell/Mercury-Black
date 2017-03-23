#ifndef OBJECTMAP_H
#define OBJECTMAP_H

#include "TextureManager.h"

#include <map>

struct Object {

	int layer = 15;
	sf::Vector2f position = sf::Vector2f(0, 0);
	std::string textureName = "";

	sf::Sprite sprite = sf::Sprite();

	// False Means No Flip.
	bool flipx = false;
	// Degrees Object Is Rotated
	float rotate = 0;
	// Scaling Multiplier Of The Size (1 Is Default Scale);
	float scale = 1;

};

class ObjectMap {

public:

	void save();
	void load();
	void clean();

	void insert(Object * tempObject);
	void insert(sf::Vector2f position);
	void remove();

	void draw(sf::RenderWindow * window);
	void drawForeground(sf::RenderWindow * window);
	void drawBackground(sf::RenderWindow * window);
	void drawSuperBackground(sf::RenderWindow * window);

	std::map <float, Object *>::iterator findClosest(sf::Vector2f);
	std::map <float, Object *>::iterator findRight(float x);
	std::map <float, Object *>::iterator findLeft(float x);

	void nextObject();
	void prevObject();
	void selectObject(std::string textureName);

	void objectFlipx(Object*);
	void objectFlipy(Object*);

	void objectRotate(Object*, float);
	void objectScale(Object*, float);

	ObjectMap() {}
	ObjectMap(TextureManager *);

	TextureManager * textureManager;

	Object object;
	std::map<float, Object *> map;
	std::multimap<int, Object *> layerMap;
	std::map<float, Object *>::iterator selected;
};

#endif