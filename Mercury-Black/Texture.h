#ifndef TEXTURE_H
#define TEXTURE_H

#include <map>
#include <SFML\Graphics.hpp>

enum ID { playerIdle, playerRun, playerJump };

class textureManager{

	std::multimap<ID, sf::Texture> textures;

};

#endif