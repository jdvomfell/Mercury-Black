#ifndef PLATFORMMAP_H
#define PLATFORMMAP_H

#include "TextureManager.h"
#include <map>

struct Platform {

	sf::ConvexShape * shape; 
	sf::Vector2f position; 
	sf::Vector2f proj;
};

class PlatformMap {

	public:

		Platform * platform;
		
		//float = 'x' position
		std::map<float, Platform *> platformMap;
		std::map<float, Platform *>::iterator pit;

		void save(); 
		void load(); 
		sf::Vector2f getEdgeNormal(int vertex, sf::ConvexShape shape);
		sf::Vector2f getProjection(sf::Vector2f normal, sf::ConvexShape shape);
		
		void add(sf::Vector2f position, unsigned int vertices); 
		void remove();
		
		PlatformMap() {};
		//PlatformMap(TextureManager *); 

		TextureManager * textureManager;

};

#endif 