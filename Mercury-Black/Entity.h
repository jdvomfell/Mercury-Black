#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include "TextureManager.h"
#include "Metaball.h"

#define MAX_ENTITIES 100

struct World {

	int mask[MAX_ENTITIES];

	Name name[MAX_ENTITIES];
	Stats stats[MAX_ENTITIES];
	Input input[MAX_ENTITIES];
	Health health[MAX_ENTITIES];
	Sprite sprite[MAX_ENTITIES];
	Gravity gravity[MAX_ENTITIES];
	Position position[MAX_ENTITIES];
	Velocity velocity[MAX_ENTITIES];
	ScriptParameters scriptParameters[MAX_ENTITIES];

	TextureManager * textureManager;
	MetaballHandler * metaballHandler;

};

void cleanWorld(World * world);
int createEntity(World * world);
void destroyEntity(World * world, int entityID);

int createTest(World * world, float x, float y);
int createPlayer(World * world, float x, float y);
int createGroundBlob(World * world, float x, float y);
int createCeilingPlant(World * world, float x, float y);
int createWisp(World * world, float x, float y, MetaballHandler * metaballHandler);
int createLotus(World * world, float x, float y);

int createHeart(World * world, float x, float y);

#endif