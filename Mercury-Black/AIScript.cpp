#include "AIScript.h"
#include <cmath>


void scriptTest(World * world, int entityID) {

	world->sprite[entityID].sprite.setColor(sf::Color::Black);

	scriptFollow(world, entityID,sf::Vector2f(world->position[0].x, world->position[0].y));
}

void scriptFollow(World * world, int entityID, sf::Vector2f position) {

	if (std::fabs(world->position[entityID].x - position.x) <=
		world->scriptParameter[entityID].followDistMax &&

		std::fabs(world->position[entityID].x - position.x) >=
		world->scriptParameter[entityID].followDistMin){
			
			if (world->position[entityID].x - position.x < 0) {
				world->input[entityID].right = true;
			}
	
			else {
				world->input[entityID].left = true;
			}
	}
	
}

void scriptAttack(World* world, int entityID, sf::Vector2f position) {

	if (std::fabs(world->position[entityID].x - position.x) <=
		world->scriptParameter[entityID].attackRangeMax &&

		std::fabs(world->position[entityID].x - position.x) >=
		world->scriptParameter[entityID].attackRangeMin) {

			world->input[entityID].attack = true;
	}

}

void scriptRetreat(World * world, int entityID, sf::Vector2f position) {

	if (std::fabs(world->position[entityID].x - position.x) <=
		world->scriptParameter[entityID].followDistMin) {

		if (world->position[entityID].x - position.x < 0) {
			world->input[entityID].right = true;
		}

		else {
			world->input[entityID].left = true;
		}
	}

}