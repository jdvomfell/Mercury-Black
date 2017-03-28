#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML\Graphics.hpp>

class Animation {
	
	public: 

		std::vector<sf::Texture *> textures;
		std::vector<std::string> textureIDs;

		float animationTime; 

		Animation(float animationTime);
		Animation() {}

		void addFrame(sf::Texture * texture, std::string textureID);

};

#endif