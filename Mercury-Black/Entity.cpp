#include "Entity.h"

void cleanWorld(World * world) {

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		world->mask[entityID] = EMPTY;

	}

}

int createEntity(World * world){

	int entityID;
	
	for (entityID = 1; entityID < MAX_ENTITIES; entityID++){

		if (world->mask[entityID] == EMPTY)
			return entityID;

	}

	printf("No More Entity Space, Overriding last entity in array...\n");

	return MAX_ENTITIES;

}

void destroyEntity(World * world, int entityID) {

	printf("Destroying Entity: %s With ID: %d\n", world->name[entityID].name.c_str(), entityID);

	world->mask[entityID] = EMPTY;

}

int createPlayer(World * world, float x, float y) {

	int entityID = 0;

	world->mask[entityID] = NAME | INPUT | POSITION | VELOCITY | SPRITE | COLLISION | GRAVITY | SCRIPT;

	world->name[entityID].name = "player";

	world->position[entityID].x = x;
	world->position[entityID].y = y;

	world->velocity[entityID].x = 0.0f;
	world->velocity[entityID].y = 0.0f;
	world->velocity[entityID].speed = 15.0f;
	world->velocity[entityID].canJump = false;
	world->velocity[entityID].onGround = false;

	world->gravity[entityID].weight = 1.0f;

	world->scriptParameters[entityID].currentState = 0;

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idle", 1, 0.2f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idleAttack", 8, 0.1f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "run", 6, 0.125f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "jump", 7, 0.05f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "inAir", 1, 0.001f);
	
	return entityID;

}

int createCeilingPlant(World * world, float x, float y) {
	int entityID = createEntity(world);
	int i;
	std::string plantName, temp;

	world->mask[entityID] = NAME | INPUT | POSITION | SPRITE | SCRIPT;

	world->name[entityID].name = "ceilingPlant";

	world->position[entityID].x = x;
	world->position[entityID].y = y;

	world->scriptParameters[entityID].attackRangeMax = 1000.0f;
	world->scriptParameters[entityID].attackRangeMin = 0.0f;

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idle", 11, 0.2f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "spawn", 20, 0.1f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "tripleAttack", 25, 0.1f);

	return entityID;
}

int createTest(World * world, sf::Vector2f position) {
	
	int entityID = createEntity(world);

	world->mask[entityID] = NAME | INPUT | POSITION | VELOCITY | SPRITE | COLLISION | GRAVITY | SCRIPT;

	world->name[entityID].name = "test";

	world->position[entityID].x = position.x;
	world->position[entityID].y = position.y;

	world->velocity[entityID].x = 0.0f;
	world->velocity[entityID].y = 0.0f;
	world->velocity[entityID].speed = 8.0f;
	world->velocity[entityID].canJump = false;
	world->velocity[entityID].onGround = false;

	world->gravity[entityID].weight = 1.0f;

	world->scriptParameters[entityID].followDistMin = 250.0f;
	world->scriptParameters[entityID].followDistMax = 1500.0f;

	world->scriptParameters[entityID].attackRangeMin = 0.0f;
	world->scriptParameters[entityID].attackRangeMax = 250.0f;

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idle", 1, 0.2f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "run", 6, 0.125f);
	
	return entityID;

}