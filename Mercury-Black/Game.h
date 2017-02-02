#ifndef GAME_H
#define GAME_H

#include "GameState.h"

#include "Entity.h"
#include "ObjectMap.h"
#include "PlatformMap.h"
#include "CollisionMap.h"

#define PLAYER (0)

class Game : public GameState {

public:

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static Game* instance(GameEngine * engine) { game.engine = engine; return &game; }

protected:

	Game() {}

private:

	static Game game;

	sf::View view;

	ObjectMap objectMap;
	PlatformMap platformMap;
	CollisionMap collisionMap;
	
	World world;

};

#endif