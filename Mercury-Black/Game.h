#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "Entity.h"
#include "CollisionMap.h"

class Game : public GameState {

public:

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvent(GameEngine* engine);
	void update(GameEngine* engine);
	void render(GameEngine* engine);

	static Game* instance() { return &game; }

protected:

	Game() {}

private:

	static Game game;

	CollisionMap collisionMap;
	World world;

	int playerID;

};

#endif