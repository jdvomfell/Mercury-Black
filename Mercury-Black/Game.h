#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "Entity.h"
#include "CollisionMap.h"
#include "PlatformMap.h"

class Game : public GameState {

public:

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static Game* instance(GameEngine * engine) { game.engine = engine; return &game; }

protected:

	Game() {}

private:

	static Game game;

	sf::View view;

	CollisionMap collisionMap;

	PlatformMap platformMap; 
	
	World world;

	int playerID;

};

#endif