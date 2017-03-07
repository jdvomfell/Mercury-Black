#include <SFML/Graphics.hpp>
#include <map>

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class Event {
	
public:

	sf::RectangleShape * eventArea; 
	virtual void trigger() = 0;
	virtual bool isTriggered() = 0;

};

class Spawner : public Event {

public:

	void trigger(); 
	bool isTriggered(); 

};

class Sound : public Event {

public:

	void trigger();
	bool isTriggered();

};

class Switch : public Event {

public:

	void trigger();
	bool isTriggered();

};

class SwitchEffect : public Event {

public:

	void trigger();
	bool isTriggered();

};

class EventHandler {

	void insertSpawn(sf::RectangleShape * rectangle);
	void insertSound(sf::RectangleShape * rectangle);
	void insertSwitch(sf::RectangleShape * rectangle);
	void insertSwitchEffect(sf::RectangleShape * rectangle);
	
	void remove(std::map<float, Event *>::iterator oldEvent);

	std::map<float, Event *> events; 

};

#endif 