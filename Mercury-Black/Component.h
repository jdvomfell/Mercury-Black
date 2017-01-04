#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML\Graphics.hpp>

enum Component {

	EMPTY =		0,

	NAME =		1 << 0,
	INPUT =		1 << 1,
	SPRITE =	1 << 2,
	GRAVITY =	1 << 3,
	POSITION =	1 << 4,
	VELOCITY =	1 << 5,
	COLLISION =	1 << 6,

};

struct Name {

	std::string name;

};

struct Input {

	bool Up;
	bool Down;
	bool Left;
	bool Right;

	bool Jump;

	bool Ink;
	bool Swing;

};

struct Sprite {

	sf::RectangleShape sprite;

};

struct Gravity {

	float weight;
	bool onGround;

};

struct Position {
	
	float x;
	float y;

};

struct Velocity {

	float x;
	float y;

};

#endif