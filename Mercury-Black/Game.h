#ifndef GAME_H
#define GAME_H

#include <SFML\Audio.hpp>

#include "GameState.h"

#include "EventHandler.h"
#include "Entity.h"
#include "ObjectMap.h"
#include "PlatformMap.h"
#include "CollisionMap.h"
#include "Metaball.h"
#include "Hitbox.h"
#include "Water.h"

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
	sf::View guiView;

	HitboxMap hitboxMap;
	ObjectMap objectMap;
	EventHandler eventMap;
	PlatformMap platformMap;
	WaterHandler waterHandler;
	MetaballHandler metaballHandler;

	World world;

	class HealthBar * healthBar;

	sf::RectangleShape rect;

	bool drawDebug;

	std::map <float, sf::ConvexShape *>::iterator pit;

	sf::Music music;

};

#endif