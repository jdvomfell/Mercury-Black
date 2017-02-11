#ifndef SYSTEM_H
#define SYSTEM_H

#include "Entity.h"
#include "CollisionMap.h"
#include "PlatformMap.h"
#include "AIScript.h"

void aiSystem(World * world, float dt);
void inputSystem(World * world);
void renderSystem(World * world, sf::RenderWindow * window);
void gravitySystem(World * world);
void movementSystem(World * world);
void animationSystem(World * world, float dt);
void collisionSystem(World * world, CollisionMap * collisionMap);
void shapeCollSystem(World * world, PlatformMap * platforms);

sf::Vector2f getEntityNormal(std::string side, sf::Sprite entity);
sf::Vector2f getEntityProjection(sf::Vector2f normal, sf::Sprite entity);
bool isCollision(sf::Vector2f shapeProj, sf::Vector2f entityProj);

#endif