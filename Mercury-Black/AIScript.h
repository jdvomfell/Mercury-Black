#ifndef AISCRIPT_H
#define AISCRIPT_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

void scriptPlayer(World *world, float dt);
void scriptPlant(World *world, int entityID, float dt);
void scriptTest(World * world, int entityID, float dt);
void scriptWisp(World * world, int entityID, float dt);
void scriptHeart(World * world, int entityID);

void scriptFollow(World * world, int entityID, float x, float y);
void scriptAttack(World * world, int entityID, float x, float y);
void scriptRetreat(World * world, int entityID, float x, float y);
void scriptSpawn(World * world, int entityID);
#endif