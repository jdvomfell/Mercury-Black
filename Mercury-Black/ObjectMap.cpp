#include "ObjectMap.h"

#include "TextureManager.h"

void ObjectMap::save() {

}

void ObjectMap::load() {

}

void ObjectMap::add() {

}

void ObjectMap::remove() {

}

void ObjectMap::changeObject() {
	
	if (textureManager->textures.find(object.type) == --textureManager->textures.end())
		object.type = textureManager->textures.begin()->first;
	else
		object.type = (++textureManager->textures.find(object.type))->first;

}

void ObjectMap::selectObject() {

}

ObjectMap::ObjectMap(TextureManager * textureManager) {

	this->textureManager = textureManager;
	object.type = this->textureManager->textures.begin()->first;

}