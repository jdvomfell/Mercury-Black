#ifndef COLLISIONMAP_H
#define COLLISIONMAP_H

#include <SFML\Graphics.hpp>
#include <map>

class CollisionMap {

public:

	void clean();
	void save();
	void load();

	std::map <float, sf::Vertex *>::iterator findClosest(float x);
	std::map <float, sf::Vertex *>::iterator findRight(float x);
	std::map <float, sf::Vertex *>::iterator findLeft(float x);
	void insert(sf::Vector2f position);
	void remove();
	void move();

	void updateVerticies();

	CollisionMap() { lines = sf::VertexArray(sf::LinesStrip, 0); }

	sf::VertexArray lines;
	std::map <float, sf::Vertex *> map;
	std::map <float, sf::Vertex *>::iterator selected;

};

#endif