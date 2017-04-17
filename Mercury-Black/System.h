#ifndef SYSTEM_H
#define SYSTEM_H

#include "Entity.h"
#include "CollisionMap.h"
#include "PlatformMap.h"
#include "AIScript.h"

void aiSystem(World * world, float dt);
void inputSystem(World * world);
void renderSystem(World * world, sf::RenderWindow * window);
void damageSystem(World * world, float dt, class HitboxMap * hitboxMap);
void gravitySystem(World * world);
void movementSystem(World * world);
void animationSystem(World * world, float dt);
void shapeCollSystem(World * world, PlatformMap * platformMap, HitboxMap * hitboxMap);
void metaballDamageSystem(World * world, HitboxMap * hitboxMap);

#endif