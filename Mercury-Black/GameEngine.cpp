#include "GameEngine.h"
#include "GameState.h"

#include <iostream>

void GameEngine::init() {

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Project Mercury Black", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 600, SDL_WINDOW_SHOWN);

	screen = SDL_GetWindowSurface(window);

	bgColor = SDL_MapRGB(screen->format, 0, 0, 0);

	running = true;

	return;
}

void GameEngine::clean() {

	for (size_t i = 0; i < states.size(); i++) {
		states[i]->clean();
	}

	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);

	SDL_Quit();

}

void GameEngine::changeState(GameState * state) {

	if (!states.empty()) {
		states.back()->clean();
		states.pop_back();
	}

	states.push_back(state);
	states.back()->init();

}

void GameEngine::pushState(GameState * state) {

	states.push_back(state);
	states.back()->init();

}

void GameEngine::popState() {

	if (!states.empty()) {
		states.back()->clean();
		states.pop_back();
	}

}

void GameEngine::handleEvents() {

	states.back()->handleEvent(this);

}

void GameEngine::update() {

	states.back()->update(this);

}

void GameEngine::render() {

	SDL_FillRect(screen, NULL, bgColor);

	for (size_t i = 0; i < states.size(); i++)
		states[i]->render(this);

	SDL_UpdateWindowSurface(window);

}

bool GameEngine::isRunning() {

	return running;

}

void GameEngine::quit() {
	
	running = false;

}