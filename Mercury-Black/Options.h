#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML/Window.hpp>

namespace KeyBinding {

	const int INK_KEY = 1;
	const int ATTACK_KEY = 2;

	const int MOVE_LEFT_KEY = 3;
	const int MOVE_RIGHT_KEY = 4;

	const int JUMP_KEY = 5;
	const int CROUCH_KEY = 6;

	const int MENU_KEY = 7;

}

class Options {

public:

	static Options * instance() { return &options; }

	void changeKeyBinding(int keyBinding, int setKey);

private:

	static Options options;

	Options() { }

	/* Gameplay */

	int inkKey;
	int attackKey;

	int moveLeftKey;
	int moveRightKey;

	int jumpKey;
	int crouchKey;

	/* Utility */

	int menuKey;

};

#endif