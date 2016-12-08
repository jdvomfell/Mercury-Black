#include "GameEngine.h"
#include "GameState.h"

int GameEngine::init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Video Init Failed! SDL_Error: %s\n", SDL_GetError);
		return 0;
	}

	window = SDL_CreateWindow("Project Mercury Black", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("SDL Window Creation Failed! SDL_Error: &s\n", SDL_GetError);
		return 0;
	}

	screen = SDL_GetWindowSurface(window);

	bgColor = SDL_MapRGB(screen->format, 0, 0, 0);

	running = true;

	return 1;
}

void GameEngine::clean() {

	for (int i = 0; i < states.size(); i++) {
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

	for (int i = 0; i < states.size(); i++)
		states[i]->render(this);

	SDL_UpdateWindowSurface(window);

}

bool GameEngine::isRunning() {

	return running;

}

void GameEngine::quit() {
	
	running = false;

}