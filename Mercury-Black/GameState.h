#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameEngine.h"

class GameState {

public:

	GameEngine * engine;

	virtual void init() = 0;
	virtual void clean() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvent() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	void changeState(GameEngine * engine, GameState * state) { 
		engine->changeState(state); 
	}

protected:

	GameState() {}

};

#endif