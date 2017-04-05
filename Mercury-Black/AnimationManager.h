#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <SFML\Graphics.hpp>
#include <map>
#include <vector>

#include "Animation.h"
#include "TextureManager.h"

class AnimationManager {
	public:

		int currentFrame;
		float currentTime;

		std::string currentAnimation;

		std::map<std::string, Animation *> animations;

		AnimationManager();

		void clean();
		std::string getCurrentTextureID();
		sf::Texture * getCurrentTexture();

		bool isEmpty();

		int updateAnimation(float deltaTime);
		void changeAnimation(std::string animationID);

		void addAnimation(Animation * animation, std::string id);
		void createAnimation(TextureManager * textureManager, std::string entityName, std::string animationName, int numFrames, float animationSpeed);

};

#endif 
