#include "System.h"
#include <cmath>

/* Do Not Edit CONSTS Without Discussing Gameplay Implications First */
#define DEACCELERATION_CONST 0.99f
#define GRAVITY_CONST 0.0005f
#define JUMP_CONST -0.4f

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

#define INPUT_MASK (INPUT | VELOCITY)

void inputSystem(World * world) {

	Input * i;
	Velocity * v;

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & INPUT_MASK) == INPUT_MASK) {

			i = &(world->input[entityID]);
			v = &(world->velocity[entityID]);

			/* INPUT */

			if (i->left)
				v->x = -v->speed;
			if (i->right)
				v->x = v->speed;

			if (i->jump && v->onGround) {
				v->y = JUMP_CONST;
				v->onGround = false;
			}

			/* DEACCELERATION MODS */

			if (v->x != 0)
				v->x *= DEACCELERATION_CONST;

			if ((v->x < 0 && v->x > -0.01f) || (v->x > 0 && v->x < 0.01f))
				v->x = 0;

		}

	}

}

#define GRAVITY_MASK (VELOCITY | GRAVITY)

void gravitySystem(World * world) {

	Gravity * g;
	Velocity * v;

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		g = &(world->gravity[entityID]);
		v = &(world->velocity[entityID]);

		v->y += GRAVITY_CONST * g->weight;

	}

}

#define MOVEMENT_MASK (POSITION | VELOCITY | INPUT)

void movementSystem(World * world) {

	Position * p;
	Velocity * v;

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & MOVEMENT_MASK) == MOVEMENT_MASK) {

			p = &(world->position[entityID]);
			v = &(world->velocity[entityID]);

			p->x += v->x;
			p->y += v->y;

		}

	}

}

#define COLLISION_MASK (POSITION | VELOCITY | COLLISION | GRAVITY)

void collisionSystem(World * world, CollisionMap * collisionMap) {

	Position * p;
	Velocity * v;

	float ground = 0.0f;
	float slope = 0.0f;
	sf::Vertex * leftVertex = NULL;
	sf::Vertex * rightVertex = NULL;


	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & COLLISION_MASK) == COLLISION_MASK) {

			p = &(world->position[entityID]);
			v = &(world->velocity[entityID]);

			if (collisionMap->findLeft(p->x) != collisionMap->map.end())
				leftVertex = collisionMap->findLeft(p->x)->second;
			else
				leftVertex = collisionMap->map.begin()->second;

			if (collisionMap->findRight(p->x) != collisionMap->map.end())
				rightVertex = collisionMap->findRight(p->x)->second;
			else
				rightVertex = collisionMap->map.begin()->second;

			slope = ((rightVertex->position.y - leftVertex->position.y) / (rightVertex->position.x - leftVertex->position.x));
			ground = ((slope * (p->x - leftVertex->position.x)) + (leftVertex->position.y));

			/* Check If On Course To Pass Through The Ground */
			/* Adjust To Hit The Ground */

			if ((p->y += v->y) > ground) {
				
				p->y = ground;
				v->y = 0;
				v->onGround = true;

			}

			/* Slide Down Step Slopes, Cancel Jump */

			if (v->onGround && std::abs(slope) > 1.2) {
				
				if (slope > 1.2 && v->x <= 0) {
					v->x = .005;
				}
				
				else if (slope < -1.2 && v->x >= 0) {
					v->x = -.005;
				}

				v->y = GRAVITY_CONST;
				v->onGround = false;

			}

		}

	}

} 