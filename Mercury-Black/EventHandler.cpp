#include "EventHandler.h"

void EventHandler::insert(sf::RectangleShape * rectangle)
{

	Event * newEvent = new Event();
	newEvent->eventArea = rectangle; 

	events.insert(std::make_pair((rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}

void EventHandler::remove(std::map<float, Event *>::iterator oldEvent)
{

	events.erase(oldEvent);

}

void EventHandler::spawnCheck()
{

}
