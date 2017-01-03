#include "CollisionMap.h"
#include <fstream>

void CollisionMap::clean() {

	std::map<float, sf::Vertex *>::iterator it;

	it = map.begin();
	while (it != map.end()) {

		delete(it->second);
		map.erase(it++);

	}

}

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

void CollisionMap::findCollisionPoint(float x) {

	selected = map.upper_bound(x);

}

void CollisionMap::moveCollisionPoint() {

	if (selected->second == NULL)
		return;

}

void CollisionMap::save() {

	// Save Points for collision map

	std::ofstream ofstream;

	std::string pointFilename = "point.dat";
	ofstream.open(pointFilename, std::ios::out | std::ios::binary);

	for (std::map<float, sf::Vertex *>::iterator it = map.begin(); it != map.end(); it++)
		ofstream.write((char*)it->second, sizeof(sf::Vertex));

	ofstream.close();

	// Save objects for object map

	/*std::string objectFilename = "object.dat";
	ofstream.open(objectFilename);

	std::multimap<int, sf::Sprite*>::iterator oit;
	for (oit = objectMap.begin(); oit != objectMap.end(); oit++) {
	ofstream << oit->second;
	}

	ofstream.close();*/

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