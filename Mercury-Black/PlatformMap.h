#ifndef PLATFORMMAP_H
#define PLATFORMMAP_H

#include "TextureManager.h"
#include <map>

class PlatformMap {

	public:
		
		std::map<float, sf::ConvexShape *> map;
		std::map<float, sf::ConvexShape *>::iterator it;

		sf::Vector2f getEdgeNormal(int vertex, sf::ConvexShape * shape);
		sf::Vector2f getProjection(sf::Vector2f normal, sf::ConvexShape * shape);
		
		void add(sf::VertexArray * points);
		void remove();
		void clean();

		void draw(sf::RenderWindow * window);

		void save();
		void load();
		
		PlatformMap() {};

};

struct PlatPoint {

	sf::Vector2f point;
	PlatPoint * prevPoint;
	PlatPoint * nextPoint;

};

class PlatformPoints {

public:

	PlatPoint * current;
	PlatPoint * begin;

	void insert(sf::Vector2f point);
	void remove();

	void clean();

	void draw(sf::RenderWindow * window);
	void update();
	sf::VertexArray lines;

	PlatformPoints() { current = NULL; begin = NULL; lines = sf::VertexArray(sf::LinesStrip, 0); }

};

#endif 