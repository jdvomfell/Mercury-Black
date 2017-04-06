/*----------------------------------COLLISION HELPER--------------------------------*/
/*		Class that grabs information from the entity specified and calculates       */
/*      various vector functions for use in shapeCollSystem in System.cpp           */
/*----------------------------------------------------------------------------------*/

#ifndef COLLISIONHELPER_H
#define COLLISIONHELPER_H

#include "System.h"
#include <cmath>	

	sf::Vector2f getEntityNormal(std::string side);
	sf::Vector2f getEntityProjection(sf::Vector2f unitNormal, sf::RectangleShape bounds);
	bool isCollision(sf::Vector2f firstProj, sf::Vector2f secondProj);
	float getOverlap(sf::Vector2f shapeProj, sf::Vector2f entityProj);
	void stopCollision(World * world, unsigned int entityID, float length, sf::Vector2f unitNormal);

#endif