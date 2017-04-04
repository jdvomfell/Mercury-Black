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

	Input * dti;
	Health * dth;
	Sprite * dts;
	Position * dtp;
	ScriptParameters * dtsp;

	Input * ddi;
	Stats * ddst;
	Sprite * dds;
	Position * ddp;
	ScriptParameters * ddsp;

	std::string hurtID;
	std::string damageID;
	std::vector<sf::RectangleShape> hurtBoxes;
	std::vector<sf::RectangleShape> damageBoxes;

	/* Find An Entity That Can Take Damage */

	for (int damageTakerID = 0; damageTakerID < MAX_ENTITIES; damageTakerID++) {

		if ((world->mask[damageTakerID] & TAKE_DAMAGE_MASK) != TAKE_DAMAGE_MASK)
			continue;

		/* If The Entity Is Still Invaunerable Reduce It's Invaunerability Timer */

		if (world->health[damageTakerID].hurtTimer > 0) {
			world->health[damageTakerID].hurtTimer -= dt;
			continue;
		}

		/* Get Damage Taker Info */

		dti = &(world->input[damageTakerID]);
		dth = &(world->health[damageTakerID]);
		dts = &(world->sprite[damageTakerID]);
		dtp = &(world->position[damageTakerID]);
		dtsp = &(world->scriptParameters[damageTakerID]);

		/* Get The Hitboxes For The Damage Taker */

		hurtBoxes.clear();

		if (!dts->animationManager.isEmpty()) {
			
			hurtID = dts->animationManager.getCurrentTextureID();
			
			if (dti->lastDirection == LEFT)
				hurtBoxes = hitboxMap->getFlippedHitboxes(hurtID, HITBOXTYPE_HURT);
			else
				hurtBoxes = hitboxMap->getHitboxes(hurtID, HITBOXTYPE_HURT);
		}

		/* Move The Hitboxes To The Entities Position */

		for (int i = 0; i < hurtBoxes.size(); i++)
			hurtBoxes[i].move(dtp->x, dtp->y);

		/* Find An Entity That Can Deal Damage */

		for (int damageDealerID = 0; damageDealerID < MAX_ENTITIES; damageDealerID++) {

			if ((world->mask[damageDealerID] & DEAL_DAMAGE_MASK) != DEAL_DAMAGE_MASK || world->scriptParameters[damageDealerID].currentState != ATTACK_STATE)
				continue;

			/* Don't Let Entities Kill Themselves */

			if (damageDealerID == damageTakerID)
				continue;

			/* Get Damage Dealer Info */

			ddi = &(world->input[damageDealerID]);
			dds = &(world->sprite[damageDealerID]);
			ddp = &(world->position[damageDealerID]);
			ddst = &(world->stats[damageDealerID]);
			ddsp = &(world->scriptParameters[damageDealerID]);

			/* Get The Hitboxes For The Damage Dealer */

			damageBoxes.clear();

			if (!dds->animationManager.isEmpty()) {
				
				damageID = dds->animationManager.getCurrentTextureID();

				if (ddi->lastDirection == LEFT)
					damageBoxes = hitboxMap->getFlippedHitboxes(damageID, HITBOXTYPE_DAMAGE);
				else
					damageBoxes = hitboxMap->getHitboxes(damageID, HITBOXTYPE_DAMAGE);

			}

			/* Move The Hitboxes To The Entities Position */

			for (int i = 0; i < damageBoxes.size(); i++)
				damageBoxes[i].move(ddp->x, ddp->y);

			/* Check Each Damage Box Against Each Hurt Box */

			for (size_t i = 0; i < damageBoxes.size(); i++) {
				for(size_t j = 0; j < hurtBoxes.size(); j++){

					printf("Check\n");

					/* If One Intersects Deal Damage */

					if (damageBoxes[i].getGlobalBounds().intersects(hurtBoxes[j].getGlobalBounds())) {

						dth->current -= ddst->power;
						dth->hurtTimer = 1.0f;

						if (dth->current <= 0)
							dtsp->currentState = DEATH_STATE;

						printf("E: %d\n", dth->current);
					
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

			if ((i->left && i->right) || (!i->left && !i->right))
				v->x = 0.0f;

			else if (i->left) {
				v->x = -v->speed * v->speedUp;
				i->lastDirection = LEFT;
			}

			else if (i->right) {
				v->x = v->speed * v->speedUp;
				i->lastDirection = RIGHT;
			}

			if ((world->mask[entityID] & FLYING) == FLYING) {

				if ((i->up && i->down) || (!i->up && !i->down))
					v->y = 0.0f;
				else if (i->up)
					v->y = -v->speed * v->speedUp;
				else if (i->down)
					v->y = v->speed * v->speedUp;
			
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

	/* Find An Entity That Can Collide With Platforms */

	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {

		if ((world->mask[entityID] & COLLISION_MASK) == COLLISION_MASK) {

			sprite = &world->sprite[entityID].sprite;
			tempSprite = *sprite;
			tempSprite.setPosition(sprite->getPosition());
			tempSprite.setPosition(tempSprite.getPosition().x + world->velocity[entityID].x, tempSprite.getPosition().y + world->velocity[entityID].y);

			/* Retrieve The Entity Normals */

			entityTopNormal = entity->getEntityNormal("top", sprite);
			entityBottomNormal = entity->getEntityNormal("bottom", sprite);
			entityLeftNormal = entity->getEntityNormal("left", sprite);
			entityRightNormal = entity->getEntityNormal("right", sprite);

			/* Check The Entity Against Platforms */

			for (it = platformMap->map.begin(); it != platformMap->map.end(); it++) {

				overlap = FLT_MAX;
				overlapBuff = FLT_MAX;

				shape = it->second;
				collision = true;

				/* Check Projections Against Each Normal Of The Shape */

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

				/* Check Projections Against Each Entity Projections */

				/* Entity Top Projections */

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

				/* Entity Bottom Projections */

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

				/* Entity Left Projections */

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

				/* Entity Right Projections */

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

				/* Collision Has Happened, Calculate And Apply The MTV */
				
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