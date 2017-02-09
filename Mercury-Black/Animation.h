#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML\Graphics.hpp>

class Animation {
	
	public: 

		std::vector<sf::Texture *> textures;

		float animationTime; 

		Animation(float animationTime);
		Animation() {}

		void addFrame(sf::Texture * texture);

};

#endif