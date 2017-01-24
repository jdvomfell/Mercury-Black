#include "GameEngine.h"
#include "MainMenu.h"

int main() {

	sf::Clock clock;
	GameEngine engine;

	engine.init();

	engine.changeState(MainMenu::instance(&engine));

	while (engine.isRunning()) {

		sf::Time timePassed = clock.restart();
		float deltaTime = timePassed.asSeconds();

		engine.handleEvents();
		engine.update(deltaTime);
		engine.render(deltaTime);

	}

	engine.clean();

	return 0;
}