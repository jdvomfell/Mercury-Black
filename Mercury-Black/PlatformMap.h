#ifndef PLATFORMMAP_H
#define PLATFORMMAP_H

#include "TextureManager.h"
#include <map>

struct Platform {

	sf::ConvexShape shape; 
	sf::Vector2f position; 

};

class PlatformMap {

	public:

		//float = 'x' position
		std::map<float, Platform *> platformMap;

		void save(); 
		void load(); 

		void add(); 
		void remove();
		
		PlatformMap() {}; 
		PlatformMap(TextureManager *); 

		TextureManager * textureManager;
};

#endif 