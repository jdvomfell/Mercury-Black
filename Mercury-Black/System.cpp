#include "System.h"
#include "CollisionHelper.h"
#include "Hitbox.h"

#include <cmath>

/* Do Not Edit CONSTS Without Discussing Gameplay Implications First */
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

			else if (world->name[entityID].name == "heart")
				scriptHeart(world, entityID);

			else if (world->name[entityID].name == "wisp")
				scriptWisp(world, entityID, dt);

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

#define ANIMATION_MASK (INPUT | SPRITE | SCRIPT)

void animationSystem(World * world, float dt) {

	Sprite * s;
	Input * i;
	ScriptParameters * sp;

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & ANIMATION_MASK) == ANIMATION_MASK) {

			s = &(world->sprite[entityID]);
			i = &(world->input[entityID]);
			sp = &(world->scriptParameters[entityID]);

			if (i->left)
				s->sprite.setTextureRect(sf::IntRect((int)s->sprite.getLocalBounds().width, 0, (int)-s->sprite.getLocalBounds().width, (int)s->sprite.getLocalBounds().height));
			else if (i->right)
				s->sprite.setTextureRect(sf::IntRect(0, 0, (int)s->sprite.getLocalBounds().width, (int)s->sprite.getLocalBounds().height));

			s->sprite.setTexture(*s->animationManager.getCurrentTexture());
			s->sprite.setOrigin(sf::Vector2f(s->sprite.getLocalBounds().width / 2, s->sprite.getLocalBounds().height / 2));

			/* Allow Animation Changes If Current Animation Has Ended */
			if (s->animationManager.updateAnimation(dt) == 1) {
				sp->currentState = NO_STATE;

			}

		}

	}

}

#define TAKE_DAMAGE_MASK (HEALTH)
#define DEAL_DAMAGE_MASK (STATS | SCRIPT)

void damageSystem(World * world, float dt, HitboxMap * hitboxMap) {

	Health * h;
	Stats * st;
	ScriptParameters * sp;

	bool dealDamage;

	std::string hurtID;
	std::string damageID;
	std::multimap<std::string, Hitbox *>::iterator hurtIt;
	std::multimap<std::string, Hitbox *>::iterator damageIt;

	sf::FloatRect hurtBox;
	sf::FloatRect damageBox;

	for (int damageTakerID = 0; damageTakerID < MAX_ENTITIES; damageTakerID++) {

		world->health[damageTakerID].hurtTimer -= dt;

		if ((world->mask[damageTakerID] & TAKE_DAMAGE_MASK) == TAKE_DAMAGE_MASK && world->health[damageTakerID].hurtTimer <= 0) {

			h = &(world->health[damageTakerID]);

			if ((world->mask[damageTakerID] & ANIMATION_MASK) == ANIMATION_MASK) {
				hurtID = world->sprite[damageTakerID].animationManager.getCurrentTextureID();
				hurtIt = hitboxMap->hurtBoxes.find(hurtID);
			}
			else {
				hurtIt = hitboxMap->hurtBoxes.end();
			}

			for (int damageDealerID = 0; damageDealerID < MAX_ENTITIES; damageDealerID++) {

				dealDamage = false;

				if ((world->mask[damageDealerID] & DEAL_DAMAGE_MASK) == DEAL_DAMAGE_MASK && world->scriptParameters[damageDealerID].currentState == ATTACK_STATE) {

					if ((world->mask[damageDealerID] & ANIMATION_MASK) == ANIMATION_MASK) {
						damageID = world->sprite[damageDealerID].animationManager.getCurrentTextureID();
						damageIt = hitboxMap->damageBoxes.find(damageID);
					}
					else {
						damageIt = hitboxMap->damageBoxes.end();
					}

					/* See If Damage Should Be Dealt */

					//if (hurtIt == hitboxMap->hurtBoxs.end() && damageIt == hitboxMap->damageBoxs.end()) {

						/* Check The Bounds Of The Damage Dealer And Damage Taker Against Each Other */

					//	if ((world->sprite[damageTakerID].sprite.getGlobalBounds().intersects(world->sprite[damageDealerID].sprite.getGlobalBounds()) == true) && (damageDealerID != damageTakerID)) {
					//		printf("No Boxes\n");
					//		dealDamage = true;
					//	}

					//}

					//else if (hurtIt == hitboxMap->hurtBoxs.end()) {

						/* Check Each Hurt Box Against The Bounds Of The Damage Dealer */

					//	do {
							
					//		damageBox = damageIt->second->box.getLocalBounds();
					//		damageBox.top = world->position[damageDealerID].y;
					//		damageBox.left = world->position[damageDealerID].x;

					//		if (damageBox.intersects(world->sprite[damageTakerID].sprite.getGlobalBounds()) && (damageDealerID != damageTakerID)) {
					//			printf("Only Damage\n");
					//			dealDamage = true;
					//			break;
					//		}

					//		damageIt++;

					//	} while (damageIt != hitboxMap->damageBoxs.upper_bound(damageID));

					//}

					//else if (damageIt == hitboxMap->damageBoxs.end()) {

						/* Check Each Damage Box Against The Bounds Of The Damage Taker */

					//	do {

					//		hurtBox = hurtIt->second->box.getLocalBounds();
					//		hurtBox.top = world->position[damageTakerID].y;
					//		hurtBox.left = world->position[damageTakerID].x;

					//		if (hurtBox.intersects(world->sprite[damageDealerID].sprite.getGlobalBounds()) && (damageDealerID != damageTakerID)) {
					//			printf("Only Hurt\n");
					//			dealDamage = true;
					//			break;
					//		}

					//		hurtIt++;

					//	} while (hurtIt != hitboxMap->hurtBoxs.upper_bound(hurtID));

					//}
					
					//else {
					if (hurtIt != hitboxMap->hurtBoxs.end() && damageIt != hitboxMap->damageBoxs.end()) {

						/* Check Each Damage Box Against Each Hurt Box */

						do {

							hurtIt = hitboxMap->hurtBoxes.find(hurtID);

							damageBox = damageIt->second->box.getLocalBounds();
							damageBox.top += world->sprite[damageDealerID].sprite.getGlobalBounds().top;
							damageBox.left += world->sprite[damageDealerID].sprite.getGlobalBounds().left;

							do {

								hurtBox = hurtIt->second->box.getLocalBounds();
								hurtBox.top += world->sprite[damageTakerID].sprite.getGlobalBounds().top;
								hurtBox.left += world->sprite[damageTakerID].sprite.getGlobalBounds().left;

								if (damageBox.intersects(hurtBox) && (damageDealerID != damageTakerID)) {
									printf("YO\n");
									dealDamage = true;
									break;
								}

								hurtIt++;

							} while (hurtIt != hitboxMap->hurtBoxes.upper_bound(hurtID));

							damageIt++;
						} while (damageIt != hitboxMap->damageBoxes.upper_bound(damageID));

					}

					/* If One Intersects Deal Damage */

					if (dealDamage) {

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
				v->x = -v->speed * v->speedUp;
			if (i->right)
				v->x = v->speed * v->speedUp;
			if ((i->left && i->right) || (!i->left && !i->right))
				v->x = 0.0f;

			if ((world->mask[entityID] & FLYING) == FLYING) {

				if (i->up)
					v->y = -v->speed * v->speedUp;
				if (i->down)
					v->y = v->speed * v->speedUp;
				if ((i->up && i->down) || (!i->up && !i->down))
					v->y = 0.0f;
			
			}

			else {

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

			}

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

void shapeCollSystem(World * world, PlatformMap * platformMap) {

	CollisionHelper * entity = new CollisionHelper;

	bool collision = true;
	float overlap;
	float overlapBuff;
	sf::ConvexShape * shape;
	sf::Sprite * sprite;
	sf::Sprite tempSprite;

	sf::Vector2f shapeProjection;
	sf::Vector2f entityProjection;
	
	sf::Vector2f entityTopNormal;
	sf::Vector2f entityBottomNormal; 
	sf::Vector2f entityLeftNormal;
	sf::Vector2f entityRightNormal; 
	sf::Vector2f shapeNormal;
	sf::Vector2f smallestNormal;

	std::map<float, sf::ConvexShape *>::iterator it;

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & COLLISION_MASK) == COLLISION_MASK) {

			sprite = &world->sprite[entityID].sprite;
			tempSprite = *sprite;
			tempSprite.setPosition(sprite->getPosition());
			tempSprite.setPosition(tempSprite.getPosition().x + world->velocity[entityID].x, tempSprite.getPosition().y + world->velocity[entityID].y);

			entityTopNormal = entity->getEntityNormal("top", sprite);
			entityBottomNormal = entity->getEntityNormal("bottom", sprite);
			entityLeftNormal = entity->getEntityNormal("left", sprite);
			entityRightNormal = entity->getEntityNormal("right", sprite);

			for (it = platformMap->map.begin(); it != platformMap->map.end(); it++) {

				overlap = FLT_MAX;
				overlapBuff = FLT_MAX;

				shape = it->second;
				collision = true;

				for (size_t i = 0; i < shape->getPointCount(); i++) {

					shapeNormal = platformMap->getEdgeNormal(i, shape);

					shapeProjection = platformMap->getProjection(shapeNormal, shape);
					entityProjection = entity->getEntityProjection(shapeNormal, tempSprite);

					if (!entity->isCollision(entityProjection, shapeProjection) && collision == true)
					{
						shape->setFillColor(sf::Color::Black);
						collision = false;
						break;
					}
					else
					{

						overlapBuff = entity->getOverlap(shapeProjection, entityProjection);

						if (overlapBuff <= overlap)
						{
							overlap = overlapBuff;
							smallestNormal = shapeNormal;
						}
					}
				}

				entityProjection = entity->getEntityProjection(entityTopNormal, tempSprite);
				shapeProjection = platformMap->getProjection(entityTopNormal, shape);

				if (!entity->isCollision(shapeProjection, entityProjection) && collision == true)
				{
					shape->setFillColor(sf::Color::Black);
					collision = false;
					continue;
				}
				else
				{

					overlapBuff = entity->getOverlap(entityProjection, shapeProjection);

					if (overlapBuff <= overlap && shapeProjection.x <= entityProjection.y)
					{
						overlap = overlapBuff;
						smallestNormal = entityTopNormal;
					}
				}

				entityProjection = entity->getEntityProjection(entityBottomNormal, tempSprite);
				shapeProjection = platformMap->getProjection(entityBottomNormal, shape);

				if (!entity->isCollision(shapeProjection, entityProjection) && collision == true)
				{
					shape->setFillColor(sf::Color::Black);
					collision = false;
					continue;
				}
				else
				{
					overlapBuff = entity->getOverlap(entityProjection, shapeProjection);

					if (overlapBuff <= overlap && shapeProjection.y >= entityProjection.x && entityProjection.y > shapeProjection.y)
					{
						overlap = overlapBuff;
						smallestNormal = entityBottomNormal;
					}
				}

				entityProjection = entity->getEntityProjection(entityLeftNormal, tempSprite);
				shapeProjection = platformMap->getProjection(entityLeftNormal, shape);

				if (!entity->isCollision(shapeProjection, entityProjection) && collision == true)
				{
					shape->setFillColor(sf::Color::Black);
					collision = false;
					continue;
				}
				else
				{
					overlapBuff = entity->getOverlap(entityProjection, shapeProjection);

					if (overlapBuff <= overlap && shapeProjection.y >= entityProjection.x)
					{
						overlap = overlapBuff;
						smallestNormal = entityLeftNormal;
					}
				}

				entityProjection = entity->getEntityProjection(entityRightNormal, tempSprite);
				shapeProjection = platformMap->getProjection(entityRightNormal, shape);

				if (!entity->isCollision(shapeProjection, entityProjection) && collision == true)
				{
					shape->setFillColor(sf::Color::Black);
					collision = false;
					continue;
				}
				else
				{
					overlapBuff = entity->getOverlap(entityProjection, shapeProjection);

					if (overlapBuff <= overlap && shapeProjection.y >= entityProjection.x && entityProjection.y > shapeProjection.y)
					{
						overlap = overlapBuff;
						smallestNormal = entityRightNormal;
					}
				}

				//COLLISION DETECTED, CALCULATE MTV
				if (collision == true)
				{
					shape->setFillColor(sf::Color::Red);
					entity->stopCollision(world, entityID, overlap, smallestNormal);
					world->velocity[entityID].onGround = true;
					world->velocity[entityID].canJump = true;
					world->velocity[entityID].canDoubleJump = true;
				}
			}
		}
	}

	delete(entity);
}