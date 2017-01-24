#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <SFML\Graphics.hpp>
#include <map>
#include <vector>

#include "Animation.h"

class AnimationManager {
	public:

		std::map<std::string, Animation *> animations; 

		float currentTime; 

		std::string currentAnimation;

		int currentFrame;	

		void addAnimation(Animation * animation, std::string id);
		void updateAnimation(float deltaTime);
		void changeAnimation(std::string animationID);
		sf::Texture * getCurrentTexture();
		AnimationManager();
};

#endif 
