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
			<< it->second->flipx << std::endl
			<< it->second->rotate << std::endl
			<< it->second->scale << std::endl
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

	bool flipx;
	float rotate;
	float scale;
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

	while (ifstream >> flipx >> rotate >> scale >> layer >> x >> y >> name) {

		if (ifstream.eof())
			return;

		numObjects++;

		tempObject = new Object;

		tempObject->flipx = !flipx;
		tempObject->rotate = rotate;
		tempObject->scale = scale;
		tempObject->layer = layer;
		tempObject->position = sf::Vector2f(x, y);
		tempObject->textureName = name;
		
		tempObject->sprite.setTexture(textureManager->textures.find(tempObject->textureName)->second);
		tempObject->sprite.setOrigin(tempObject->sprite.getLocalBounds().width / 2, tempObject->sprite.getLocalBounds().height / 2);
		tempObject->sprite.setPosition(tempObject->position);
		tempObject->sprite.setColor(sf::Color::White);

		objectFlipx(tempObject);
		objectRotate(tempObject, 0);
		objectScale(tempObject, 0);

		insert(tempObject);

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

void ObjectMap::insert(Object * tempObject) {

	map.insert(std::make_pair(tempObject->position.x, tempObject));
	layerMap.insert(std::make_pair(tempObject->layer, tempObject));

}

void ObjectMap::insert(sf::Vector2f position) {

	if (textureManager->textures.find(object.textureName) == textureManager->textures.end()) {
		printf("Error: Could Not Insert Object To Map, Unidentified Texture Name: %s\n", object.textureName.c_str());
		return;
	}

	Object * tempObject = new Object(object);

	tempObject->flipx = !object.flipx;
	tempObject->rotate = object.rotate;
	tempObject->scale = object.scale;

	tempObject->textureName = object.textureName;
	tempObject->layer = object.layer;
	tempObject->sprite.setTexture(textureManager->textures.find(object.textureName)->second);
	tempObject->sprite.setOrigin(tempObject->sprite.getLocalBounds().width / 2, tempObject->sprite.getLocalBounds().height / 2);

	tempObject->position = position;
	tempObject->sprite.setPosition(position);
	tempObject->sprite.setColor(sf::Color::White);

	map.insert(std::make_pair(tempObject->position.x, tempObject));
	layerMap.insert(std::make_pair(tempObject->layer, tempObject));

	objectFlipx(tempObject);
	objectRotate(tempObject, 0);
	objectScale(tempObject, 0);

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
	for (it = layerMap.lower_bound(20); it != layerMap.end(); it++)
		window->draw(it->second->sprite);

	return;

}

void ObjectMap::drawBackground(sf::RenderWindow * window) {

	std::multimap<int, Object *>::iterator it;
	for (it = layerMap.lower_bound(10); it != layerMap.lower_bound(20); it++)
		window->draw(it->second->sprite);

	return;

}

void ObjectMap::drawSuperBackground(sf::RenderWindow * window) {

	std::multimap<int, Object *>::iterator it;
	for (it = layerMap.begin(); it != layerMap.lower_bound(10); it++)
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

void ObjectMap::nextObject() {
	
	if (textureManager->textures.find(object.textureName) == --textureManager->textures.end())
		object.textureName = textureManager->textures.begin()->first;
	else if (textureManager->textures.find(object.textureName) == textureManager->textures.end())
		object.textureName = textureManager->textures.begin()->first;
	else
		object.textureName = (++textureManager->textures.find(object.textureName))->first;

	object.sprite.setTexture(textureManager->textures.at(object.textureName));
	object.sprite.setTextureRect(sf::IntRect(0, 0, textureManager->textures.at(object.textureName).getSize().x, textureManager->textures.at(object.textureName).getSize().y));
	object.sprite.setOrigin(object.sprite.getGlobalBounds().width / 2, object.sprite.getGlobalBounds().height / 2);
	object.sprite.setColor(sf::Color(0, 0, 0, 100));

}

void ObjectMap::prevObject() {

	if(textureManager->textures.find(object.textureName) == textureManager->textures.begin())
		object.textureName = (--textureManager->textures.end())->first;
	else if(textureManager->textures.find(object.textureName) == textureManager->textures.end())
		object.textureName = textureManager->textures.begin()->first;
	else
		object.textureName = (--textureManager->textures.find(object.textureName))->first;

	object.sprite.setTexture(textureManager->textures.at(object.textureName));
	object.sprite.setTextureRect(sf::IntRect(0, 0, textureManager->textures.at(object.textureName).getSize().x, textureManager->textures.at(object.textureName).getSize().y));
	object.sprite.setOrigin(object.sprite.getGlobalBounds().width / 2, object.sprite.getGlobalBounds().height / 2);
	object.sprite.setColor(sf::Color(0, 0, 0, 100));

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
	object.sprite.setTexture(this->textureManager->textures.begin()->second);
	object.layer = 15;
	object.position = sf::Vector2f(0, 0);

}

void ObjectMap::objectFlipx(Object* object) {

	if (object == NULL) return;

	object->flipx = !object->flipx;

	if (object->flipx == true) {
		object->sprite.setTextureRect(sf::IntRect((int) object->sprite.getLocalBounds().width, 0, (int) -object->sprite.getLocalBounds().width, (int) object->sprite.getLocalBounds().height));
	}

	else {
		object->sprite.setTextureRect(sf::IntRect(0, 0, (int) object->sprite.getLocalBounds().width, (int) object->sprite.getLocalBounds().height));
	}

	return;
}

void ObjectMap::objectFlipy(Object* object) {
	
	if (object == NULL) return;

	objectFlipx(object);
	object->sprite.setRotation(selected->second->rotate + 180);

	object->rotate += 180;

	if(object->rotate > 360)
		object->rotate = (int) object->rotate % 360;

	return;
}

void ObjectMap::objectRotate(Object* object, float mod) {
	
	if (object == NULL) return;

	object->rotate += mod;

	object->sprite.setRotation(object->rotate);

	if (object->rotate > 360)
		object->rotate = (int) object->rotate % 360;

}

void ObjectMap::objectScale(Object* object, float mod) {

	if (object == NULL) return;

	if (object->scale + mod > 0) {

		object->scale += mod;

		object->sprite.setScale(sf::Vector2f(object->scale, object->scale));

	}

	return;
}