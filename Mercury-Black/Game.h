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
	CollisionMap collisionMap;
	
	World world;

	sf::Text slide1;
	sf::Text slide2;
	sf::Text slide3;
	sf::Text slide4;
	sf::Text slide5;
	sf::Text slide6;
	sf::Text slide7;
	sf::Text slide8;
	sf::Text slide9;
	sf::Text slide10;
	sf::Text slide11;
	sf::Text slide12;
	sf::Text slide13;
	sf::Text slide14;
	sf::Text slide15;
	sf::Text slide16;
	sf::Text slide17;
	sf::Text slide18;
	sf::Text slide19;
	sf::Text slide20;
	sf::Text slide21;
	sf::Text slide22;

	sf::Music music;

};

#endif