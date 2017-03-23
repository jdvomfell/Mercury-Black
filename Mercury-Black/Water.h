#ifndef WATER_H
#define WATER_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <map>

class Spring {

public:

	void update();

	Spring(float x, float targetHeight);

	float x;

	float speed;
	float height;
	float targetHeight;

};

class Water {

public:

	void splash(size_t index, float speed);

	void update();
	void draw(sf::RenderWindow * window);

	void clean();

	Water(sf::Vector2f corner1, sf::Vector2f corner2);

	//private:

	sf::VertexArray waterShape;
	std::vector<Spring *> springs;

	sf::Vector2f topLeft;
	sf::Vector2f bottomRight;

	float targetHeight;
	float x;
	float length;
	float depth;

};

class WaterHandler {

public:

	void insert(sf::Vector2f topLeft, sf::Vector2f);

	void updateWaves(float dt);
	void update();
	void draw(sf::RenderWindow * window);

	void clean();

	void save();
	void load();

	//private:

	float waveOffset;
	std::map<float, Water *> map;

};

#endif