#include "Water.h"

#include <cmath>
#include <fstream>

#include "Entity.h"

#define PI 3.14159265f

#define PIXELS_PER_SPRING 20.0f
#define SPREAD 0.25f

void Spring::update() {

	/* Spring Constant - Determines Spring Stifness */
	float k = 0.015f;
	/* Dampening Factor - Determines How Fast Waves Die */
	float d = 0.05f;

	float targetHeightDistance = height - targetHeight;
	speed += (-k * targetHeightDistance) - speed * d;
	height += speed;

}

Spring::Spring(float x, float targetHeight) {

	this->x = x;

	this->speed = 0;

	this->height = targetHeight;
	this->targetHeight = targetHeight;

}

void WaterHandler::dealDamage(World * world) {

	for (std::map<float, Water *>::iterator it = map.begin(); it != map.end(); it++) {
		if (it->second->type == WATERTYPE_INK && it->second->rect.getGlobalBounds().contains(world->position[0].x, world->position[0].y)) {
			world->health[0].current -= 1;
			printf("E: %d", world->health[0].current);
		}
	}

}

void Water::update() {

	for (size_t i = 0; i < springs.size(); i++) {
		springs[i]->update();
		if (springs[i]->height > depth)
			springs[i]->height = depth;
	}

	/* Have Springs Effect Each Other */

	std::vector<float> leftDeltas(springs.size());
	std::vector<float> rightDeltas(springs.size());

	for (size_t i = 0; i < springs.size(); i++) {

		if (i > 0) {
			leftDeltas[i] = SPREAD * (springs[i]->height - springs[i - 1]->height);
			springs[i - 1]->speed += leftDeltas[i];
		}
		if (i < springs.size() - 1) {
			rightDeltas[i] = SPREAD * (springs[i]->height - springs[i + 1]->height);
			springs[i + 1]->speed += rightDeltas[i];
		}

	}

	for (size_t i = 0; i < springs.size(); i++) {

		if (i > 0)
			springs[i - 1]->height += leftDeltas[i];
		if (i < springs.size() - 1)
			springs[i + 1]->height += rightDeltas[i];

	}

	springs[0]->height = targetHeight;
	springs[springs.size() - 1]->height = targetHeight;

	for (size_t i = 0; i < springs.size(); i++) {

		waterShape[i * 2].position = sf::Vector2f(springs[i]->x, springs[i]->height);

	}

}

void Water::draw(sf::RenderWindow * window) {

	window->draw(waterShape);

}

void Water::splash(size_t index, float speed) {

	if (index >= 0 && index < springs.size()) {
		springs[index]->speed = speed;
		printf("splash");
	}

}

Water::Water(sf::Vector2f topLeft, sf::Vector2f bottomRight, WaterType type) {

	Spring * spring;

	this->topLeft = topLeft;
	this->bottomRight = bottomRight;

	this->type = type;
	rect = sf::RectangleShape(bottomRight - topLeft);
	rect.move(topLeft);

	x = topLeft.x;
	depth = bottomRight.y;
	length = (bottomRight.x - topLeft.x);
	targetHeight = topLeft.y;

	float numSprings = length / PIXELS_PER_SPRING;

	for (int i = 0; i < numSprings; i++) {
		spring = new Spring(topLeft.x + length * ((float)i / (float)numSprings), topLeft.y);
		springs.push_back(spring);
	}

	/* Insert Last Spring */

	spring = new Spring(topLeft.x + length, topLeft.y);
	springs.push_back(spring);

	/* Create Vertex Array Of Traiangles For Rendering */

	waterShape = sf::VertexArray(sf::TriangleStrip, springs.size() * 2);

	for (size_t i = 0; i < springs.size(); i++) {
		/* Make Water Surface */
		waterShape[i * 2].position = sf::Vector2f(springs[i]->x, springs[i]->height);
		if (type == WATERTYPE_INK) {
			waterShape[i * 2].color = sf::Color(0, 0, 0, 175);
		}
		else if(type == WATERTYPE_WATER){
			waterShape[i * 2].color = sf::Color(66, 194, 244, 175);
		}
		/* Make Bottom Of Water */
		waterShape[i * 2 + 1].position = sf::Vector2f(springs[i]->x, depth);
		if (type == WATERTYPE_INK) {
			waterShape[i * 2 + 1].color = sf::Color::Black;
		}
		else if (type == WATERTYPE_WATER) {
			waterShape[i * 2].color = sf::Color(35, 93, 132, 0);
		}
	}

}

void Water::clean() {

	for (size_t i = 0; i < springs.size(); i++) {
		delete(springs[i]);
	}

}

void WaterHandler::insert(sf::Vector2f topLeft, sf::Vector2f bottomRight, WaterType type) {

	Water * water = new Water(topLeft, bottomRight, type);

	map.insert(std::make_pair(topLeft.x, water));

}

void WaterHandler::updateWaves(float dt) {

	waveOffset += dt;
	if (waveOffset > 2 * PI)
		waveOffset -= 2 * PI;

	std::map<float, Water *>::iterator it;
	for (it = map.begin(); it != map.end(); it++) {

		for (size_t i = 1; i < it->second->springs.size() - 1; i++) {

			it->second->springs[i]->targetHeight = it->second->targetHeight + sin(it->second->springs[i]->x + waveOffset * 10) * 100;

		}

	}

}

void WaterHandler::update() {

	std::map<float, Water *>::iterator it;
	for (it = map.begin(); it != map.end(); it++)
		it->second->update();

}

void WaterHandler::draw(sf::RenderWindow * window) {

	std::map<float, Water *>::iterator it;
	for (it = map.begin(); it != map.end(); it++) {
		it->second->draw(window);
	}

}

void WaterHandler::load() {
	
	std::string objectFilename = "water.dat";
	std::ifstream ifstream;

	float x1, x2;
	float y1, y2;
	int type;

	int numObjects = 0;

	clean();

	ifstream.open(objectFilename, std::ios::in | std::ios::binary);

	if (!ifstream.is_open()) {
		printf("ERROR: Cannot Open Object File (Possibly No File To Load)\n");
		return;
	}

	while (ifstream >> x1 >> y1 >> x2 >> y2 >> type) {

		if (ifstream.eof())
			return;

		numObjects++;

		insert(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2), (WaterType)type);

	}

	printf("Loaded %d Bodies Of Water\n", numObjects);

	ifstream.close();
}

void WaterHandler::save() {

	std::ofstream ofstream;

	std::string objectFilename = "water.dat";
	ofstream.open(objectFilename, std::ios::out | std::ios::binary);

	for (std::map<float, Water *>::iterator it = map.begin(); it != map.end(); it++) {

		ofstream
			<< it->second->topLeft.x << " "
			<< it->second->topLeft.y << " "
			<< it->second->bottomRight.x << " "
			<< it->second->bottomRight.y << " "
			<< it->second->type << std::endl;

	}

	ofstream.close();

}

void WaterHandler::clean() {

	for (std::map<float, Water *>::iterator it = map.begin(); it != map.end();) {

		it->second->clean();
		delete(it->second);
		map.erase(it++);

	}

}

std::map <float, Water *>::iterator WaterHandler::findRight(float x) {

	return map.lower_bound(x);

}

std::map <float, Water *>::iterator WaterHandler::findLeft(float x) {

	if (map.lower_bound(x) != map.begin())
		return --map.lower_bound(x);
	else
		return map.end();

}

std::map <float, Water *>::iterator WaterHandler::findClosest(sf::Vector2f position) {

	float distanceLeft;
	float distanceRight;

	std::map<float, Water *>::iterator left = findLeft(position.x);
	std::map<float, Water *>::iterator right = findRight(position.x);

	if (left != map.end() && right != map.end()) {
		distanceLeft = sqrt(pow((position.x - left->second->x), 2) + pow((position.y - left->second->targetHeight), 2));
		distanceRight = sqrt(pow((right->second->x - position.x), 2) + pow((right->second->targetHeight - position.y), 2));
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

void WaterHandler::remove() {

	if (selected == map.end())
		return;

	delete(selected->second);
	map.erase(selected);

	selected = map.end();

}