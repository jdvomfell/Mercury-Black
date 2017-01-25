#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {

public:

	std::map<std::string, sf::Texture> textures;
	
	sf::Texture * getTexture(std::string id);
	
	void loadTexture(std::string id, std::string fileName);
	void loadAllTextures();

};

#endif 