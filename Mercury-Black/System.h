#ifndef SYSTEM_H
#define SYSTEM_H

#include "Entity.h"

void renderSystem(World * world, sf::RenderWindow * window);
void movementSystem(World * world);
void collisionSystem(World * world);

#endif