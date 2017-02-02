#include "Game.h"

#include "System.h"
#include "MainMenu.h"
#include "Editor.h"

Game Game::game;

void Game::init() {

	world.textureManager = &engine->textureManager;

	int test = createTest(&world, sf::Vector2f(1000, 0));
	createPlayer(&world, 900, 0);

	world.sprite[test].sprite.setTexture(*engine->textureManager.getTexture("player_run_1"));
	world.sprite[test].sprite.setOrigin(world.sprite[test].sprite.getLocalBounds().width / 2, world.sprite[test].sprite.getLocalBounds().height);

	createCeilingPlant(&world, 100, 1000);

	objectMap = ObjectMap(&engine->textureManager);
	objectMap.load();
	collisionMap.load();

	platformMap.add(sf::Vector2f(0, 500), 3);

}

void Game::clean() {

	cleanWorld(&world);
	collisionMap.clean();

}

void Game::handleEvent() {

	sf::Event event;

	if (engine->window.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::Closed:

			engine->quit();

			break;

		case sf::Event::KeyPressed:

			if (event.key.code == sf::Keyboard::Escape)
				engine->changeState(MainMenu::instance(engine));

			if (event.key.code == sf::Keyboard::Tab)
				engine->changeState(Editor::instance(engine));

			if (event.key.code == sf::Keyboard::W)
				world.input[PLAYER].jump = true;
			if (event.key.code == sf::Keyboard::S)
				world.input[PLAYER].down = true;
			if (event.key.code == sf::Keyboard::A)
				world.input[PLAYER].left = true;
			if (event.key.code == sf::Keyboard::D)
				world.input[PLAYER].right = true;

			if (event.key.code == sf::Keyboard::Space)
				world.input[PLAYER].attack = true;

			if (event.key.code == sf::Keyboard::LShift)
				world.input[PLAYER].special = true;

			break;

		case sf::Event::KeyReleased:

			if (event.key.code == sf::Keyboard::W)
				world.input[PLAYER].jump = false;
			if (event.key.code == sf::Keyboard::S)
				world.input[PLAYER].down = false;
			if (event.key.code == sf::Keyboard::A)
				world.input[PLAYER].left = false;
			if (event.key.code == sf::Keyboard::D)
				world.input[PLAYER].right = false;

			if (event.key.code == sf::Keyboard::Space)
				world.input[PLAYER].attack = false;

			if (event.key.code == sf::Keyboard::LShift)
				world.input[PLAYER].special = false;

			break;

		}

	}

}

void Game::update(const float dt) {

	aiSystem(&world, dt);
	inputSystem(&world);
	gravitySystem(&world);
	collisionSystem(&world, &collisionMap);
	//PUT shapeCollisionSystem here
	//animationSystem(&world, dt, PLAYER);
	movementSystem(&world);

	view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 2, engine->window.getDefaultView().getSize().y * 2));
	view.setCenter(sf::Vector2f(world.position[PLAYER].x, world.position[PLAYER].y - view.getSize().y / 5));
	engine->window.setView(view);

}

void Game::render(const float dt) {

	std::map<float, Object *>::iterator it;
	for (it = objectMap.map.begin(); it != objectMap.map.end(); it++)
		engine->window.draw(it->second->sprite);

	engine->window.draw(collisionMap.lines);

	renderSystem(&world, &engine->window);

	for (platformMap.pit = platformMap.platformMap.begin(); platformMap.pit != platformMap.platformMap.end(); platformMap.pit++)
		engine->window.draw(*(platformMap.pit->second->shape));
}