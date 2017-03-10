#include "ObjectMap.h"

#include <fstream>

#include "TextureManager.h"

void ObjectMap::save() {

	std::ofstream ofstream;

	std::string objectFilename = "object.dat";
	ofstream.open(objectFilename, std::ios::out | std::ios::binary);

	for (std::map<float, Object *>::iterator it = map.begin(); it != map.end(); it++) {
		
		printf("%d, %f, %f, %s\n", it->second->layer, it->second->position.x, it->second->position.y, it->second->textureName.c_str());

		ofstream
			<< it->second->layer << std::endl
			<< it->second->position.x << std::endl
			<< it->second->position.y << std::endl
			<< it->second->textureName << std::endl;

	}

	ofstream.close();

}

void ObjectMap::load() {

	std::string objectFilename = "object.dat";
	std::ifstream ifstream;

	Object * tempObject = NULL;

	float x;
	float y;
	int layer;
	std::string name;

	int numObjects = 0;

	clean();

	ifstream.open(objectFilename, std::ios::in | std::ios::binary);

	if (!ifstream.is_open()) {
		printf("ERROR: Cannot Open Object File (Possibly No File To Load)\n");
		return;
	}

	while (ifstream >> layer >> x >> y >> name) {

		if (ifstream.eof())
			return;

		numObjects++;

		object.layer = layer;
		object.position = sf::Vector2f(x, y);
		object.textureName = name;

		insert(object.position);

	}

	printf("Loaded %d Objects\n", numObjects);

	ifstream.close();

}

void ObjectMap::clean() {

	std::map<float, Object *>::iterator it;
	it = map.begin();

	while(it != map.end()) {

		delete(it->second);
		
		map.erase(it++);

	}

	std::multimap<int, Object *>::iterator lit;
	lit = layerMap.begin();

	while (lit != layerMap.end()) {

		layerMap.erase(lit++);

	}

	selected = map.end();

}

void ObjectMap::insert(sf::Vector2f position) {

	if (textureManager->textures.find(object.textureName) == textureManager->textures.end()) {
		printf("Error: Could Not Insert Object To Map, Unidentified Texture Name: %s\n", object.textureName.c_str());
		return;
	}

	Object * tempObject = new Object;

	tempObject->textureName = object.textureName;
	tempObject->layer = object.layer;
	tempObject->sprite.setTexture(textureManager->textures.find(object.textureName)->second);
	tempObject->sprite.setOrigin(tempObject->sprite.getLocalBounds().width / 2, tempObject->sprite.getLocalBounds().height / 2);

	tempObject->position = position;
	tempObject->sprite.setPosition(position);

	map.insert(std::make_pair(tempObject->position.x, tempObject));
	layerMap.insert(std::make_pair(tempObject->layer, tempObject));

}

void ObjectMap::remove() {

	if (selected == map.end() || selected->second == NULL)
		return;

	std::multimap<int, Object *>::iterator lit;
	lit = layerMap.begin();

	while (lit != layerMap.end()) {
		if (lit->second == selected->second) {
			layerMap.erase(lit);
			break;
		}
		lit++;
	}

	delete(selected->second);
	map.erase(selected);
	selected = map.end();

}

void ObjectMap::draw(sf::RenderWindow * window) {

	std::multimap<int, Object *>::iterator it;
	for (it = layerMap.begin(); it != layerMap.end(); it++)
		window->draw(it->second->sprite);

	return;

}

void ObjectMap::drawForeground(sf::RenderWindow * window) {

	std::multimap<int, Object *>::iterator it;
	for (it = layerMap.lower_bound(30); it != layerMap.end(); it++)
		window->draw(it->second->sprite);

	return;

}

void ObjectMap::drawBackground(sf::RenderWindow * window) {

	std::multimap<int, Object *>::iterator it;
	for (it = layerMap.begin(); it != layerMap.lower_bound(30); it++)
		window->draw(it->second->sprite);

	return;

}

std::map <float, Object *>::iterator ObjectMap::findRight(float x) {

	return map.lower_bound(x);

}

std::map <float, Object *>::iterator ObjectMap::findLeft(float x) {

	if (map.lower_bound(x) != map.begin())
		return --map.lower_bound(x);
	else
		return map.end();

}

std::map <float, Object *>::iterator ObjectMap::findClosest(sf::Vector2f position) {

	float distanceLeft;
	float distanceRight;

	std::map<float, Object *>::iterator left = findLeft(position.x);
	std::map<float, Object *>::iterator right = findRight(position.x);

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

void ObjectMap::changeObject() {
	
	if (textureManager->textures.find(object.textureName) == --textureManager->textures.end())
		object.textureName = textureManager->textures.begin()->first;
	else if (textureManager->textures.find(object.textureName) == textureManager->textures.end())
		object.textureName = textureManager->textures.begin()->first;
	else
		object.textureName = (++textureManager->textures.find(object.textureName))->first;

}

void ObjectMap::selectObject(std::string textureName) {

	if (textureManager->textures.find(textureName) != textureManager->textures.end())
		object.textureName = textureName;
	else
		object.textureName = textureManager->textures.begin()->first;

}

ObjectMap::ObjectMap(TextureManager * textureManager) {

	this->textureManager = textureManager;
	object.textureName = this->textureManager->textures.begin()->first;
	object.layer = 0;
	object.position = sf::Vector2f(0, 0);

}