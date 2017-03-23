#ifndef PLATFORMMAP_H
#define PLATFORMMAP_H

#include "TextureManager.h"
#include <map>

struct PlatPoint {

	sf::Vector2f point;
	PlatPoint * prevPoint;
	PlatPoint * nextPoint;

};

class PlatformPoints {

public:

	PlatPoint * current;
	PlatPoint * begin;

	bool isEmpty();

	void insert(sf::Vector2f point);
	void remove();

	void clean();

	void draw(sf::RenderWindow * window);
	void update();

	sf::VertexArray lines;

	PlatformPoints() { current = NULL; begin = NULL; lines = sf::VertexArray(sf::LinesStrip, 0); }

};

class PlatformMap {

	public:
		
		std::map<float, sf::ConvexShape *> map;
		std::map<float, sf::ConvexShape *>::iterator selected;

		PlatformPoints platformPoints;

		sf::Vector2f getEdgeNormal(int vertex, sf::ConvexShape * shape);
		sf::Vector2f getProjection(sf::Vector2f normal, sf::ConvexShape * shape);
		
		std::map<float, sf::ConvexShape *>::iterator insert();
		void insertBox(sf::Vector2f topLeft, sf::Vector2f bottomRight);
		void insertGround(sf::Vector2f groundPosition);

		std::map <float, sf::ConvexShape *>::iterator findClosest(sf::Vector2f);
		std::map <float, sf::ConvexShape *>::iterator findRight(float x);
		std::map <float, sf::ConvexShape *>::iterator findLeft(float x);

		void remove();
		void clean();

		void draw(sf::RenderWindow * window);

		void save();
		void load();
		
		PlatformMap() { selected = map.end(); }

};

#endif 