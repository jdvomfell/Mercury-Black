#include "GameEngine.h"
#include "GameState.h"

void GameEngine::init() {

	window.create(sf::VideoMode(1200, 700, 32), "Project Mercury Black");
	window.setFramerateLimit(60);
	
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

	states.back()->handleEvent();

}

void GameEngine::update(const float dt) {

	states.back()->update(dt);

}

void GameEngine::render(const float dt) {

	window.clear(sf::Color::White);

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

void GameEngine::loadAllTextures() {

	textureManager.loadTexture("player_idle_1", "Textures/player_idle_1.png");
	textureManager.loadTexture("player_run_1", "Textures/player_run_1.png");
	textureManager.loadTexture("player_run_2", "Textures/player_run_2.png");
	textureManager.loadTexture("player_run_3", "Textures/player_run_3.png");
	textureManager.loadTexture("player_run_4", "Textures/player_run_4.png");
	textureManager.loadTexture("player_run_5", "Textures/player_run_5.png");
	textureManager.loadTexture("player_run_6", "Textures/player_run_6.png");

}