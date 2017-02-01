#include "GameEngine.h"
#include "MainMenu.h"
#include "Fade.h"

int main() {

	sf::Clock clock;
	GameEngine engine;

	engine.init();

	engine.pushState(TransitionState::instance(&engine));
	engine.pushState(FadeOut::instance(&engine));

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