#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML\Graphics.hpp>
#include "AnimationManager.h"
#include "Metaball.h"

const enum Direction {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

const enum states {
	NO_STATE = 0,
	ATTACK_STATE,
	DEFENCE_STATE,
	JUMP_STATE,
	SPAWN_STATE,
	NOT_SPAWNED_STATE, 
	DEATH_STATE,
	MOVEMENT_STATE
};

enum Component {

	EMPTY = 0,

	NAME = 1 << 0,
	INPUT = 1 << 1,
	SPRITE = 1 << 2,
	GRAVITY = 1 << 3,
	POSITION = 1 << 4,
	VELOCITY = 1 << 5,
	COLLISION = 1 << 6,
	SCRIPT = 1 << 7,
	HEALTH = 1 << 8, 
	STATS = 1 << 9,
	FLYING = 1 << 10

};

struct Name {

	std::string name;

};

struct Input {

	bool up;
	bool down;
	bool left;
	bool right;

	bool jump;

	bool attack;

	bool special;

	Direction lastDirection;

};

struct Sprite {

	MetaballSpawner * metaballSpawner;
	AnimationManager animationManager;
	sf::Sprite sprite;

};

struct Gravity {

	float weight;

};

struct Position {
	
	float x;
	float y;

};

struct Velocity {

	float x;
	float y;
	float speed;
	float speedUp;
	bool onGround;
	bool canJump;
	bool canDoubleJump;

};

struct ScriptParameters {

	float followDistMin;
	float followDistMax;
	float attackFrequency;
	float attackRangeMin;
	float attackRangeMax;
	float attackTimer;
	float secondsRemaining;
	int currentState;
	float spawnDistance;

};

struct Stats {

	int power;

};

struct Health {

	int max;
	int current;
	float hurtTimer;

};

#endif