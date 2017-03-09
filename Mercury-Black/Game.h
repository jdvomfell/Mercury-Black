#ifndef GAME_H
#define GAME_H

#include <SFML\Audio.hpp>

#include "GameState.h"

#include "Entity.h"
#include "ObjectMap.h"
#include "PlatformMap.h"
#include "CollisionMap.h"
#include "Options.h"

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

	Options * options = Options::instance();

	sf::View view;

	ObjectMap objectMap;
	PlatformMap platformMap;
	
	World world;

	sf::RectangleShape rect;

	bool drawPlatforms;

	std::map <float, sf::ConvexShape *>::iterator pit;

	sf::Music music;

};

#endif