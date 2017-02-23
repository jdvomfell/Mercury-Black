#include "Game.h"

#include "System.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Editor.h"

Game Game::game;

void Game::init() {

	world.textureManager = &engine->textureManager;

	createPlayer(&world, 900, 0);
	createTest(&world, 2000, 0);

	objectMap = ObjectMap(&engine->textureManager);
	objectMap.load();
	collisionMap.load();

	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(3);

	music.openFromFile("Music/drank.ogg");
	music.setVolume(20);
	music.setPosition(0, 0, 0);
	music.setMinDistance(1500.0f);
	music.setAttenuation(30);
	music.setLoop(true);
	music.play();

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
				engine->pushState(PauseMenu::instance(engine));
			
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

			if (event.key.code == sf::Keyboard::R)
				world.health[0].current = 0;

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

	if (world.health[0].current <= 0) {
		game.clean();
		game.init();
	}

	aiSystem(&world, dt);
	inputSystem(&world);
	gravitySystem(&world);
	collisionSystem(&world, &collisionMap);
	movementSystem(&world);
	shapeCollSystem(&world, &platformMap);
	//animationSystem(&world, dt, PLAYER);
	damageSystem(&world, dt);

	//listener.setPosition(world.position[0].x, world.position[0].y, 0);
	sf::Listener::setPosition(world.position[0].x, 0, world.position[0].y);

	view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 2.5f, engine->window.getDefaultView().getSize().y * 2.5f));
	view.setCenter(sf::Vector2f(world.position[PLAYER].x, world.position[PLAYER].y - view.getSize().y / 4));
	engine->window.setView(view);

	rect.setSize(sf::Vector2f(world.sprite[0].sprite.getLocalBounds().width, world.sprite[0].sprite.getLocalBounds().height));
	rect.setPosition(sf::Vector2f(world.sprite[0].sprite.getGlobalBounds().left, world.sprite[0].sprite.getGlobalBounds().top));

}

void Game::render(const float dt) {

	std::map<float, Object *>::iterator it;
	for (it = objectMap.map.begin(); it != objectMap.map.end(); it++)
		engine->window.draw(it->second->sprite);

	engine->window.draw(collisionMap.lines);

	engine->window.draw(rect);

	renderSystem(&world, &engine->window);

	for (pit = platformMap.map.begin(); pit != platformMap.map.end(); pit++)
		engine->window.draw(*(pit->second));
}