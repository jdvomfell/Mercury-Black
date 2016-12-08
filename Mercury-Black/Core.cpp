#include "GameEngine.h"
#include "MainMenu.h"

int main(int argc, char ** argv) {

	GameEngine engine;

	if (engine.init() == 0) {
		printf("Closing: Could Not Initialize!\n");
		return -1;
	}

	engine.changeState(MainMenu::instance());

	while (engine.isRunning()) {

		engine.handleEvents();
		engine.update();
		engine.render();

	}

	engine.clean();

	return 0;
}