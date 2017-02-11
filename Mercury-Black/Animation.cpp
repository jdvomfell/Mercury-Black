#include "Animation.h"

Animation::Animation(float animationTime) {

	this->animationTime = animationTime;

}

void Animation::addFrame(sf::Texture * texture) {

	textures.push_back(texture);

}