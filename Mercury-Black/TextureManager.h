#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {
private:

	std::map<std::string, sf::Texture> textures;

public:

	void loadTexture(std::string id, std::string fileName);
	sf::Texture * getTexture(std::string id);
};


#endif 