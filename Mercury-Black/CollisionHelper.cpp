#include "CollisionHelper.h"
#include <cmath>

sf::Vector2f getEntityNormal(std::string side) {

	if (side == "left")
		return sf::Vector2f(-1.0f, 0.0f);

	else if (side == "right")
		return sf::Vector2f(1.0f, 0.0f);

	else if (side == "top")
		return sf::Vector2f(0.0f, -1.0f);

	else if (side == "bottom")
		return sf::Vector2f(0.0f, 1.0f);

	return sf::Vector2f(0.0f, 0.0f);

}

sf::Vector2f getEntityProjection(sf::Vector2f unitNormal, sf::RectangleShape bounds) {

	float min, max, projection;
	sf::Vector2f projReturn;

	sf::Vector2f topLeft(bounds.getGlobalBounds().left, bounds.getGlobalBounds().top);
	sf::Vector2f topRight(bounds.getGlobalBounds().left + bounds.getGlobalBounds().width, bounds.getGlobalBounds().top);
	sf::Vector2f bottomLeft(bounds.getGlobalBounds().left, bounds.getGlobalBounds().top + bounds.getGlobalBounds().height);
	sf::Vector2f bottomRight(bounds.getGlobalBounds().left + bounds.getGlobalBounds().width, bounds.getGlobalBounds().top + bounds.getGlobalBounds().height);

	min = (topLeft.x * unitNormal.x) + (topLeft.y * unitNormal.y);
	max = min;

	projection = ((topLeft.x * unitNormal.x) + (topLeft.y * unitNormal.y));
	if (projection < min)
		min = projection;
	else if (projection > max)
		max = projection;

	projection = (bottomLeft.x * unitNormal.x) + (bottomLeft.y * unitNormal.y);
	if (projection < min)
		min = projection;
	else if (projection > max)
		max = projection;

	projection = (topRight.x * unitNormal.x) + (topRight.y * unitNormal.y);
	if (projection < min)
		min = projection;
	else if (projection > max)
		max = projection;

	projection = (bottomRight.x * unitNormal.x) + (bottomRight.y * unitNormal.y);
	if (projection < min)
		min = projection;
	else if (projection > max)
		max = projection;

	projReturn.x = min;
	projReturn.y = max;

	return projReturn;
}

bool isCollision(sf::Vector2f firstProj, sf::Vector2f secondProj) {

	return !(firstProj.y < secondProj.x || secondProj.y < firstProj.x);

}

float getOverlap(sf::Vector2f shapeProj, sf::Vector2f entityProj) {

	if ((shapeProj.x < entityProj.x && shapeProj.y > entityProj.y) || (entityProj.x < shapeProj.x && entityProj.y > shapeProj.y))
		return FLT_MAX;

	float overlapLength = fabs(std::min(shapeProj.y, entityProj.y) - std::max(shapeProj.x, entityProj.x));

	return overlapLength;

}

void stopCollision(World * world, unsigned int entityID, float length, sf::Vector2f unitNormal)
{

	sf::Vector2f mtv;

	mtv.x = unitNormal.x * length;
	mtv.y = unitNormal.y * length;

	if (mtv.x > 0)
		mtv.x += 0.02f;
	else if (mtv.x < 0)
		mtv.x += -0.02f;

	if (mtv.y > 0)
		mtv.y += 0.02f;
	else if (mtv.y < 0)
		mtv.y += -0.02f;

	world->position[entityID].x += world->velocity[entityID].x;
	world->position[entityID].y += world->velocity[entityID].y;
	world->position[entityID].x += mtv.x;
	world->position[entityID].y += mtv.y;

	world->velocity[entityID].x = 0;
	world->velocity[entityID].y = 0;

}