#include "EventHandler.h"
/*
void EventHandler::insertSpawn(sf::RectangleShape * rectangle, World * world) {

	Spawner * newEvent = new Spawner();

	newEvent->eventArea = rectangle; 
	newEvent->world = world; 

	events.insert(std::make_pair((float) (rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}*/

void EventHandler::insertSound(sf::RectangleShape * rectangle, World * world, std::string fileName, float volume, bool loop) {

	Sound * newEvent = new Sound();
	float pos;

	Position player;
	player = world->position[0];

	newEvent->eventArea = rectangle; 
	newEvent->world = world;
	pos = rectangle->getPosition().x;

	rectangle->setOrigin(rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0),
						 rectangle->getPosition().x + (rectangle->getGlobalBounds().height / 2.0));

	newEvent->sound = new sf::Music(); 
	newEvent->sound->openFromFile(fileName);
	newEvent->sound->setPosition(player.x, player.y, 0);
	newEvent->sound->setVolume(volume);
	newEvent->sound->setLoop(loop);
	newEvent->sound->setMinDistance(100000.0f);

	events.insert(std::make_pair(pos, newEvent));

}
/*
void EventHandler::insertSwitch(sf::RectangleShape * rectangle, World * world) {

	Switch * newEvent = new Switch();

	newEvent->eventArea = rectangle; 
	newEvent->world = world;

	events.insert(std::make_pair((rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}

void EventHandler::insertSwitchEffect(sf::RectangleShape * rectangle, World * world) {

	SwitchEffect * newEvent = new SwitchEffect();

	newEvent->eventArea = rectangle; 
	newEvent->world = world;

	events.insert(std::make_pair((rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}*/

void EventHandler::remove(std::map<float, Event *>::iterator oldEvent) {

	events.erase(oldEvent);

}

void EventHandler::clean() {

	for (eit = events.begin(); eit != events.end(); eit++)
		events.erase(eit); 

}

void Spawner::trigger() {
	
}

bool Spawner::isTriggered() {
	
	return false;
}

void Sound::trigger() {

	eventArea->setFillColor(sf::Color::Red);
	sound->play();

}

bool Sound::isTriggered() {

	Position player; 

	player = world->position[0];

	if (eventArea->getGlobalBounds().contains(player.x, player.y)) {

		if (sound->getPlayingOffset() != sf::Time::Zero) 
			 return false;
		else return true;

	}
	else return false; 

}

void Switch::trigger() {


}

bool Switch::isTriggered() {
	return false;
}

void SwitchEffect::trigger() {

}

bool SwitchEffect::isTriggered() {
	
	return false;

}
