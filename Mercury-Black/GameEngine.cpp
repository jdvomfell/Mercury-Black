#include "GameEngine.h"
#include "GameState.h"

#include <iostream>

void GameEngine::init() {

	running = true;

	return;
}

void GameEngine::clean() {

	for (size_t i = 0; i < states.size(); i++) {
		states[i]->clean();
	}

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

	for (size_t i = 0; i < states.size(); i++)
		states[i]->render(this);

}

bool GameEngine::isRunning() {

	return running;

}

void GameEngine::quit() {
	
	running = false;

}