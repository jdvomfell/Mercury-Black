#include "GameEngine.h"
#include "MainMenu.h"

int main() {

	GameEngine engine;

	engine.init();

	engine.changeState(MainMenu::instance(&engine));

	while (engine.isRunning()) {

		engine.handleEvents();
		engine.update();
		engine.render();

	}

	engine.clean();

	return 0;
}