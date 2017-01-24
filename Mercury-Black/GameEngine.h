#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "textureManager.h"
#include <SFML\Graphics.hpp>
#include <vector>

class GameState;

class GameEngine {

public:

	sf::RenderWindow window;
	TextureManager textureManager;

	void init();
	void clean();

	void changeState(GameState * state);
	void pushState(GameState * state);
	void popState();

	void handleEvents();
	void update(const float dt);
	void render(const float dt);

	bool isRunning();
	void quit();

private:
	
	void loadAllTextures();
	std::vector <GameState *> states;
	bool running;

};

#endif