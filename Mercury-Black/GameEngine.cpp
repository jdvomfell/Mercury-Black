#include "GameEngine.h"
#include "GameState.h"

void GameEngine::init() {

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Project Mercury Black", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	running = true;

}

void GameEngine::clean() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

}

void GameEngine::changeState(GameState * state) {

	if (!states.empty())
		states.pop_back();

	states.push_back(state);
	states.back()->init();

}

void GameEngine::pushState(GameState * state) {

	states.push_back(state);
	states.back()->init();

}

void GameEngine::popState() {

	states.back()->clean();
	states.pop_back();

}

void GameEngine::handleEvents() {

	states.back()->handleEvent(this);

}

void GameEngine::update() {

	states.back()->update(this);

}

void GameEngine::render() {

	SDL_RenderClear(renderer);

	//for (int i = 0; i < states.size(); i++)
	//	states[i]->render(this);

	SDL_RenderPresent(renderer);

}

bool GameEngine::isRunning() {

	return running;

}

void GameEngine::quit() {
	
	running = false;

}