#include "AIScript.h"

void scriptFollow(World * world, int entityID, sf::Vector2f position) {

}

void scriptPlayer(World *world, float dt) {
	Sprite * s;
	Velocity * v;
	Input *in;
	
	s = &(world->sprite[0]);
	v = &(world->velocity[0]);
	in = &(world->input[0]);
	
	if (v->onGround) {

		if (v->x != 0)
			s->animationManager.changeAnimation("run");
		else {
			if (in->attack)
				s->animationManager.changeAnimation("idleAttack");
			else
				s->animationManager.changeAnimation("idle");
		}
		
	} else {
		//s->animationManager.changeAnimation("jump");
		s->animationManager.changeAnimation("inAir");

	}
	
	if (v->x < 0)
		s->sprite.setTextureRect(sf::IntRect(s->sprite.getLocalBounds().width, 0, -s->sprite.getLocalBounds().width, s->sprite.getLocalBounds().height));
	if (v->x > 0)
		s->sprite.setTextureRect(sf::IntRect(0, 0, s->sprite.getLocalBounds().width, s->sprite.getLocalBounds().height));

	s->animationManager.updateAnimation(dt);
	s->sprite.setTexture(*s->animationManager.getCurrentTexture());
	s->sprite.setOrigin(sf::Vector2f(s->sprite.getLocalBounds().width / 2, s->sprite.getLocalBounds().height));

}