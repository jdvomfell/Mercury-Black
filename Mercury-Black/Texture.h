#ifndef TEXTURE_H
#define TEXTURE_H

#include <map>
#include <SFML\Graphics.hpp>

enum ID { playerIdle, playerRun, playerJump, playerSwing, rock1, tree1 };

class TextureManager{

public:

	sf::Texture * loadTexture(ID, std::string filename);
	sf::Texture * getTexture(ID);

private:

	std::map<ID, sf::Texture *> textures;

};

#endif