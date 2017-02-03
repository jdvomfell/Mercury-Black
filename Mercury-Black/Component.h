#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML\Graphics.hpp>
#include "AnimationManager.h"

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

};

struct Sprite {

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
	bool onGround;
	bool canJump;

};

struct ScriptParameters {

	float followDistMin;
	float followDistMax;
	float attackFrequency;
	float attackRangeMin;
	float attackRangeMax;
	float secondsRemaining;
	int currentState;
};

#endif