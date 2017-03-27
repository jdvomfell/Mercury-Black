#include "Animation.h"

Animation::Animation(float animationTime) {

	this->animationTime = animationTime;

}

void Animation::addFrame(sf::Texture * texture, std::string textureID) {

	textures.push_back(texture);
	textureIDs.push_back(textureID);

}