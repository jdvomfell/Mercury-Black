#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include "TextureManager.h"

#define MAX_ENTITIES 100

struct World {

	int mask[MAX_ENTITIES];

	Name name[MAX_ENTITIES];
	Input input[MAX_ENTITIES];
	Sprite sprite[MAX_ENTITIES];
	Gravity gravity[MAX_ENTITIES];
	Position position[MAX_ENTITIES];
	Velocity velocity[MAX_ENTITIES];

	TextureManager * textureManager;

};

void cleanWorld(World * world);
int createEntity(World * world);
void destroyEntity(World * world, int entityID);

int createPlayer(World * world, float x, float y);

#endif