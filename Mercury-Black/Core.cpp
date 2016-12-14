#include "GameEngine.h"
#include "MainMenu.h"

int main(int argc, char ** argv) {

	GameEngine engine;

	engine.init();

	engine.changeState(MainMenu::instance());

	while (engine.isRunning()) {

		engine.handleEvents();
		engine.update();
		engine.render();

	}

	engine.clean();

	return 0;
}