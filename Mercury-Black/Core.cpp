#include "GameEngine.h"
#include "Gamestate.h"
#include <SDL.h>

int main(int argc, char ** argv) {

	GameEngine engine;

	engine.init();

	// Add State And PushBack

	while (engine.isRunning()) {

		engine.handleEvents();
		engine.update();
		engine.render();

		engine.quit();

	}

	engine.clean();

	return 0;
}