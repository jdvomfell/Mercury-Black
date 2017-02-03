#include "AnimationManager.h"

AnimationManager::AnimationManager() {

	currentTime = 0.0f;
	currentAnimation = "";
	currentFrame = 0; 

}

void AnimationManager::addAnimation(Animation * animation, std::string id) {
	
	animations.insert(std::make_pair(id, animation));

}

int AnimationManager::updateAnimation(float deltaTime) {

	if (animations.find(currentAnimation) == animations.end())
		return -1;

	float animationTime = animations[currentAnimation]->animationTime;

	if (int((currentTime + deltaTime) / animationTime) > int(currentTime / animationTime)) {

		int frameNum = int((currentTime + deltaTime) / animationTime);

		frameNum %= animations[currentAnimation]->textures.size();

		currentFrame = frameNum;
	}

	currentTime += deltaTime;

	if (currentTime > animationTime * animations[currentAnimation]->textures.size()) {
		currentTime = 0.0f;
		return 1;
	}
	return 0;
}


void AnimationManager::changeAnimation(std::string animationID)	{

	if (animationID == currentAnimation || animations.find(animationID) == animations.end())
		return;

	currentAnimation = animationID;
	currentFrame = 0;
	currentTime = 0.0f;

}

sf::Texture * AnimationManager::getCurrentTexture() {

	return animations[currentAnimation]->textures[currentFrame];

}