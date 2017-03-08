#include <SFML/Graphics.hpp>
#include <map>

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

struct Event {

	sf::RectangleShape * eventArea; 
	//void trigger();
	//bool isTriggered();
};

class EventHandler {

	void insert(sf::RectangleShape * rectangle);
	void remove(std::map<float, Event *>::iterator oldEvent);
	void spawnCheck(); 

	std::map<float, Event *> events; 
};

#endif 