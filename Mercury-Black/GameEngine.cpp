#include "GameEngine.h"
#include "GameState.h"

void GameEngine::init() {

	window.create(sf::VideoMode(1200, 700, 32), "Project Mercury Black");
	
	loadAllTextures();

	running = true;

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

	window.clear(sf::Color::White);

	for (size_t i = 0; i < states.size(); i++)
		states[i]->render(this);

	window.display();

}

bool GameEngine::isRunning() {

	return running;

}

void GameEngine::quit() {
	
	running = false;

}

void GameEngine::loadAllTextures() {
	textureManager.loadTexture("idleHero1", "Textures/Idle.png");
}
