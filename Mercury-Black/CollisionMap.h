#ifndef COLLISIONMAP_H
#define COLLISIONMAP_H

#include <SFML\Graphics.hpp>
#include <map>

class CollisionMap {

public:

	void insertCollisionPoint(sf::Vector2f position);
	void removeCollisionPoint();
	void findCollisionPoint(int x);
	void moveCollisionPoint();

	void updateVerticies();

	CollisionMap() { lines = sf::VertexArray(sf::LinesStrip, 0); }

	sf::VertexArray lines;
	std::map <float, sf::Vertex *> map;
	std::map <float, sf::Vertex *>::iterator selected;

};

#endif