#ifndef AISCRIPT_H
#define AISCRIPT_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

void inputFlip(World * world, int entityID);

void scriptPlayer(World * world, float dt);
void scriptPlant(World * world, int entityID, float dt);
void scriptTest(World * world, int entityID, float dt);
void scriptWisp(World * world, int entityID, float dt);
void scriptHeart(World * world, int entityID);
void scriptLotus(World * world, int entityID, float dt);
void scriptSpitter(World * world, int entityID, float dt);
void scriptGroundBlob(World * world, int entityID, float dt);

void scriptFollow(World * world, int entityID, float x, float y);
bool scriptAttack(World * world, int entityID, float x, float y, float dt);
void scriptRetreat(World * world, int entityID, float x, float y);
void scriptSpawn(World * world, int entityID);

#endif