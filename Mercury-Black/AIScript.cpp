#include "AIScript.h"
#include <cmath>

/* Utility Scripts */

void scriptFollow(World * world, int entityID, float x, float y) {

	float distance = sqrt(pow(world->position[entityID].x - x, 2) + pow(world->position[entityID].y - y, 2));

	if (distance <= world->scriptParameters[entityID].followDistMax && distance >=world->scriptParameters[entityID].followDistMin){
			
		if (world->position[entityID].x < x) {
			world->input[entityID].right = true;
			world->input[entityID].left = false;
		}
		else {
			world->input[entityID].left = true;
			world->input[entityID].right = false;
		}

		if (world->position[entityID].y > y) {
			world->input[entityID].up = true;
			world->input[entityID].down = false;
		}
		else {
			world->input[entityID].down = true;
			world->input[entityID].up = false;
		}
	}

	else {
		world->input[entityID].left = false;
		world->input[entityID].right = false;
		world->input[entityID].down = false;
		world->input[entityID].up = false;
	}

}

void scriptAttack(World* world, int entityID, float x, float y) {

	if (std::fabs(world->position[entityID].x - x) <=
		world->scriptParameters[entityID].attackRangeMax &&

		std::fabs(world->position[entityID].x - x) >=
		world->scriptParameters[entityID].attackRangeMin) {
			
		world->scriptParameters[entityID].currentState = ATTACK_STATE;
			//world->input[entityID].attack = true;
	}

	else {
		//world->input[entityID].attack = false;
	}
}

void scriptRetreat(World * world, int entityID, float x, float y) {

	if (std::fabs(world->position[entityID].x - x) <=
		world->scriptParameters[entityID].followDistMin) {

		if (world->position[entityID].x < x) {
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

/* Entity Scripts */

void scriptPlayer(World *world, float dt) {

	Input * i;
	Sprite * s;
	Velocity * v;
	ScriptParameters * sp;
	
	s = &(world->sprite[0]);
	v = &(world->velocity[0]);
	i = &(world->input[0]);
	sp = &(world->scriptParameters[0]);

	if (sp->currentState == MOVEMENT_STATE)
		v->speedUp = 2.0f;
	else
		v->speedUp = 1.0f;
	
	/* On Ground */
	if (v->onGround) {
		/* Moving */
		if (i->left || i->right) {
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
				if (sp->currentState == NO_STATE) {
					s->animationManager.changeAnimation("sheathedRun");
				}
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
				if (sp->currentState == NO_STATE) {
					s->animationManager.changeAnimation("idleAttack");
					sp->currentState = ATTACK_STATE;
				}
			}
			/* No Input */
			else {
				if (sp->currentState == NO_STATE) {
					s->animationManager.changeAnimation("idleUnsheathed");
				}
			}
		}
		/* Roll */
		if (i->down) {
			if (sp->currentState == NO_STATE) {
				s->animationManager.changeAnimation("roll");
				sp->currentState = MOVEMENT_STATE;
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

}

void scriptPlant(World * world, int entityID, float dt) {
	
	Sprite *s;
	ScriptParameters *sP;

	s = &(world->sprite[entityID]);
	sP = &(world->scriptParameters[entityID]);
		
	if (sP->currentState == NO_STATE) {
		scriptFollow(world, entityID, world->position[0].x, world->position[0].y);
		scriptAttack(world, entityID, world->position[0].x, world->position[0].y);
		
		if (sP->currentState == ATTACK_STATE)
			s->animationManager.changeAnimation("tripleAttack");
		else {
			if (sP->currentState == NO_STATE)
				s->animationManager.changeAnimation("idle");
		}
	}
	
	else if (sP->currentState == NOT_SPAWNED_STATE) {
		scriptSpawn(world, entityID);
		if (sP->currentState == SPAWN_STATE)
			s->animationManager.changeAnimation("spawn");
		else
			s->animationManager.changeAnimation("notSpawn");
	}

}

void scriptSpawn(World *world, int entityID) {
	ScriptParameters * sP;

	sP = &world->scriptParameters[entityID];

	if (sP->spawnDistance >= abs(world->position[entityID].x - world->position[0].x) &&
		sP->spawnDistance >= abs(world->position[entityID].y - world->position[0].y)) {
		sP->currentState = SPAWN_STATE;
	}

	return;
}

void scriptTest(World * world, int entityID, float dt) {

	Velocity * v;
	Sprite * s;
	ScriptParameters * sp;
	Input * i;

	i = &(world->input[entityID]);
	v = &(world->velocity[entityID]);
	s = &(world->sprite[entityID]);
	sp = &(world->scriptParameters[entityID]);

	if (sp->currentState == DEATH_STATE) {
		destroyEntity(world, entityID);
		return;
	}

	scriptFollow(world, entityID, world->position[0].x, world->position[0].y);
	scriptAttack(world, entityID, world->position[0].x, world->position[0].y);

	if (i->left || i->right)
		s->animationManager.changeAnimation("sheathedRun");
	
	else {

		if (sp->currentState == ATTACK_STATE)
			s->animationManager.changeAnimation("idleAttack");
		else
			s->animationManager.changeAnimation("idleUnsheathed");
	
	}

}

void scriptWisp(World * world, int entityID, float dt) {

	Sprite * s;
	Position * p;
	ScriptParameters * sp;

	s = &(world->sprite[entityID]);
	p = &(world->position[entityID]);
	sp = &(world->scriptParameters[entityID]);

	if (sp->currentState == DEATH_STATE) {
		//SUNBURT
		//KILL SPAWNER LIFESPAN
		destroyEntity(world, entityID);
		return;
	}

	scriptFollow(world, entityID, world->position[0].x, world->position[0].y);

	s->metaballSpawner->position.x = p->x;
	s->metaballSpawner->position.y = p->y;

}

void scriptHeart(World * world, int entityID) {

	ScriptParameters * sp;

	sp = &(world->scriptParameters[entityID]);

	if (sp->currentState == DEATH_STATE) {
		//SUNBURST
		world->health[0].max += 10;
		world->health[0].current = world->health[0].max;
		destroyEntity(world, entityID);
	}

}