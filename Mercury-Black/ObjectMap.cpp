#include "ObjectMap.h"

#include "TextureManager.h"

void ObjectMap::save() {

}

void ObjectMap::load() {

}

void ObjectMap::clean() {

	for (selected = map.begin(); selected != map.end(); selected++) {

		delete(selected->second);
		map.erase(selected);

		selected = map.begin();

	}

}

void ObjectMap::insert(sf::Vector2f position) {

	this->object.position = position;

	this->object.sprite.setPosition(position);
	this->object.sprite.setTexture(textureManager->textures.find(this->object.textureName)->second);

	Object * object = new Object(this->object);

	map.insert(std::make_pair(object->position.x, object));

}

void ObjectMap::remove(float xPos) {

	if (map.find(xPos) != map.end()) {

		delete(map.find(xPos)->second);
		map.erase(xPos);
	
	}

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