#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Entity.h"
#include <map>
#include <string>


#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class Event {
	
public:

	sf::RectangleShape * eventArea; 
	virtual void trigger() = 0;
	virtual bool isTriggered() = 0;
	World * world; 

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
	sf::Music * sound;
	//bool loopSound; 
	//bool isPlaying;

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

public:
	//void insertSpawn(sf::RectangleShape * rectangle, World * world);
	void insertSound(sf::RectangleShape * rectangle, World * world, std::string fileName, float volume, bool loop);
	//void insertSwitch(sf::RectangleShape * rectangle, World * world);
//	void insertSwitchEffect(sf::RectangleShape * rectangle, World * world);
	
	void remove(std::map<float, Event *>::iterator oldEvent);
	void clean();

	std::map<float, Event *> events; 
	std::map<float, Event *>::iterator eit;
};

#endif 