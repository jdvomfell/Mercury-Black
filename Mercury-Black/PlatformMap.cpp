#include "PlatformMap.h"

#include "TextureManager.h"
#include <fstream>

void PlatformMap::save()
{

	std::ofstream ofstream;
	std::string filename = "platform.dat";

	ofstream.open(filename, std::ios::out | std::ios::binary);

	for (std::map<float, sf::ConvexShape *>::iterator it = map.begin(); it != map.end(); it++) {

		ofstream
			<< it->second->getPointCount() << std::endl;

		for (size_t i = 0; i < it->second->getPointCount(); i++) {

			ofstream
				<< it->second->getPoint(i).x << std::endl
				<< it->second->getPoint(i).y << std::endl;

		}

	}

	ofstream.close();

}

void PlatformMap::load()
{

	size_t pointCount;
	sf::Vector2f point;
	unsigned int platformCount = 0;

	PlatformPoints platformPoints;

	std::ifstream ifstream;
	std::string filename = "platform.dat";

	ifstream.open(filename, std::ios::in | std::ios::binary);

	if (!ifstream.is_open()) {
		printf("Cannot Open Platform File (Possibly No File To Load)\n");
		return;
	}

	clean();

	while (ifstream >> pointCount) {

		if (ifstream.eof())
			return;

		platformCount++;

		printf("PC: %d\n", pointCount);

		printf("PLAT C: %d\n", platformCount);

		for (size_t i = 0; i < pointCount; i++) {

			ifstream >> point.x >> point.y;

			printf("X,Y: %f %f\n", point.x, point.y);

			platformPoints.insert(point);

		}

		insert(&platformPoints.lines);
		platformPoints.clean();

	}

	printf("Loaded %d Platforms\n", platformCount);

	ifstream.close();

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

	map.insert(std::make_pair(shape->getPoint(0).x, shape)).first;

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

void PlatformMap::insertGround(sf::Vector2f groundPosition) {

	sf::Vector2f edge;
	sf::Vector2f normal;
	sf::Vector2f unitNormal;


	if (platformPoints.isEmpty()) {

		platformPoints.insert(groundPosition);
		platformPoints.insert(sf::Vector2f(groundPosition.x, groundPosition.y + 30));

	}

	else {

		edge.x = platformPoints.begin->point.x - groundPosition.x;
		edge.y = platformPoints.begin->point.y - groundPosition.y;

		normal.x = edge.y;
		normal.y = -edge.x;

		unitNormal.x = normal.x / (sqrt(pow(normal.x, 2) + pow(normal.y, 2)));
		unitNormal.y = normal.y / (sqrt(pow(normal.x, 2) + pow(normal.y, 2)));

		platformPoints.insert(sf::Vector2f(groundPosition.x + unitNormal.x * 30, groundPosition.y + unitNormal.y * 30));
		platformPoints.insert(groundPosition);

		insert(&platformPoints.lines);
		platformPoints.clean();

		platformPoints.insert(groundPosition);
		platformPoints.insert(sf::Vector2f(sf::Vector2f(groundPosition.x + unitNormal.x * 30, groundPosition.y + unitNormal.y * 30)));

	}

}

void PlatformMap::remove()
{

}

void PlatformMap::clean() {

	std::map<float, sf::ConvexShape *>::iterator pit = map.begin();

	while (pit != map.end()) {

		delete(pit->second);
		map.erase(pit++);

	}

	platformPoints.clean();

	return;

}

sf::Vector2f PlatformMap::getEdgeNormal(int vertex, sf::ConvexShape * shape) {

	sf::Vector2f p1, p2, edge, normal, unitNormal;

	p1 = shape->getPoint(vertex);

	if (shape->getPoint(vertex) == shape->getPoint(shape->getPointCount() - 1))
		p2 = shape->getPoint(0);
	else
		p2 = shape->getPoint(vertex + 1);

	edge.x = p1.x - p2.x;
	edge.y = p1.y - p2.y;

	normal.x = edge.y;
	normal.y = -edge.x;

	unitNormal.x = normal.x / (sqrt(pow(normal.x, 2) + pow(normal.y, 2)));
	unitNormal.y = normal.y / (sqrt(pow(normal.x, 2) + pow(normal.y, 2)));

	return unitNormal;
}

/* Projects Shape onto SAT (normal of shape edge) */
sf::Vector2f PlatformMap::getProjection(sf::Vector2f unitNormal, sf::ConvexShape * shape) {

	float min;
	float max;
	float projection;

	size_t i;

	sf::Vector2f projReturn;

	min = (shape->getPoint(0).x * unitNormal.x) + (shape->getPoint(0).y * unitNormal.y);
	max = min;

	for (i = 1; i < shape->getPointCount(); i++)
	{
		projection = (shape->getPoint(i).x * unitNormal.x) + (shape->getPoint(i).y * unitNormal.y);
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

bool PlatformPoints::isEmpty() {

	if (lines.getVertexCount() == 0)
		return true;
	else
		return false;

}