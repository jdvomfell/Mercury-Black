#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <SFML\Graphics.hpp>
#include <map>
#include <vector>

#include "Animation.h"
#include "TextureManager.h"

class AnimationManager {
	public:

		std::map<std::string, Animation *> animations; 

		float currentTime; 

		std::string currentAnimation;

		int currentFrame;

		AnimationManager();
		sf::Texture * getCurrentTexture();
		int updateAnimation(float deltaTime);
		void changeAnimation(std::string animationID);
		void addAnimation(Animation * animation, std::string id);
		void createAnimation(TextureManager * textureManager, std::string entityName, std::string animationName, int numFrames, float animationSpeed);

};

#endif 
