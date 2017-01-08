#include "Game.h"

#include "System.h"

Game Game::game;

void Game::init() {

	playerID = createPlayer(&world, 0, 0);

	collisionMap.load();

}

void Game::clean() {

	collisionMap.clean();

}

void Game::pause() {

}

void Game::resume() {

}

void Game::handleEvent(GameEngine* engine) {

	sf::Event event;

	if (engine->window.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::Closed:

			clean();
			engine->quit();

			break;

		case sf::Event::MouseButtonPressed:

			if (event.mouseButton.button == sf::Mouse::Left)
				world.input[playerID].attack = true;
			
			break;

		case sf::Event::KeyPressed:

			if (event.key.code == sf::Keyboard::W)
				world.input[playerID].up = true;
			if (event.key.code == sf::Keyboard::S)
				world.input[playerID].down = true;
			if (event.key.code == sf::Keyboard::A)
				world.input[playerID].left = true;
			if (event.key.code == sf::Keyboard::D)
				world.input[playerID].right = true;

			if (event.key.code == sf::Keyboard::Space)
				world.input[playerID].jump = true;

			if (event.key.code == sf::Keyboard::LShift)
				world.input[playerID].special = true;

			break;

		case sf::Event::KeyReleased:

			if (event.key.code == sf::Keyboard::W)
				world.input[playerID].up = false;
			if (event.key.code == sf::Keyboard::S)
				world.input[playerID].down = false;
			if (event.key.code == sf::Keyboard::A)
				world.input[playerID].left = false;
			if (event.key.code == sf::Keyboard::D)
				world.input[playerID].right = false;

			if (event.key.code == sf::Keyboard::Space)
				world.input[playerID].jump = false;

			if (event.key.code == sf::Keyboard::LShift)
				world.input[playerID].special = false;

			break;

		}

	}

}

void Game::update(GameEngine* engine) {

	inputSystem(&world);
	collisionSystem(&world, &collisionMap);
	movementSystem(&world);

}

void Game::render(GameEngine* engine) {

	engine->window.draw(collisionMap.lines);

	renderSystem(&world, &engine->window);

}