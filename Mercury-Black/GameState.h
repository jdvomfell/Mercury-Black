#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameEngine.h"

class GameState {

public:

	void init() {}
	void clean() {}

	void pause() {}
	void resume() {}

	void handleEvent(GameEngine * engine) {}
	void update(GameEngine * engine) {}
	void render(GameEngine * engine) {}

	void changeState(GameEngine * engine, GameState * state) { 
		engine->changeState(state); 
	}

};

#endif