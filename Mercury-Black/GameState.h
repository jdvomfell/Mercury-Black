#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameEngine.h"

class GameState {

public:

	virtual void init() = 0;
	virtual void clean() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvent(GameEngine * engine) = 0;
	virtual void update(GameEngine * engine) = 0;
	virtual void render(GameEngine * engine) = 0;

	void changeState(GameEngine * engine, GameState * state) { 
		engine->changeState(state); 
	}

protected:

	GameState() {}

};

#endif