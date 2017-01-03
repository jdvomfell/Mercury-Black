#include "Texture.h"

sf::Texture * TextureManager::getTexture(ID id) {

	if (textures.find(id) != textures.end())
		return textures[id];

	else
		return NULL;

}

sf::Texture * TextureManager::loadTexture(ID id, std::string filename) {

	sf::Texture * tempTexture;

	tempTexture = new sf::Texture;

	if (tempTexture->loadFromFile(filename)) {

		textures[id] = tempTexture;

		return textures[id];

	}

	else {

		delete tempTexture;

		return NULL;

	}

}