#include "Game.h"

#include "System.h"
#include "MainMenu.h"
#include "Editor.h"

Game Game::game;

void Game::init() {

	world.textureManager = &engine->textureManager;

	playerID = createPlayer(&world, 0, 0);
	createTest(&world, sf::Vector2f(200, 0));
	collisionMap.load();

}

void Game::clean() {

	cleanWorld(&world);
	collisionMap.clean();

}

void Game::pause() {

}

void Game::resume() {

}

void Game::handleEvent() {

	sf::Event event;

	if (engine->window.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::Closed:

			engine->quit();

			break;

		case sf::Event::MouseButtonPressed:

			if (event.mouseButton.button == sf::Mouse::Left)
				world.input[playerID].attack = true;
			
			break;

		case sf::Event::KeyPressed:

			if (event.key.code == sf::Keyboard::Escape)
				engine->changeState(MainMenu::instance(engine));

			if (event.key.code == sf::Keyboard::Tab)
				engine->changeState(Editor::instance(engine));

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

void Game::update(const float dt) {

	inputSystem(&world);
	gravitySystem(&world);
	collisionSystem(&world, &collisionMap);
	animationSystem(&world, dt, playerID);
	movementSystem(&world);

	view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 2, engine->window.getDefaultView().getSize().y * 2));
	view.setCenter(sf::Vector2f(world.position[playerID].x, world.position[playerID].y));
	engine->window.setView(view);

}

void Game::render(const float dt) {

	engine->window.draw(collisionMap.lines);

	renderSystem(&world, &engine->window);

}