#include "PlatformMap.h"

#include "TextureManager.h"

void PlatformMap::save()
{

}

void PlatformMap::load()
{

}

void PlatformMap::add(sf::Vector2f position, unsigned int vertices)
{
	int i;

	const sf::Color color = sf::Color::Blue;

	platform = new Platform; 
	platform->position = position; 
	platform->shape = new sf::ConvexShape(vertices); 
	platform->shape->setFillColor(color);

	platform->shape->setPoint(0, position);
	platform->shape->setPoint(1, sf::Vector2f(position.x + 200, position.y - 100));
	platform->shape->setPoint(2, sf::Vector2f(position.x - 200, position.y - 250));

	platformMap.insert(std::make_pair(position.x, platform));
}

void PlatformMap::remove()
{

}

void PlatformMap::clean()
{

}