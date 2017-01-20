#include "TextureManager.h"

sf::Texture * TextureManager::getTexture(std::string id) {
	return &textures[id];
}

void TextureManager::loadTexture(std::string id, std::string fileName) {
	sf::Texture texture;

	texture.loadFromFile(fileName);

	textures[id] = texture;
}

