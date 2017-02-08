#include "AIScript.h"
#include <cmath>

#define NO_STATE 0
#define ATTACK_STATE 1
#define DEFENCE_STATE 2
#define JUMP_STATE 3
#define SPAWN_STATE 4


void scriptTest(World * world, int entityID, float dt) {

	Velocity * v;
	Sprite * s;

	v = &(world->velocity[entityID]);
	s = &(world->sprite[entityID]);

	scriptFollow(world, entityID,sf::Vector2f(world->position[0].x, world->position[0].y));

	if (v->x != 0)
		s->animationManager.changeAnimation("sheathedRun");
	else
		s->animationManager.changeAnimation("idleUnsheathed");

	if (v->x < 0)
		s->sprite.setTextureRect(sf::IntRect(s->sprite.getLocalBounds().width, 0, -s->sprite.getLocalBounds().width, s->sprite.getLocalBounds().height));
	if (v->x > 0)
		s->sprite.setTextureRect(sf::IntRect(0, 0, s->sprite.getLocalBounds().width, s->sprite.getLocalBounds().height));

	s->animationManager.updateAnimation(dt);

	s->sprite.setTexture(*s->animationManager.getCurrentTexture());
	s->sprite.setOrigin(sf::Vector2f(s->sprite.getLocalBounds().width / 2, s->sprite.getLocalBounds().height));

}

void scriptFollow(World * world, int entityID, sf::Vector2f position) {

	if (std::fabs(world->position[entityID].x - position.x) <=
		world->scriptParameters[entityID].followDistMax &&

		std::fabs(world->position[entityID].x - position.x) >=
		world->scriptParameters[entityID].followDistMin){
			
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
		world->scriptParameters[entityID].attackRangeMax &&

		std::fabs(world->position[entityID].x - position.x) >=
		world->scriptParameters[entityID].attackRangeMin) {

			world->input[entityID].attack = true;
	}

	else {
		world->input[entityID].attack = false;
	}
}

void scriptRetreat(World * world, int entityID, sf::Vector2f position) {

	if (std::fabs(world->position[entityID].x - position.x) <=
		world->scriptParameters[entityID].followDistMin) {

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

	Input * i;
	Sprite * s;
	Velocity * v;
	ScriptParameters * sp;
	
	s = &(world->sprite[0]);
	v = &(world->velocity[0]);
	i = &(world->input[0]);
	sp = &(world->scriptParameters[0]);
	
	/* On Ground */
	if (v->onGround) {
		/* Moving */
		if (v->x != 0) {
			/* Jump */
			if (i->jump) {
				s->animationManager.changeAnimation("jump");
				sp->currentState = JUMP_STATE;
			}
			/* Attack */
			//else if (i->attack) {
				//TODO
			//}
			/* No Input */
			else {
				s->animationManager.changeAnimation("sheathedRun");
			}
		}
		/* Not Moving*/
		else {
			/* Jump */
			if (i->jump) {
				s->animationManager.changeAnimation("jump");
				sp->currentState = JUMP_STATE;
			}
			/* Attack */
			else if (i->attack) {
				s->animationManager.changeAnimation("idleAttack");
				sp->currentState = ATTACK_STATE;
			}
			/* No Input */
			else {
				if (sp->currentState == NO_STATE) {
					s->animationManager.changeAnimation("idleUnsheathed");
				}
			}
		}
	}
	/* In Air */
	else {
		/* Moving */
		if (v->x != 0) {
			/* Attack */
			//if (i->attack) {
				//TODO
			//}
			/* No Input */
			//else {
				if (sp->currentState == NO_STATE) {
					s->animationManager.changeAnimation("inAir");
				}
			//}
		}
		/* Not Moving  (Might Be Able To Remove)*/
		else {
			/* Attack */
			//if (i->attack) {
				//TODO
			//}
			/* No Input */
			//else {
				if (sp->currentState == NO_STATE) {
					s->animationManager.changeAnimation("inAir");
				}
			//}
		}
	}
	
	if (v->x < 0)
		s->sprite.setTextureRect(sf::IntRect(s->sprite.getLocalBounds().width, 0, -s->sprite.getLocalBounds().width, s->sprite.getLocalBounds().height));
	if (v->x > 0)
		s->sprite.setTextureRect(sf::IntRect(0, 0, s->sprite.getLocalBounds().width, s->sprite.getLocalBounds().height));

	s->sprite.setTexture(*s->animationManager.getCurrentTexture());
	s->sprite.setOrigin(sf::Vector2f(s->sprite.getLocalBounds().width / 2, s->sprite.getLocalBounds().height));

	/* Allow Animation Changes If Current Animation Has Ended */
	if (s->animationManager.updateAnimation(dt) == 1)
		sp->currentState = NO_STATE;

}

void scriptPlant(World * world, int entityID, float dt) {
	
	Sprite *s;

	s = &(world->sprite[entityID]);

	scriptAttack(world, entityID, sf::Vector2f(world->position[0].x, world->position[0].y));

	if (world->input[entityID].attack) {
		s->animationManager.changeAnimation("tripleAttack");
	}
	else {
		s->animationManager.changeAnimation("spawn");
	}
	
	s->animationManager.updateAnimation(dt);
	s->sprite.setTexture(*s->animationManager.getCurrentTexture());
	s->sprite.setOrigin(sf::Vector2f(s->sprite.getLocalBounds().width / 2, s->sprite.getLocalBounds().height));
}