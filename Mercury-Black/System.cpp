#include "System.h"
#include <cmath>

/* Do Not Edit CONSTS Without Discussing Gameplay Implications First */
#define DEACCELERATION_CONST 0.90f
#define GRAVITY_CONST 0.5f
#define JUMP_CONST -15.0f
#define NORMAL_UP sf::Vector2f(0, 1)
#define NORMAL_RIGHT sf::Vector2f(1, 0)

#define SCRIPT_MASK (NAME | SCRIPT)

void aiSystem(World * world, float dt) {

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & SCRIPT_MASK) == SCRIPT_MASK) {

			if (world->name[entityID].name == "player")
				scriptPlayer(world, dt);

			else if (world->name[entityID].name == "ceilingPlant")
				scriptPlant(world, entityID, dt);

			else if (world->name[entityID].name == "test")
				scriptTest(world, entityID, dt);

			else
				printf("ERROR: Could Not Find Entity AI: %s\n", world->name[entityID].name.c_str());

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

#define TAKE_DAMAGE_MASK (HEALTH)
#define DEAL_DAMAGE_MASK (STATS | SCRIPT)

void damageSystem(World * world, float dt) {

	Health * h;
	Stats * st;
	ScriptParameters * sp;

	for (int damageTakerID = 0; damageTakerID < MAX_ENTITIES; damageTakerID++) {

		world->health[damageTakerID].hurtTimer -= dt;

		if ((world->mask[damageTakerID] & TAKE_DAMAGE_MASK) == TAKE_DAMAGE_MASK && world->health[damageTakerID].hurtTimer <= 0) {

			h = &(world->health[damageTakerID]);

			for (int damageDealerID = 0; damageDealerID < MAX_ENTITIES; damageDealerID++) {

				if ((world->mask[damageDealerID] & DEAL_DAMAGE_MASK) == DEAL_DAMAGE_MASK && world->scriptParameters[damageDealerID].currentState == ATTACK_STATE) {

					if ((world->sprite[damageTakerID].sprite.getGlobalBounds().intersects(world->sprite[damageDealerID].sprite.getGlobalBounds()) == true) && (damageDealerID != damageTakerID)) {

						st = &(world->stats[damageDealerID]);
						sp = &(world->scriptParameters[damageDealerID]);

						h->current -= st->power;

						h->hurtTimer = 1.0f;

						if (world->health[damageTakerID].current <= 0)
							world->scriptParameters[damageTakerID].currentState = DEATH_STATE;

						printf("E: %d\n", world->health[damageTakerID].current);

					}

				}

			}

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

			if (i->jump) {

				if (v->canJump) {
					v->y = JUMP_CONST;
					v->onGround = false;
					v->canJump = false;
				}

				else if (v->canDoubleJump) {
					v->y = JUMP_CONST;
					v->canDoubleJump = false;
				}

				i->jump = false;

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

/*void animationSystem(World * world, float dt) {

Sprite * s;
Velocity * v;

for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

if ((world->mask[entityID] & ANIMATION_MASK) == ANIMATION_MASK) {

}

}

}*/

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
				v->canJump = true;
				v->onGround = true;
				v->canDoubleJump = true;

			}

			/* Don't Enter Bad Slopes */

			if (v->onGround == true) {

				if (v->x > 0 && (p->x + v->x) > rightVertex->position.x) {

					slopeCheck = ((rightCheck->position.y - rightVertex->position.y) / (rightCheck->position.x - rightVertex->position.x));

					if (slopeCheck < -1.8) {

						p->x = rightVertex->position.x;
						v->x = -0.1f;

					}

				}

				else if (v->x < 0 && (p->x + v->x) < leftVertex->position.x) {

					slopeCheck = ((leftVertex->position.y - leftCheck->position.y) / (leftVertex->position.x - leftCheck->position.x));

					if (slopeCheck > 1.8) {

						p->x = leftVertex->position.x;
						v->x = 0.1f;

					}

				}

			}

			/* Slide Down Step Slopes, Cancel Jump */

			if (v->onGround && std::abs(slope) > 1.8) {

				v->canJump = false;

				if (slope > 1.8 && v->x <= 0) {
					v->x = 0.5f;
				}

				else if (slope < -1.8 && v->x >= 0) {
					v->x = -0.5f;
				}

				v->y = GRAVITY_CONST;

			}

			if (p->y < ground - 30)
				v->onGround = false;
		}

	}

}

sf::Vector2f getEntityNormal(std::string side, sf::Sprite * entity) {
	sf::Vector2f p1, p2, edge, normal;

	//Get left side if leftSide = 1
	if (side == "left")
	{
		edge.x = 0;
		edge.y = entity->getLocalBounds().height - entity->getLocalBounds().top;
	}
	else if (side == "right")
	{
		edge.x = 0;
		edge.y = entity->getLocalBounds().top - entity->getLocalBounds().height;
	}
	else if (side == "top")
	{
		edge.x = entity->getLocalBounds().left - entity->getLocalBounds().width;
		edge.y = 0;
	}
	else if (side == "bottom")
	{
		edge.x = entity->getLocalBounds().width - entity->getLocalBounds().left;
		edge.y = 0;
	}

	normal.x = edge.y;
	normal.y = -edge.x;

	return normal;
}

sf::Vector2f getEntityProjection(sf::Vector2f normal, sf::Sprite * entity) {

	float min, max, projection;
	sf::Vector2f projReturn;
	sf::Vector2f unitNormal;

	unitNormal.x = normal.x / (sqrt(pow(normal.x, 2) + pow(normal.y, 2)));
	unitNormal.y = normal.y / (sqrt(pow(normal.x, 2) + pow(normal.y, 2)));

	normal = unitNormal;

	sf::Vector2f topLeft(entity->getGlobalBounds().left, entity->getGlobalBounds().top);
	sf::Vector2f topRight(entity->getGlobalBounds().left + entity->getGlobalBounds().width, entity->getGlobalBounds().top);
	sf::Vector2f bottomLeft(entity->getGlobalBounds().left, entity->getGlobalBounds().top + entity->getGlobalBounds().height);
	sf::Vector2f bottomRight(entity->getGlobalBounds().left + entity->getGlobalBounds().width, entity->getGlobalBounds().top + entity->getGlobalBounds().height);

	min = (topLeft.x * normal.x) + (topLeft.y * normal.y);
	max = min;

	projection = ((topLeft.x * normal.x) + (topLeft.y * normal.y));
	if (projection < min)
		min = projection;
	else if (projection > max)
		max = projection;

	projection = (bottomLeft.x * normal.x) + (bottomLeft.y * normal.y);
	if (projection < min)
		min = projection;
	else if (projection > max)
		max = projection;

	projection = (topRight.x * normal.x) + (topRight.y * normal.y);
	if (projection < min)
		min = projection;
	else if (projection > max)
		max = projection;

	projection = (bottomRight.x * normal.x) + (bottomRight.y * normal.y);
	if (projection < min)
		min = projection;
	else if (projection > max)
		max = projection;

	projReturn.x = min;
	projReturn.y = max;

	return projReturn;
}

bool isCollision(sf::Vector2f firstProj, sf::Vector2f secondProj) {

	return (firstProj.y < secondProj.x || secondProj.y < firstProj.x);

}

float getOverlap(sf::Vector2f shapeProj, sf::Vector2f entityProj) {

	float overlapLength = std::min(shapeProj.y, entityProj.y) - std::max(shapeProj.x, entityProj.x);

	return overlapLength;

}

void stopCollision(World * world, unsigned int entityID, float length, sf::Vector2f axis)
{

	sf::Vector2f unitNormal;
	sf::Vector2f mtv;

	unitNormal.x = axis.x / (sqrt(pow(axis.x, 2) + pow(axis.y, 2)));
	unitNormal.y = axis.y / (sqrt(pow(axis.x, 2) + pow(axis.y, 2)));

	mtv.x = unitNormal.x * length;
	mtv.y = unitNormal.y * length;

	if (mtv.x > 0)
		mtv.x += 0.01f;
	else if (mtv.x < 0)
		mtv.x += -0.01f;

	if (mtv.y > 0)
		mtv.y += 0.01f;
	else if (mtv.y < 0)
		mtv.y += -0.01f;

	world->position[entityID].x += mtv.x;
	world->position[entityID].y += mtv.y;

	world->velocity[entityID].x = 0;
	world->velocity[entityID].y = 0;

}

void shapeCollSystem(World * world, PlatformMap * platformMap) {

	bool collision = true;
	float overlap;
	float overlapBuff;
	sf::ConvexShape * currentShape;
	sf::Sprite * currentEntity;

	sf::Vector2f shapeProjection;
	sf::Vector2f entityProjection;
	sf::Vector2f shapeAxis;
	sf::Vector2f smallestAxis;

	std::map<float, sf::ConvexShape *>::iterator it;

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & COLLISION_MASK) == COLLISION_MASK) {

			currentEntity = &world->sprite[entityID].sprite;

			for (it = platformMap->map.begin(); it != platformMap->map.end(); it++) {

				overlap = FLT_MAX;
				overlapBuff = FLT_MAX;

				currentShape = it->second;
				collision = true;

				for (size_t i = 0; i < currentShape->getPointCount(); i++) {

					shapeAxis = platformMap->getEdgeNormal(i, currentShape);

					shapeProjection = platformMap->getProjection(shapeAxis, currentShape);
					entityProjection = getEntityProjection(shapeAxis, currentEntity);

					if (isCollision(entityProjection, shapeProjection) && collision == true)
					{
						currentShape->setFillColor(sf::Color::Black);
						collision = false;
						break;
					}
					else
					{
						overlapBuff = getOverlap(shapeProjection, entityProjection);

						if (overlapBuff < overlap)
						{
							overlap = overlapBuff;
							smallestAxis = shapeAxis;
						}
					}
				}

				entityProjection = getEntityProjection(getEntityNormal("right", currentEntity), currentEntity);
				shapeProjection = platformMap->getProjection(getEntityNormal("right", currentEntity), currentShape);

				if (isCollision(shapeProjection, entityProjection) && collision == true)
				{
					currentShape->setFillColor(sf::Color::Black);
					collision = false;
					continue;
				}
				else
				{
					overlapBuff = getOverlap(entityProjection, shapeProjection);

					if (overlapBuff <= overlap)
					{
						overlap = overlapBuff;
						smallestAxis = getEntityNormal("right", currentEntity);
					}
				}

				entityProjection = getEntityProjection(getEntityNormal("left", currentEntity), currentEntity);
				shapeProjection = platformMap->getProjection(getEntityNormal("left", currentEntity), currentShape);

				if (isCollision(shapeProjection, entityProjection) && collision == true)
				{
					currentShape->setFillColor(sf::Color::Black);
					collision = false;
					continue;
				}
				else
				{
					overlapBuff = getOverlap(entityProjection, shapeProjection);

					if (overlapBuff <= overlap)
					{
						overlap = overlapBuff;
						smallestAxis = getEntityNormal("left", currentEntity);
					}
				}

				entityProjection = getEntityProjection(getEntityNormal("top", currentEntity), currentEntity);
				shapeProjection = platformMap->getProjection(getEntityNormal("top", currentEntity), currentShape);

				if (isCollision(shapeProjection, entityProjection) && collision == true)
				{
					currentShape->setFillColor(sf::Color::Black);
					collision = false;
					continue;
				}
				else
				{

					overlapBuff = getOverlap(entityProjection, shapeProjection);

					if (overlapBuff <= overlap)
					{
						overlap = overlapBuff;
						smallestAxis = getEntityNormal("top", currentEntity);
					}
				}

				entityProjection = getEntityProjection(getEntityNormal("bottom", currentEntity), currentEntity);
				shapeProjection = platformMap->getProjection(getEntityNormal("bottom", currentEntity), currentShape);

				if (isCollision(shapeProjection, entityProjection) && collision == true)
				{
					currentShape->setFillColor(sf::Color::Black);
					collision = false;
					continue;
				}
				else
				{

					overlapBuff = getOverlap(entityProjection, shapeProjection);

					if (overlapBuff <= overlap)
					{
						overlap = overlapBuff;
						smallestAxis = getEntityNormal("bottom", currentEntity);
					}
				}

				//COLLISION DETECTED, CALCULATE MTV
				if (collision == true)
				{
					currentShape->setFillColor(sf::Color::Red);
					stopCollision(world, entityID, overlap, smallestAxis);
				}
			}
		}
	}
}