#include "EventHandler.h"

void EventHandler::insertSpawn(sf::RectangleShape * rectangle)
{

	Event * newEvent = new Spawner();
	events.insert(std::make_pair((rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}

void EventHandler::insertSound(sf::RectangleShape * rectangle)
{

	Event * newEvent = new Sound();
	events.insert(std::make_pair((rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}

void EventHandler::insertSwitch(sf::RectangleShape * rectangle)
{

	Event * newEvent = new Switch();
	events.insert(std::make_pair((rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}

void EventHandler::insertSwitchEffect(sf::RectangleShape * rectangle)
{

	Event * newEvent = new SwitchEffect();
	events.insert(std::make_pair((rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}

void EventHandler::remove(std::map<float, Event *>::iterator oldEvent)
{

	events.erase(oldEvent);

}

void Spawner::trigger()
{

}

bool Spawner::isTriggered()
{
	return false;
}

void Sound::trigger()
{

}

bool Sound::isTriggered()
{
	return false;
}

void Switch::trigger()
{

}

bool Switch::isTriggered()
{
	return false;
}

void SwitchEffect::trigger()
{

}

bool SwitchEffect::isTriggered()
{
	return false;
}
