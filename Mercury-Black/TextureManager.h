#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {

public:

	sf::Font font;
	sf::Font slideFont;

	std::map<std::string, sf::Texture> textures;
	
	sf::Texture * getTexture(std::string id);
	
	void loadTexture(std::string id, std::string fileName);
	void loadTextures(std::string id, std::string fileName, int numTextures);
	void loadAllTextures();

	std::string getPrevTextureID(std::string textureID);
	std::string getNextTextureID(std::string textureID);

};

#endif 