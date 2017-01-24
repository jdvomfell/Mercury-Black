#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML\Graphics.hpp>

class Animation {
	
	public: 

		std::vector<sf::Texture *> textures;

		float animationTime; 

		Animation(float animationTime) {

			this->animationTime = animationTime; 

		}

		Animation() {}

		void addFrame(sf::Texture * texture) {

			textures.push_back(texture);

		}

};

#endif