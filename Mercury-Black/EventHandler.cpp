#include "EventHandler.h"
/*
void EventHandler::insertSpawn(sf::RectangleShape * rectangle, World * world) {

	Spawner * newEvent = new Spawner();

	newEvent->eventArea = rectangle; 
	newEvent->world = world; 

	events.insert(std::make_pair((float) (rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}*/


/*
void EventHandler::insertSwitch(sf::RectangleShape * rectangle, World * world) {

	Switch * newEvent = new Switch();

	newEvent->eventArea = rectangle; 
	newEvent->world = world;

	events.insert(std::make_pair((rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}

void EventHandler::insertSwitchEffect(sf::RectangleShape * rectangle, World * world) {
s
	SwitchEffect * newEvent = new SwitchEffect();

	newEvent->eventArea = rectangle; 
	newEvent->world = world;

	events.insert(std::make_pair((rectangle->getPosition().x + (rectangle->getGlobalBounds().width / 2.0)), newEvent));

}*/


void EventHandler::remove(std::map<float, Event *>::iterator oldEvent) {

	if (oldEvent == events.end() || oldEvent->second == NULL || numEvents <= 1)
		return;

	delete(oldEvent->second);
	events.erase(selected);
	selected = events.end();
	numEvents--;
}

void EventHandler::clean() {

	for (eit = events.begin(); eit != events.end();)
	{
		eit->second->clean();
		events.erase(eit++);
	}

	numEvents = 0;
}

void EventHandler::save() {

	std::ofstream ofstream;

	std::string eventFilename = "event.dat";
	ofstream.open(eventFilename, std::ios::out | std::ios::binary);

	for (eit = events.begin(); eit != events.end(); eit++) {

		if (eit->second->type == "SOUND") {
			Sound * sound = dynamic_cast<Sound *>(eit->second);

			ofstream
				<< "SOUND" << std::endl
				<< sound->eventArea->getPosition().x << std::endl
				<< sound->eventArea->getPosition().y << std::endl
				<< sound->eventArea->getSize().x << std::endl
				<< sound->eventArea->getSize().y << std::endl
				<< sound->filename << std::endl
				<< sound->sound->getVolume() << std::endl
				<< sound->sound->getLoop() << std::endl
				<< sound->sound->getMinDistance() << std::endl;

		}
	}

	ofstream.close();
}

void EventHandler::load() {

	std::string eventFilename = "event.dat";
	std::ifstream ifstream;

	float x, y, sizeX, sizeY;
	std::string eventType; 

	int numEvents = 0; 

	clean();

	ifstream.open(eventFilename, std::ios::in | std::ios::binary);

	if (!ifstream.is_open()) {
		printf("ERROR: Cannot Open Object File (Possibly No File To Load)\n");
		return;
	}

	while (ifstream >> eventType) {

		if (ifstream.eof())
			return; 

		if (eventType == "SOUND") {

			numEvents++;

			printf("fuckkckcckckckckc");
			float volume; 
			bool loop;
			float minDistance; 
			std::string filename; 
			Sound * sound = new Sound();
			
			ifstream >> x >> y >> sizeX >> sizeY >> filename >> volume >> loop >> minDistance;
			
			sf::RectangleShape * rect = new sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
			rect->setPosition(x, y);

			insertSound(rect, filename, volume, loop);

		}
	}

	printf("Loaded %d Weenie Hut Juniors! n", numEvents);

	ifstream.close(); 

}

void EventHandler::insertSound(sf::RectangleShape * rectangle, std::string fileName, float volume, bool loop) {

	Sound * newEvent = new Sound();
	float pos;
	sf::Color color(255, 0, 0, 30);

	numEvents++;

	newEvent->eventArea = rectangle;
	newEvent->type = "SOUND";
	newEvent->filename = fileName;

	pos = rectangle->getPosition().x;

	newEvent->eventArea->setFillColor(color);

	newEvent->sound = new sf::Music();
	newEvent->sound->openFromFile(fileName);
	newEvent->sound->setPosition(rectangle->getPosition().x, rectangle->getPosition().y, 0);
	newEvent->sound->setVolume(volume);
	newEvent->sound->setLoop(loop);
	newEvent->sound->setMinDistance(100000.0f);

	selected = events.insert(std::make_pair(pos, newEvent));

}

void EventHandler::draw(sf::RenderWindow * window)
{
	for (eit = events.begin(); eit != events.end(); ) {
		window->draw(*(eit++)->second->eventArea);
	}
}

std::map<float, Event *>::iterator EventHandler::containment(sf::Vector2f mouse) {

	for (eit = events.begin(); eit != events.end(); eit++) {
		if (eit->second != NULL) {
			if (eit->second->eventArea != NULL) {
				if (eit->second->eventArea->getGlobalBounds().contains(mouse)) {
					return eit;
				}
			}
		}
		
	}

	return events.end();
}

void Spawner::trigger() {

}

bool Spawner::isTriggered() {
	
	return false;
}

void Spawner::clean() {



}

void Sound::trigger() {

	sound->play();

}

bool Sound::isTriggered() {

	if (sound->getPlayingOffset() != sf::Time::Zero) 
		 return false;
	else return true; 

}

void Sound::clean() {

	sound->stop();
	delete(eventArea);

}

void Switch::trigger() {


}

bool Switch::isTriggered() {
	return false;
}

void Switch::clean()
{

}

void SwitchEffect::trigger() {

}

bool SwitchEffect::isTriggered() {
	
	return false;

}

void SwitchEffect::clean()
{

}
