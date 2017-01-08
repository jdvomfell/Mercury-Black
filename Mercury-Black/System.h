#ifndef SYSTEM_H
#define SYSTEM_H

#include "Entity.h"
#include "CollisionMap.h"

void inputSystem(World * world);
void renderSystem(World * world, sf::RenderWindow * window);
void movementSystem(World * world);
void collisionSystem(World * world, CollisionMap * collisionMap);

#endif