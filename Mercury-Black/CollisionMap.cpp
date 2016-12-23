#include "CollisionMap.h"

void CollisionMap::insertCollisionPoint(sf::Vector2f position) {

	sf::Vertex * tempVertex;

	tempVertex = new sf::Vertex(position, sf::Color::Black);

	map.insert(std::make_pair(position.x, tempVertex));

	updateVerticies();

}

void CollisionMap::removeCollisionPoint() {

	if (selected == map.end() || selected->second == NULL)
		return;

	map.erase(selected);
	selected = map.end();

	updateVerticies();

}

void CollisionMap::findCollisionPoint(int x) {

	selected = map.upper_bound((float)x);

}

void CollisionMap::moveCollisionPoint() {

	if (selected->second == NULL)
		return;

}

void CollisionMap::updateVerticies() {

	std::map<float, sf::Vertex *>::iterator it;

	lines.clear();

	for (it = map.begin(); it != map.end(); it++) {

		lines.append(*(it->second));

	}

}