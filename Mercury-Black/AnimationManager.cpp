#include "AnimationManager.h"

AnimationManager::AnimationManager() {

	currentTime = 0.0f;
	currentAnimation = "";
	currentFrame = 0; 

}

void AnimationManager::clean() {

	std::map<std::string, Animation *>::iterator it;

	it = animations.begin();
	while (it != animations.end()) {

		delete(it->second);
		animations.erase(it++);

	}

}

void AnimationManager::createAnimation(TextureManager * textureManager, std::string entityName, std::string animationName, int numFrames, float animationSpeed) {

	std::string frameName;

	Animation * animation = new Animation(animationSpeed);

	for (int i = 0; i < numFrames; i++) {
		frameName = entityName;
		frameName += "_" + animationName + "_" + std::to_string(i + 1);
		animation->addFrame(textureManager->getTexture(frameName), frameName);
	}

	this->addAnimation(animation, animationName);

}

void AnimationManager::addAnimation(Animation * animation, std::string id) {
	
	if (animations.find(id) != animations.end()) {
		printf("Error: Adding Existing Animation: %s\n", id.c_str());
	}

	animations.insert(std::make_pair(id, animation));

}

int AnimationManager::updateAnimation(float deltaTime) {

	if (animations.find(currentAnimation) == animations.end()) {
		printf("Error: Could Not Update Animation, Does Not Exist: %s\n", currentAnimation.c_str());
		return -1;
	}

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

	if (animations.find(animationID) == animations.end()) {
		printf("Error: Could Not Switch To Animation, Does Not Exist: %s\n", animationID.c_str());
		return;
	}

	if (animationID == currentAnimation)
		return;

	currentAnimation = animationID;
	currentFrame = 0;
	currentTime = 0.0f;

}

std::string AnimationManager::getCurrentTextureID() {

	return animations[currentAnimation]->textureIDs[currentFrame];

}

sf::Texture * AnimationManager::getCurrentTexture() {

	return animations[currentAnimation]->textures[currentFrame];

}

bool AnimationManager::isEmpty() {

	if (animations.begin() == animations.end())
		return true;
	else
		return false;

}