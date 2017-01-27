#ifndef AISCRIPT_H
#define AISCRIPT_H

#include "Entity.h"
#include <SFML/Graphics.hpp>

void scriptPlayer(World *world, float dt);
void scriptPlant();
void scriptTest(World * world, int);

void scriptFollow(World * world, int entityID, sf::Vector2f position);
void scriptAttack(World * world, int entityID, sf::Vector2f position);
void scriptRetreat(World * world, int entityID, sf::Vector2f position);

#endif