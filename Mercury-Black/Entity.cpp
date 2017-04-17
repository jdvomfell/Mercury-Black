#include "Entity.h"

void cleanWorld(World * world) {

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		destroyEntity(world, entityID);

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

	world->gravity[entityID].weight = 1.0f;

	world->name[entityID].name = "";

	world->health[entityID].max = 0;
	world->health[entityID].current = 0;
	world->health[entityID].hurtTimer = 0;

	world->position[entityID].x = 0;
	world->position[entityID].y = 0;

	world->velocity[entityID].x = 0.0f;
	world->velocity[entityID].y = 0.0f;
	world->velocity[entityID].speed = 0.0f;
	world->velocity[entityID].speedUp = 1.0f;
	world->velocity[entityID].onGround = false;

	world->velocity[entityID].canJump = false;
	world->velocity[entityID].canDoubleJump = false;

	world->input[entityID].up = false;
	world->input[entityID].jump = false;
	world->input[entityID].down = false;
	world->input[entityID].left = false;
	world->input[entityID].right = false;
	world->input[entityID].attack = false;
	world->input[entityID].special = false;

	world->scriptParameters[entityID].retreatDist = 0;
	world->scriptParameters[entityID].attackTimer = 0;
	world->scriptParameters[entityID].currentState = 0;
	world->scriptParameters[entityID].spawnDistance = 0;
	world->scriptParameters[entityID].followDistMax = 0;
	world->scriptParameters[entityID].followDistMin = 0;
	world->scriptParameters[entityID].attackRangeMax = 0;
	world->scriptParameters[entityID].attackRangeMin = 0;
	world->scriptParameters[entityID].attackFrequency = 0;
	world->scriptParameters[entityID].secondsRemaining = 0;

	world->sprite[entityID].sprite = sf::Sprite();
	world->sprite[entityID].animationManager.clean();

	world->mask[entityID] = EMPTY;

}

int createPlayer(World * world, float x, float y) {

	int entityID = 0;

	world->mask[entityID] = NAME | INPUT | POSITION | VELOCITY | SPRITE | COLLISION | GRAVITY | SCRIPT | HEALTH | STATS;

	world->name[entityID].name = "player";

	world->position[entityID].x = x;
	world->position[entityID].y = y;

	world->velocity[entityID].x = 0.0f;
	world->velocity[entityID].y = 0.0f;
	world->velocity[entityID].speed = 15.0f;
	world->velocity[entityID].speedUp = 1.0f;
	world->velocity[entityID].canJump = false;
	world->velocity[entityID].onGround = false;

	world->stats[entityID].power = 30;

	world->health[entityID].max = 100;
	world->health[entityID].current = world->health[entityID].max;

	world->gravity[entityID].weight = 1.0f;

	world->scriptParameters[entityID].currentState = 0;

	world->sprite[entityID].animationManager.createAnimation
	(world->textureManager, world->name[entityID].name, "fall", 3, 0.07f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idle", 24, 0.15f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idleAttack", 7, 0.1f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "run", 6, 0.125f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "jump", 6, 0.05f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "roll", 5, 0.1f);
	
	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "inkArmAttack", 9, 0.1f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "runAttack", 6, 0.125f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "jumpAttack", 6, 0.125f);

	return entityID;

}

int createGroundBlob(World * world, float x, float y) {

	int entityID = createEntity(world);

	world->mask[entityID] = NAME | INPUT | POSITION | SPRITE | SCRIPT | STATS | HEALTH | COLLISION | GRAVITY | VELOCITY;

	world->name[entityID].name = "gblob";

	world->position[entityID].x = x;
	world->position[entityID].y = y;

	world->gravity[entityID].weight = 1.0f;

	world->scriptParameters[entityID].currentState = NO_STATE;

	world->scriptParameters[entityID].followDistMin = 0.0f;
	world->scriptParameters[entityID].followDistMax = 1500.0f;
	world->scriptParameters[entityID].attackRangeMin = 500.0f;
	world->scriptParameters[entityID].attackRangeMax = 1000.0f;
	world->scriptParameters[entityID].attackTimer = 0.0f;
	world->scriptParameters[entityID].attackFrequency = 5.0f;
	world->scriptParameters[entityID].retreatDist = 750.0f;

	world->velocity[entityID].speed = 5.0f;
	world->velocity[entityID].speedUp = 1.0f;
	world->velocity[entityID].x = 0.0f;
	world->velocity[entityID].y = 0.0f;
	world->velocity[entityID].onGround = false;

	world->stats[entityID].power = 10;

	world->health[entityID].max = 200;
	world->health[entityID].current = world->health[entityID].max;
	world->health->hurtTimer = 0.0f;

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idle", 10, 0.1f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "attack", 17, 0.05f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "up", 11, 0.1f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "down", 16, 0.15f);

	return entityID;

}

int createCeilingPlant(World * world, float x, float y) {

	int entityID = createEntity(world);
	std::string plantName, temp;

	world->mask[entityID] = NAME | INPUT | POSITION | SPRITE | SCRIPT | STATS | HEALTH;

	world->name[entityID].name = "ceilingPlant";

	world->position[entityID].x = x;
	world->position[entityID].y = y;

	world->scriptParameters[entityID].attackRangeMax = 700.0f;
	world->scriptParameters[entityID].attackRangeMin = 0.0f;

	world->scriptParameters[entityID].attackFrequency = 3.0f;

	world->scriptParameters[entityID].followDistMax = 500.0f;
	world->scriptParameters[entityID].followDistMin = 0.0f;

	world->scriptParameters[entityID].spawnDistance = 500.0f;
	world->scriptParameters[entityID].currentState = NO_STATE;
	
	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idle", 12, 0.1f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "drop", 17, 0.1f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "attack", 25, 0.065f);
	
	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "notSpawn", 2, 0.1f);
	
	return entityID;
}

int createTest(World * world, float x, float y) {
	
	int entityID = createEntity(world);

	world->mask[entityID] = NAME | INPUT | POSITION | VELOCITY | SPRITE | COLLISION | GRAVITY | SCRIPT | HEALTH | STATS;

	world->name[entityID].name = "test";

	world->position[entityID].x = x;
	world->position[entityID].y = y;

	world->velocity[entityID].x = 0.0f;
	world->velocity[entityID].y = 0.0f;
	world->velocity[entityID].speed = 8.0f;
	world->velocity[entityID].speedUp = 1.0f;
	world->velocity[entityID].canJump = false;
	world->velocity[entityID].onGround = false;

	world->gravity[entityID].weight = 1.0f;

	world->stats[entityID].power = 10;

	world->health[entityID].max = 100;
	world->health[entityID].current = world->health[entityID].max;

	world->scriptParameters[entityID].followDistMin = 250.0f;
	world->scriptParameters[entityID].followDistMax = 1500.0f;

	world->scriptParameters[entityID].retreatDist = 1000.0f;

	world->scriptParameters[entityID].attackRangeMin = 0.0f;
	world->scriptParameters[entityID].attackRangeMax = 250.0f;

	world->scriptParameters[entityID].attackFrequency = 2.0f;

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idle", 24, 0.2f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "run", 6, 0.125f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idleAttack", 7, 0.1f);
	
	return entityID;

}

int createWisp(World * world, float x, float y, MetaballHandler * metaballHandler) {

	int entityID = createEntity(world);

	world->mask[entityID] = NAME | HEALTH | SCRIPT | POSITION | VELOCITY | STATS | INPUT | FLYING;

	world->name[entityID].name = "wisp";

	world->health[entityID].max = 50;
	world->health[entityID].current = 50;

	world->scriptParameters[entityID].followDistMin = 0;
	world->scriptParameters[entityID].followDistMax = 1000;
	world->scriptParameters[entityID].currentState = ATTACK_STATE;

	world->position[entityID].x = x;
	world->position[entityID].x = y;

	world->velocity[entityID].speed = 10.0f;
	world->velocity[entityID].speedUp = 1.0f;

	world->stats[entityID].power = 5;

	world->sprite[entityID].metaballSpawner = new MetaballSpawner(metaballHandler, sf::Vector2f(x, y), sf::Vector2f(0, 0.5f), -0.05f, 1.5f, 25, 5, 5, false);
	metaballHandler->addSpawner(world->sprite[entityID].metaballSpawner);

	return entityID;

}

int createLotus(World * world, float x, float y) {

	int entityID = createEntity(world);

	world->mask[entityID] = NAME | INPUT | POSITION | VELOCITY | SPRITE | SCRIPT | HEALTH | STATS;

	world->name[entityID].name = "lotusMb";

	world->health[entityID].max = 500;
	world->health[entityID].current = world->health[entityID].max;
	world->health[entityID].hurtTimer = 0.0f;

	world->scriptParameters[entityID].followDistMin = 10.0f;
	world->scriptParameters[entityID].followDistMax = 1500.0f;
	world->scriptParameters[entityID].attackRangeMin = 10.0f;
	world->scriptParameters[entityID].attackRangeMax = 300.0f;
	world->scriptParameters[entityID].attackFrequency = 5.0f;

	world->scriptParameters[entityID].currentState = NO_STATE;

	world->position[entityID].x = x;
	world->position[entityID].y = y;

	world->velocity[entityID].x = 0;
	world->velocity[entityID].y = 0;
	world->velocity[entityID].speed = 7.0f;
	world->velocity[entityID].speedUp = 1.0f;

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "idle", 10, 0.1f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "dropAttack", 11, 0.07f);

	world->sprite[entityID].animationManager.createAnimation
		(world->textureManager, world->name[entityID].name, "rise", 14, 0.07f);

	world->stats[entityID].power = 30;

	return entityID;

}

int createHeart(World * world, float x, float y) {

	int entityID = createEntity(world);

	world->mask[entityID] = NAME | HEALTH | SCRIPT | SPRITE | POSITION;

	world->name[entityID].name = "heart";

	world->health[entityID].max = 1;
	world->health[entityID].current = 1;

	world->scriptParameters[entityID].currentState = NO_STATE;

	world->sprite[entityID].sprite.setTexture(*world->textureManager->getTexture("heart"));

	world->position[entityID].x = x;
	world->position[entityID].y = y;

	return entityID;

}