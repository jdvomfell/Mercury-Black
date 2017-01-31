#include "AIScript.h"
#include <cmath>


void scriptTest(World * world, int entityID) {

	//world->sprite[entityID].sprite.setColor(sf::Color::Black);

	scriptFollow(world, entityID,sf::Vector2f(world->position[0].x, world->position[0].y));

}

void scriptFollow(World * world, int entityID, sf::Vector2f position) {

	if (std::fabs(world->position[entityID].x - position.x) <=
		world->scriptParameter[entityID].followDistMax &&

		std::fabs(world->position[entityID].x - position.x) >=
		world->scriptParameter[entityID].followDistMin){
			
			if (world->position[entityID].x - position.x < 0) {
				world->input[entityID].right = true;
			}
			
			else {
				world->input[entityID].left = true;
			}
	}

	else {
		world->input[entityID].left = false;
		world->input[entityID].right = false;
	}
	
}

void scriptAttack(World* world, int entityID, sf::Vector2f position) {

	if (std::fabs(world->position[entityID].x - position.x) <=
		world->scriptParameter[entityID].attackRangeMax &&

		std::fabs(world->position[entityID].x - position.x) >=
		world->scriptParameter[entityID].attackRangeMin) {

			world->input[entityID].attack = true;
	}

	else {
		world->input[entityID].attack = false;
	}
}

void scriptRetreat(World * world, int entityID, sf::Vector2f position) {

	if (std::fabs(world->position[entityID].x - position.x) <=
		world->scriptParameter[entityID].followDistMin) {

		if (world->position[entityID].x - position.x < 0) {
			world->input[entityID].left = true;
		}

		else {
			world->input[entityID].right = true;
		}
	}

	else {
		world->input[entityID].left = false;
		world->input[entityID].right = false;
	}
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

void scriptPlant(World * world, int entityID, float dt) {
	Sprite *s;

	s = &world->sprite[entityID];
	
	s->animationManager.updateAnimation(dt);
	s->sprite.setTexture(*s->animationManager.getCurrentTexture());
	s->sprite.setOrigin(sf::Vector2f(s->sprite.getLocalBounds().width / 2, s->sprite.getLocalBounds().height));
}