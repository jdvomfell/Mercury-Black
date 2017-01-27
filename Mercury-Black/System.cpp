#include "System.h"
#include <cmath>

/* Do Not Edit CONSTS Without Discussing Gameplay Implications First */
#define DEACCELERATION_CONST 0.90f
#define GRAVITY_CONST 0.5f
#define JUMP_CONST -15.0f

#define SCRIPT_MASK (NAME | SCRIPT)

void aiSystem(World * world, float dt) {
	
	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & SCRIPT_MASK) == SCRIPT_MASK) {

			if (world->name[entityID].name == "player")
				scriptPlayer(world, dt);

			else if (world->name[entityID].name == "test")
				scriptTest(world, entityID);

		}
	
	}
	
}



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
			if (i->left && i->right)
				v->x = 0.0f;

			if (i->jump && v->canJump) {
				v->y = JUMP_CONST;
				v->onGround = false;
				v->canJump = false;
			}

			/* DEACCELERATION MODS */

			if (v->x != 0)
				v->x *= DEACCELERATION_CONST;

			if ((v->x < 0 && v->x > -0.5f) || (v->x > 0 && v->x < 0.5f))
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

#define ANIMATION_MASK (VELOCITY | SPRITE)
/*
void animationSystem(World * world, float dt, int player) {

	Sprite * s;
	Velocity * v;

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & ANIMATION_MASK) == ANIMATION_MASK) {

			s = &(world->sprite[entityID]);
			v = &(world->velocity[entityID]);

			if (v->onGround) {
			
				if (v->x != 0)
					s->animationManager.changeAnimation("run");
				else
					s->animationManager.changeAnimation("idle");

			}
			
			else {
			
				//s->animationManager.changeAnimation("jump");
				s->animationManager.changeAnimation("inAir");
			
			}

			if (v->x < 0)
				s->sprite.setTextureRect(sf::IntRect(s->sprite.getLocalBounds().width, 0, -s->sprite.getLocalBounds().width, s->sprite.getLocalBounds().height));
			if (v->x > 0)
				s->sprite.setTextureRect(sf::IntRect(0, 0, s->sprite.getLocalBounds().width, s->sprite.getLocalBounds().height));

			s->animationManager.updateAnimation(dt);
			s->sprite.setTexture(*s->animationManager.getCurrentTexture());
			s->sprite.setOrigin(sf::Vector2f(s->sprite.getLocalBounds().width / 2, s->sprite.getLocalBounds().height));

		}

	}

}
*/
#define COLLISION_MASK (POSITION | VELOCITY | COLLISION | GRAVITY)

void collisionSystem(World * world, CollisionMap * collisionMap) {

	Position * p;
	Velocity * v;

	float ground = 0.0f;
	float slope = 0.0f;
	float slopeCheck = 0.0f;
	sf::Vertex * leftVertex = NULL;
	sf::Vertex * rightVertex = NULL;
	sf::Vertex * leftCheck = NULL;
	sf::Vertex * rightCheck = NULL;


	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & COLLISION_MASK) == COLLISION_MASK) {

			p = &(world->position[entityID]);
			v = &(world->velocity[entityID]);

			/* Find Nearby Collision Points */

			if (collisionMap->findLeft(p->x) != collisionMap->map.end()) {
				leftVertex = collisionMap->findLeft(p->x)->second;
				if ((--collisionMap->findLeft(p->x)) != collisionMap->map.end())
					leftCheck = (--collisionMap->findLeft(p->x))->second;
				else
					leftCheck = leftVertex;
			}
			else {
				leftVertex = collisionMap->map.begin()->second;
				leftCheck = collisionMap->map.begin()->second;
			}

			if (collisionMap->findRight(p->x) != collisionMap->map.end()) {
				rightVertex = collisionMap->findRight(p->x)->second;
				if ((++collisionMap->findRight(p->x)) != collisionMap->map.end())
					rightCheck = (++collisionMap->findRight(p->x))->second;
				else
					rightCheck = rightVertex;
			}
			else {
				rightVertex = collisionMap->map.begin()->second;
				rightCheck = collisionMap->map.begin()->second;
			}

			/* Calculate The Ground */

			slope = ((rightVertex->position.y - leftVertex->position.y) / (rightVertex->position.x - leftVertex->position.x));
			ground = ((slope * (p->x - leftVertex->position.x)) + (leftVertex->position.y));

			/* Check If On Course To Pass Through The Ground */
			/* Adjust To Hit The Ground */

			if ((p->y + v->y) > ground) {

				v->y = 0;
				p->y = ground;
				v->onGround = true;
				v->canJump = true;

			}

			/* Don't Enter Bad Slopes */

			if (v->onGround == true) {

				if (v->x > 0 && (p->x + v->x) > rightVertex->position.x) {

					slopeCheck = ((rightCheck->position.y - rightVertex->position.y) / (rightCheck->position.x - rightVertex->position.x));

					if (slopeCheck < -1.2) {

						p->x = rightVertex->position.x;
						v->x = -0.1f;

					}

				}

				else if (v->x < 0 && (p->x + v->x) < leftVertex->position.x) {

					slopeCheck = ((leftVertex->position.y - leftCheck->position.y) / (leftVertex->position.x - leftCheck->position.x));

					if (slopeCheck > 1.2) {

						p->x = leftVertex->position.x;
						v->x = 0.1f;

					}

				}

			}

			/* Slide Down Step Slopes, Cancel Jump */

			if (v->onGround && std::abs(slope) > 1.2) {

				v->canJump = false;
				
				if (slope > 1.2 && v->x <= 0) {
					v->x = 0.5f;
				}
				
				else if (slope < -1.2 && v->x >= 0) {
					v->x = -0.5f;
				}

				v->y = GRAVITY_CONST;

			}

		}

	}

} 