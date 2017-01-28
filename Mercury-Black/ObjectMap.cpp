#include "ObjectMap.h"

#include "TextureManager.h"

void ObjectMap::save() {

}

void ObjectMap::load() {

}

void ObjectMap::clean() {

	for (selected = map.begin(); selected != map.end(); selected++) {

		delete(selected->second);
		map.erase(selected++);

		selected = map.begin();

	}

}

void ObjectMap::insert(sf::Vector2f position) {

	this->object.sprite.setTexture(textureManager->textures.find(this->object.textureName)->second);
	object.sprite.setOrigin(object.sprite.getLocalBounds().width / 2, object.sprite.getLocalBounds().height / 2);
	
	this->object.position = position;
	this->object.sprite.setPosition(position);

	Object * object = new Object(this->object);

	map.insert(std::make_pair(object->position.x, object));

}

void ObjectMap::remove() {

	printf("ENTRY\n");

	if (selected == map.end() || selected->second == NULL)
		return;

	printf("HI\n");

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

}