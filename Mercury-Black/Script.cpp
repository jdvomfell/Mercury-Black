#include "script.h"

void playerScript(World * world, int playerID) {

	Input * i = &world->input[playerID];
	Sprite * s = &world->sprite[playerID];
	Velocity * v = &world->velocity[playerID];

	if (v->onGround) {

		//if (v->x == 0)
			//s->animationManager.changeAnimation("idle");

		if (v->x != 0)
			s->animationManager.changeAnimation("run");

	}

	else {

		//s->animationManager.changeAnimation("jump");

	}

}