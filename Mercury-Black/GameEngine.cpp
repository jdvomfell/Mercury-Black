#include "GameEngine.h"
#include "GameState.h"

void GameEngine::init() {

	window.create(sf::VideoMode(1200, 700, 32), "Project Mercury Black");
	window.setFramerateLimit(60);
	
	textureManager.loadAllTextures();

	running = true;

}

void GameEngine::clean() {

	for (size_t i = 0; i < states.size(); i++) {
		states[i]->clean();
	}

}

void GameEngine::changeState(GameState * state) {

	if (!states.empty()) {
		for (size_t i = 0; i < states.size(); i++) {
			states[i]->clean();
		}
		states.clear();
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

	states.back()->handleEvent();

}

void GameEngine::update(const float dt) {

	states.back()->update(dt);

}

void GameEngine::render(const float dt) {

	window.clear(sf::Color(171, 226, 252, 0));

	for (size_t i = 0; i < states.size(); i++)
		states[i]->render(dt);

	window.display();

}

bool GameEngine::isRunning() {

	return running;

}

void GameEngine::quit() {
	
	running = false;

}