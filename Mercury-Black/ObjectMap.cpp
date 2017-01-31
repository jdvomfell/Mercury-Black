#include "ObjectMap.h"

#include <fstream>

#include "TextureManager.h"

void ObjectMap::save() {

	std::ofstream ofstream;

	std::string objectFilename = "object.dat";
	ofstream.open(objectFilename, std::ios::out | std::ios::binary);

	for (std::map<float, Object *>::iterator it = map.begin(); it != map.end(); it++) {
		
		ofstream
			<< it->second->position.x << std::endl
			<< it->second->position.y << std::endl
			<< it->second->rotation << std::endl
			<< it->second->textureName << std::endl;

	}

	ofstream.close();

}

void ObjectMap::load() {

	std::string objectFilename = "object.dat";
	std::ifstream ifstream;

	Object * tempObject = NULL;

	std::string n;
	float x;
	float y;
	float r;
	std::map<float, Object *>::iterator it;

	map.clear();

	ifstream.open(objectFilename, std::ios::in | std::ios::binary);

	if (!ifstream.is_open()) {
		printf("ERROR: Cannot Open Object File (Possibly No File To Load)\n");
		return;
	}

	while (ifstream >> x >> y >> r >> n) {

		if (ifstream.eof())
			return;

		tempObject = new Object;

		object.position = sf::Vector2f(x, y);
		object.textureName = n;
		object.rotation = r;

		insert(object.position);

	}

	ifstream.close();

}

void ObjectMap::clean() {

	for (selected = map.begin(); selected != map.end(); selected++) {

		delete(selected->second);
		map.erase(selected++);

		selected = map.begin();

	}

}

void ObjectMap::insert(sf::Vector2f position) {

	object.sprite.setTexture(textureManager->textures.find(object.textureName)->second);
	object.sprite.setOrigin(object.sprite.getLocalBounds().width / 2, object.sprite.getLocalBounds().height / 2);
	
	object.position = position;
	object.sprite.setPosition(position);

	Object * tempObject = new Object(object);

	map.insert(std::make_pair(tempObject->position.x, tempObject));

}

void ObjectMap::remove() {

	if (selected == map.end() || selected->second == NULL)
		return;

	delete(selected->second);
	map.erase(selected);
	selected = map.end();

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
	object.position = sf::Vector2f(0, 0);
	object.rotation = 0.0f;

}