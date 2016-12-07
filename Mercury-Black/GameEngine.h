#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL.h>
#include <vector>

class GameState;

class GameEngine {

public:

	SDL_Window * window;
	SDL_Renderer * renderer;

	void init();
	void clean();

	void changeState(GameState * state);
	void pushState(GameState * state);
	void popState();

	void handleEvents();
	void update();
	void render();

	bool isRunning();
	void quit();

private:

	std::vector <GameState *> states;
	bool running;

};

#endif