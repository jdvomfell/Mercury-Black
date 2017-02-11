#include "PlatformMap.h"

#include "TextureManager.h"

void PlatformMap::save()
{

}

void PlatformMap::load()
{

}

void PlatformMap::changeColor(sf::Color color, float position)
{
	platformMap[position]->shape->setFillColor(color);
}

void PlatformMap::add(sf::Vector2f position, unsigned int vertices)
{
	int i;

	sf::Color color = sf::Color::Blue;

	platform = new Platform; 
	platform->position = position; 
	platform->shape = new sf::ConvexShape(vertices); 
	platform->shape->setFillColor(color);
	platform->shape->setPoint(0, sf::Vector2f(position.x, position.y));
	platform->shape->setPoint(1, sf::Vector2f(position.x - 200, position.y - 100));
	platform->shape->setPoint(2, sf::Vector2f(position.x - 400, position.y));
	//platform->shape->setPoint(4, sf::Vector2f(position.x - 50, position.y + 50));
	//platform->shape->setPoint(5, sf::Vector2f(position.x - 50, position.y));

	platformMap.insert(std::make_pair(position.x, platform));
}

void PlatformMap::remove()
{

}

sf::Vector2f PlatformMap::getEdgeNormal(int vertex, sf::ConvexShape shape) {
	sf::Vector2f p1, p2, edge, normal;

	p1 = shape.getPoint(vertex);

	if (shape.getPoint(vertex) == shape.getPoint(shape.getPointCount() - 1))
		p2 = shape.getPoint(0);
	else
		p2 = shape.getPoint(vertex + 1);

	edge.x = p2.x - p1.x;
	edge.y = p2.y - p2.y;

	normal.x = edge.y;
	normal.y = -(edge.x);

	return normal;
}

/* Projects Shape onto SAT (normal of shape edge) */
sf::Vector2f PlatformMap::getProjection(sf::Vector2f normal, sf::ConvexShape shape) {
	float min, max, projection;

	int i;

	sf::Vector2f projReturn; 

	min = (shape.getPoint(0).x * normal.x) + (shape.getPoint(0).y * normal.y);
	max = min;

	for (i = 1; i < shape.getPointCount(); i++)
	{
		projection = (shape.getPoint(i).x * normal.x) + (shape.getPoint(i).y * normal.y);	
		if (projection < min)
			min = projection;
		else if (projection > max)
			max = projection;
	}

	projReturn.x = min;
	projReturn.y = max; 

	return projReturn;
}

