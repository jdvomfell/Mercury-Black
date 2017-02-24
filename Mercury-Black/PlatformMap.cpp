#include "PlatformMap.h"

#include "TextureManager.h"

void PlatformMap::save()
{

}

void PlatformMap::load()
{

}

void PlatformMap::insert(sf::VertexArray * points)
{

	if (points->getVertexCount() == 0)
		return;

	sf::ConvexShape * shape = new sf::ConvexShape(points->getVertexCount());
	
	shape->setFillColor(sf::Color::Black);
	
	for (size_t i = 0; i < points->getVertexCount(); i++) {

		shape->setPoint(i, (*points)[i].position);

	}

	map.insert(std::make_pair(shape->getPoint(0).x, shape));

	return;
}

void PlatformMap::insertBox(sf::Vector2f topLeft, sf::Vector2f bottomRight) {

	sf::ConvexShape * shape = new sf::ConvexShape(4);

	shape->setFillColor(sf::Color::Black);

	shape->setPoint(0, topLeft);
	shape->setPoint(1, sf::Vector2f(topLeft.x, bottomRight.y));
	shape->setPoint(2, bottomRight);
	shape->setPoint(3, sf::Vector2f(bottomRight.x, topLeft.y));

	map.insert(std::make_pair(shape->getPoint(0).x, shape));

	return;

}

void PlatformMap::remove()
{

}

void PlatformMap::clean() {

	std::map<float, sf::ConvexShape *>::iterator pit = map.begin();

	while(pit != map.end()) {

		delete(pit->second);
		map.erase(pit++);

	}

	return;

}

sf::Vector2f PlatformMap::getEdgeNormal(int vertex, sf::ConvexShape * shape) {
	sf::Vector2f p1, p2, edge, normal;

	p1 = shape->getPoint(vertex);

	if (shape->getPoint(vertex) == shape->getPoint(shape->getPointCount() - 1))
		p2 = shape->getPoint(0);
	else
		p2 = shape->getPoint(vertex + 1);

	edge.x = p1.x - p2.x;
	edge.y = p1.y - p2.y;

	if (edge.y < 0) {
		normal.x = edge.y;
		normal.y = -(edge.x);
	}
	else
	{
		normal.x = -(edge.y);
		normal.y = edge.x;
	}

	return normal;
}

/* Projects Shape onto SAT (normal of shape edge) */
sf::Vector2f PlatformMap::getProjection(sf::Vector2f normal, sf::ConvexShape * shape) {
	
	float min;
	float max;
	float projection;

	size_t i;

	sf::Vector2f projReturn; 

	min = (shape->getPoint(0).x * normal.x) + (shape->getPoint(0).y * normal.y);
	max = min;

	for (i = 1; i < shape->getPointCount(); i++)
	{
		projection = (shape->getPoint(i).x * normal.x) + (shape->getPoint(i).y * normal.y);	
		if (projection < min)
			min = projection;
		else if (projection > max)
			max = projection;
	}

	projReturn.x = min;
	projReturn.y = max; 

	return projReturn;

}

void PlatformMap::draw(sf::RenderWindow * window) {

	std::map<float, sf::ConvexShape *>::iterator pit;

	for (pit = map.begin(); pit != map.end(); pit++)
		window->draw(*pit->second);

	return;

}

void PlatformPoints::insert(sf::Vector2f point) {

	PlatPoint * platPoint = new PlatPoint;
	platPoint->nextPoint = NULL;
	platPoint->prevPoint = NULL;

	platPoint->point = point;

	/* If There Is An Existing Point */
	if (current != NULL) {
		
		/* Set Previous */
		platPoint->prevPoint = current;
		
		/* Set Next */
		if (current->nextPoint != NULL) {
			platPoint->nextPoint = current->nextPoint;

			/* Set Next's Previous */
			platPoint->nextPoint->prevPoint = platPoint;
		}
		else
			platPoint->nextPoint = NULL;

		/* Set Previous' Next */
		platPoint->prevPoint->nextPoint = platPoint;

	}

	/* Not An Existing Point */
	else {

		platPoint->nextPoint = NULL;
		platPoint->prevPoint = NULL;

		begin = platPoint;

	}

	/* Set Current Point To Inserted One */
	current = platPoint;

	update();

	return;

}

void PlatformPoints::remove() {

	PlatPoint * toDelete = NULL;

	if (current == NULL)
		return;

	if (current->nextPoint == NULL && current->prevPoint == NULL) {
		delete(current);
		current = NULL;
		begin = NULL;
		return;
	}

	if (current->prevPoint != NULL) {

		if (current->nextPoint != NULL)
			current->prevPoint->nextPoint = current->nextPoint;
		else
			current->prevPoint->nextPoint = NULL;

		toDelete = current;
		current = current->prevPoint;

	}

	else if (current->nextPoint != NULL) {

		if (current->prevPoint != NULL)
			current->nextPoint->prevPoint = current->prevPoint;
		else {
			current->nextPoint->prevPoint = NULL;
			begin = current->nextPoint;
		}

		toDelete = current;
		current = current->nextPoint;

	}

	if (toDelete != NULL)
		delete(toDelete);

	update();

}

void PlatformPoints::draw(sf::RenderWindow * window) {

	window->draw(lines);

}

void PlatformPoints::update() {

	lines.clear();
	PlatPoint * uit = begin;

	while (uit != NULL) {
		if (current == uit)
			lines.append(sf::Vertex(uit->point, sf::Color::Red));
		else
			lines.append(sf::Vertex(uit->point, sf::Color::Black));
		uit = uit->nextPoint;
	}

}

void PlatformPoints::clean() {

	current = begin;

	while (begin != NULL) {

		current = begin;

		begin = current->nextPoint;
		delete(current);

	}

	current = NULL;
	lines.clear();

}