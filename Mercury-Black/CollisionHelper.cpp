#include "CollisionHelper.h"
#include <cmath>

sf::Vector2f CollisionHelper::getEntityNormal(std::string side, sf::Sprite * entity) {

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

sf::Vector2f CollisionHelper::getEntityProjection(sf::Vector2f unitNormal, sf::Sprite * entity) {

	float min, max, projection;
	sf::Vector2f projReturn;

	sf::Vector2f topLeft(entity->getGlobalBounds().left, entity->getGlobalBounds().top);
	sf::Vector2f topRight(entity->getGlobalBounds().left + entity->getGlobalBounds().width, entity->getGlobalBounds().top);
	sf::Vector2f bottomLeft(entity->getGlobalBounds().left, entity->getGlobalBounds().top + entity->getGlobalBounds().height);
	sf::Vector2f bottomRight(entity->getGlobalBounds().left + entity->getGlobalBounds().width, entity->getGlobalBounds().top + entity->getGlobalBounds().height);

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

bool CollisionHelper::isCollision(sf::Vector2f firstProj, sf::Vector2f secondProj) {

	return !(firstProj.y < secondProj.x || secondProj.y < firstProj.x);

}

float CollisionHelper::getOverlap(sf::Vector2f shapeProj, sf::Vector2f entityProj) {

	if ((shapeProj.x < entityProj.x && shapeProj.y > entityProj.y) || (entityProj.x < shapeProj.x && entityProj.y > shapeProj.y))
		return FLT_MAX;

	float overlapLength = fabs(std::min(shapeProj.y, entityProj.y) - std::max(shapeProj.x, entityProj.x));

	return overlapLength;

}

void CollisionHelper::stopCollision(World * world, unsigned int entityID, float length, sf::Vector2f unitNormal)
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

	world->position[entityID].x += mtv.x;
	world->position[entityID].y += mtv.y;

	world->velocity[entityID].x = 0;
	world->velocity[entityID].y = 0;

}