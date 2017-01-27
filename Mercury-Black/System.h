#ifndef SYSTEM_H
#define SYSTEM_H

#include "Entity.h"
#include "CollisionMap.h"
#include "AIScript.h"

void aiSystem(World * world, float dt);
void inputSystem(World * world);
void renderSystem(World * world, sf::RenderWindow * window);
void gravitySystem(World * world);
void movementSystem(World * world);
void animationSystem(World * world, float dt, int player);
void collisionSystem(World * world, CollisionMap * collisionMap);

#endif