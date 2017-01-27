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

	Animation * idleAnimation = new Animation(0.2f);
		idleAnimation->addFrame(world->textureManager->getTexture("player_idle_1"));

	Animation * idleAttackAnimation = new Animation(0.1f);
		idleAttackAnimation->addFrame(world->textureManager->getTexture("player_idle_attack_1"));
		idleAttackAnimation->addFrame(world->textureManager->getTexture("player_idle_attack_2"));
		idleAttackAnimation->addFrame(world->textureManager->getTexture("player_idle_attack_3"));
		idleAttackAnimation->addFrame(world->textureManager->getTexture("player_idle_attack_4"));
		idleAttackAnimation->addFrame(world->textureManager->getTexture("player_idle_attack_5"));
		idleAttackAnimation->addFrame(world->textureManager->getTexture("player_idle_attack_6"));
		idleAttackAnimation->addFrame(world->textureManager->getTexture("player_idle_attack_7"));
		idleAttackAnimation->addFrame(world->textureManager->getTexture("player_idle_attack_8"));
	
	Animation * runAnimation = new Animation(0.125f);
		runAnimation->addFrame(world->textureManager->getTexture("player_run_1"));
		runAnimation->addFrame(world->textureManager->getTexture("player_run_2"));
		runAnimation->addFrame(world->textureManager->getTexture("player_run_3"));
		runAnimation->addFrame(world->textureManager->getTexture("player_run_5"));
		runAnimation->addFrame(world->textureManager->getTexture("player_run_4"));
		runAnimation->addFrame(world->textureManager->getTexture("player_run_6"));

	Animation * jumpAnimation = new Animation(0.1f);
		jumpAnimation->addFrame(world->textureManager->getTexture("player_jump_1"));
		jumpAnimation->addFrame(world->textureManager->getTexture("player_jump_2"));
		jumpAnimation->addFrame(world->textureManager->getTexture("player_jump_3"));
		jumpAnimation->addFrame(world->textureManager->getTexture("player_jump_4"));
		jumpAnimation->addFrame(world->textureManager->getTexture("player_jump_5"));
		jumpAnimation->addFrame(world->textureManager->getTexture("player_jump_6"));
		jumpAnimation->addFrame(world->textureManager->getTexture("player_jump_7"));

	Animation * inAirAnimation = new Animation(0.1f);
		inAirAnimation->addFrame(world->textureManager->getTexture("player_jump_8"));

	world->sprite[entityID].animationManager.addAnimation(runAnimation, "run");
	world->sprite[entityID].animationManager.addAnimation(idleAnimation, "idle");
	world->sprite[entityID].animationManager.addAnimation(jumpAnimation, "jump");
	world->sprite[entityID].animationManager.addAnimation(inAirAnimation, "inAir");
	world->sprite[entityID].animationManager.addAnimation(idleAttackAnimation, "idleAttack");

	world->sprite[entityID].animationManager.changeAnimation("idle");
	
	world->sprite[entityID].sprite.setOrigin(sf::Vector2f(world->sprite[entityID].sprite.getLocalBounds().width / 2, world->sprite[entityID].sprite.getLocalBounds().height));

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
	world->velocity[entityID].speed = 10.0f;
	world->velocity[entityID].canJump = false;
	world->velocity[entityID].onGround = false;

	world->gravity[entityID].weight = 1.0f;

	world->scriptParameter[entityID].followDistMin = 20.0f;
	world->scriptParameter[entityID].followDistMax = 150.0f;

	return entityID;
}