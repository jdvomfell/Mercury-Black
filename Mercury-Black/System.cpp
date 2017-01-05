#include "System.h"

#define RENDER_MASK (POSITION | SPRITE)

void renderSystem(World * world, sf::RenderWindow * window) {

	Sprite * s;
	Position * p;

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & RENDER_MASK) == RENDER_MASK) {

			s = &(world->sprite[entityID]);
			p = &(world->position[entityID]);

			s->sprite.setPosition(p->x, p->y);

			window->draw(s->sprite);

		}

	}

}

#define MOVEMENT_MASK (POSITION | VELOCITY | INPUT)

void movementSystem(World * world) {

	Input * i;
	Position * p;
	Velocity * v;

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & MOVEMENT_MASK) == MOVEMENT_MASK) {

			i = &(world->input[entityID]);
			p = &(world->position[entityID]);
			v = &(world->velocity[entityID]);

			v->x = 0;

			if (i->left)
				v->x = -v->speed;
			if (i->right)
				v->x = v->speed;

			p->x += v->x;
			p->y += v->y;

		}

	}

}

void collisionSystem(World * world) {

}