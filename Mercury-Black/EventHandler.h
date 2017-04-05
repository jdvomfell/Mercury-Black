#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Entity.h"
#include <fstream>
#include <map>
#include <string>
#include <typeinfo>


#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class Event {
	
public:

	std::string type; 
	sf::RectangleShape * eventArea; 
	virtual void trigger() = 0;
	virtual bool isTriggered() = 0;
	virtual void clean() = 0;
	World * world; 

};

class Spawner : public Event {

public:

	void trigger(); 
	bool isTriggered();
	void clean();

};

class Sound : public Event {

public:

	void trigger();
	bool isTriggered();
	void clean();
	sf::Music * sound;
	std::string filename;
	//bool loopSound; 
	//bool isPlaying;

};

class Switch : public Event {

public:

	void trigger();
	bool isTriggered();
	void clean();

};

class SwitchEffect : public Event {

public:

	void trigger();
	bool isTriggered();
	void clean();

};

class EventHandler {

public:
	//void insertSpawn(sf::RectangleShape * rectangle, World * world);
	void insertSound(sf::RectangleShape * rectangle, std::string fileName, float volume, bool loop);
	//void insertSwitch(sf::RectangleShape * rectangle, World * world);
//	void insertSwitchEffect(sf::RectangleShape * rectangle, World * world);
	
	void remove(std::map<float, Event *>::iterator oldEvent);
	void clean();
	void save();
	void load();
	void draw(sf::RenderWindow * window);
	std::map <float, Event *>::iterator containment(sf::Vector2f mouse);

	std::multimap<float, Event *> events; 
	std::map<float, Event *>::iterator eit;
	std::map<float, Event *>::iterator selected;

	World * world;

	int numEvents;
};

#endif 