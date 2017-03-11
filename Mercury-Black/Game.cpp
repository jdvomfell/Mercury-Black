#include "Game.h"

#include "EventHandler.h"
#include "System.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Editor.h"
#include <map>

Game Game::game;

void Game::init() {

	world.textureManager = &engine->textureManager;

	createPlayer(&world, 900, 0);
	createTest(&world, 2000, 0);
	createHeart(&world, 900, 500);
	//createCeilingPlant(&world, 3000, 1000);



	/*Sound insertion code TEMPORARY*/

	sf::Vector2f size(800, 800);
	sf::RectangleShape * rectangle = new sf::RectangleShape(size);
	rectangle->setFillColor(sf::Color::Blue);
	eventMap.insertSound(rectangle, &world, "Music/drank.ogg", 80.0, true);
	rectangle->setPosition(1000, 0);

	/* End of sound code*/

	objectMap = ObjectMap(&engine->textureManager);
	objectMap.load();
	platformMap.load();

	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(3);
}

void Game::clean() {

	cleanWorld(&world);
	platformMap.clean();
	objectMap.clean();

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

			if (event.key.code == sf::Keyboard::L)
				drawPlatforms = !drawPlatforms;

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
	animationSystem(&world, dt);
	inputSystem(&world);
	gravitySystem(&world);
	shapeCollSystem(&world, &platformMap);
	movementSystem(&world);
	damageSystem(&world, dt);

	for (eventMap.eit = eventMap.events.begin(); eventMap.eit != eventMap.events.end(); eventMap.eit++)	
		if (eventMap.eit->second->isTriggered()) 
			eventMap.eit->second->trigger();


	//listener.setPosition(world.position[0].x, world.position[0].y, 0);
	sf::Listener::setPosition(world.position[0].x, 0, world.position[0].y);

	view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 3.5f, engine->window.getDefaultView().getSize().y * 3.5f));
	view.setCenter(sf::Vector2f(world.position[PLAYER].x, world.position[PLAYER].y - view.getSize().y / 4));
	engine->window.setView(view);

	/* Hitbox Temp */
	//rect.setSize(sf::Vector2f(world.sprite[0].sprite.getLocalBounds().width, world.sprite[0].sprite.getLocalBounds().height));
	//rect.setPosition(sf::Vector2f(world.sprite[0].sprite.getGlobalBounds().left, world.sprite[0].sprite.getGlobalBounds().top));

}

void Game::render(const float dt) {

	objectMap.drawBackground(&engine->window);

	engine->window.draw(rect);
	engine->window.draw(*eventMap.events.begin()->second->eventArea);

	renderSystem(&world, &engine->window);
	objectMap.drawForeground(&engine->window);

	if(drawPlatforms)
		for (pit = platformMap.map.begin(); pit != platformMap.map.end(); pit++)
			engine->window.draw(*(pit->second));

}