#include "CollisionMap.h"
#include <fstream>

void CollisionMap::clean() {

	for (selected = map.begin(); selected != map.end();) {

		delete(selected->second);
		map.erase(selected++);

	}

}

void CollisionMap::insert(sf::Vector2f position) {

	sf::Vertex * tempVertex;

	tempVertex = new sf::Vertex(position, sf::Color::Black);

	map.insert(std::make_pair(position.x, tempVertex));

	updateVerticies();

}

void CollisionMap::remove() {

	if (selected == map.end() || selected->second == NULL)
		return;

	delete(selected->second);
	map.erase(selected);
	selected = map.end();

	updateVerticies();

}

std::map <float, sf::Vertex *>::iterator CollisionMap::findRight(float x) {

	return map.lower_bound(x);

}

std::map <float, sf::Vertex *>::iterator CollisionMap::findLeft(float x) {

	if (map.lower_bound(x) != map.begin())
		return --map.lower_bound(x);
	else
		return map.end();

}

std::map <float, sf::Vertex *>::iterator CollisionMap::findClosest(sf::Vector2f position) {

	float distanceLeft;
	float distanceRight;

	std::map<float, sf::Vertex *>::iterator left = findLeft(position.x);
	std::map<float, sf::Vertex *>::iterator right = findRight(position.x);

	if (left != map.end() && right != map.end()) {
		distanceLeft = sqrt(pow((position.x - left->second->position.x), 2) + pow((position.y - left->second->position.y), 2));
		distanceRight = sqrt(pow((right->second->position.x - position.x), 2) + pow((right->second->position.y - position.y), 2));
		if (distanceLeft < distanceRight)
			return left;
		else
			return right;
	}
	
	else if (left == map.end())
		return right;
	
	else if (right == map.end())
		return left;
	
	else
		return map.end();

}

void CollisionMap::move() {

	if (selected->second == NULL)
		return;

}

void CollisionMap::save() {

	std::ofstream ofstream;

	std::string pointFilename = "point.dat";
	ofstream.open(pointFilename, std::ios::out | std::ios::binary);

	for (std::map<float, sf::Vertex *>::iterator it = map.begin(); it != map.end(); it++)
		ofstream.write((char*)it->second, sizeof(sf::Vertex));

	ofstream.close();

}

void CollisionMap::load() {

	std::string pointFilename = "point.dat";
	std::ifstream ifstream;

	std::map<float, sf::Vertex *>::iterator it;
	sf::Vertex * tempVertex;

	map.clear();

	ifstream.open(pointFilename, std::ios::in | std::ios::binary);

	while (ifstream.peek() != EOF) {

		tempVertex = new sf::Vertex;

		ifstream.read((char*)tempVertex, sizeof(sf::Vertex));

		map.insert(std::make_pair(tempVertex->position.x, tempVertex));

	}

	lines.clear();
	
	for (it = map.begin(); it != map.end(); it++)
		lines.append(*(it->second));
	
	ifstream.close();

}

void CollisionMap::updateVerticies() {

	std::map<float, sf::Vertex *>::iterator it;

	lines.clear();

	for (it = map.begin(); it != map.end(); it++) {

		lines.append(*(it->second));

	}

}