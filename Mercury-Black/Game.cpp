#include "Game.h"

#include "EventHandler.h"
#include "System.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Editor.h"
#include "MathFunctions.h"
#include "HealthBar.h"
#include <map>

Game Game::game;

void Game::init() {

	metaballHandler.init(engine->window.getSize(), false);

	world.textureManager = &engine->textureManager;
	world.metaballHandler = &metaballHandler;

	createPlayer(&world, 0, 0);

	createGroundBlob(&world, 6000, -1500);
	createTest(&world, 21100, -1100);
	createLotus(&world, 48000, 2150);
	//createHeart(&world, 900, 500);
	createWisp(&world, 500, 500, &metaballHandler);
	createCeilingPlant(&world, 12700, -20);
	//createSpitter(&world, 9000, -900);
	//createSpitter(&world, 11500, -1100);

	objectMap = ObjectMap(&engine->textureManager);
	objectMap.load();
	platformMap.load();
	hitboxMap.load();

	eventMap.world = &world;
	eventMap.load();
	//eventMap.numEvents = 0;

	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(3);

	waterHandler.load();

	guiView.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 3.5f, engine->window.getDefaultView().getSize().y * 3.5f));

	healthBar = new HealthBar(&guiView, world.health[0].current, world.health[0].max);
	view.setCenter(sf::Vector2f(world.position[0].x, world.position[0].y)); // NO LERP

}

void Game::clean() {

	metaballHandler.clean();
	eventMap.clean();
	cleanWorld(&world);
	platformMap.clean();
	objectMap.clean();
	waterHandler.clean();
	hitboxMap.clean();

	eventMap.clean();

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

			if (event.key.code == sf::Keyboard::L) {
				drawDebug = !drawDebug;
				printf("%f, %f", world.position[0].x, world.position[0].y);
			}

			if (event.key.code == sf::Keyboard::J)
				world.input[PLAYER].attack = true;
			if (event.key.code == sf::Keyboard::K) {
				world.input[PLAYER].special = true;
			}

			if (event.key.code == sf::Keyboard::LShift)
				metaballHandler.sunburst(sf::Vector2f(world.position[0].x, world.position[0].y), 20);

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

			if (event.key.code == sf::Keyboard::J)
				world.input[PLAYER].attack = false;
			if (event.key.code == sf::Keyboard::K) {
				world.input[PLAYER].special = false;
			}

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
	shapeCollSystem(&world, &platformMap, &hitboxMap);
	movementSystem(&world);
	damageSystem(&world, dt, &hitboxMap);
	metaballDamageSystem(&world, &hitboxMap);

	for (eventMap.eit = eventMap.events.begin(); eventMap.eit != eventMap.events.end();) {

		if (eventMap.eit->second->eventArea->getGlobalBounds().contains(world.position[0].x, world.position[0].y)) {
			if (eventMap.eit->second->isTriggered())
				eventMap.eit->second->trigger();
		}

		eventMap.eit++;
	}

	waterHandler.dealDamage(&world);
	waterHandler.update();
	waterHandler.updateWaves(dt);

	//listener.setPosition(world.position[0].x, world.position[0].y, 0);
	sf::Listener::setPosition(world.position[0].x, 0, world.position[0].y);

	view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 3.5f, engine->window.getDefaultView().getSize().y * 3.5f));
	guiView.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 3.5f, engine->window.getDefaultView().getSize().y * 3.5f));

	// @Hardcoded We assume dt will always be 0.01666666f, not good if we change frame rate
	view.setCenter(sf::Vector2f(lerp(view.getCenter().x, world.position[PLAYER].x, 1.0f - exp(-2.0f * 0.01666666f)), world.position[PLAYER].y - view.getSize().y / 6));
	
	engine->window.setView(view);

	metaballHandler.update(dt);

	healthBar->update(&guiView, world.health[0].current, world.health[0].max);

	/* Hitbox Temp */
	//rect.setSize(sf::Vector2f(world.sprite[0].sprite.getLocalBounds().width, world.sprite[0].sprite.getLocalBounds().height));
	//rect.setPosition(sf::Vector2f(world.sprite[0].sprite.getGlobalBounds().left, world.sprite[0].sprite.getGlobalBounds().top));

}

void Game::render(const float dt) {

	objectMap.drawSuperBackground(&engine->window);

	objectMap.drawBackground(&engine->window);

	renderSystem(&world, &engine->window);

	metaballHandler.draw(&engine->window, &view);

	waterHandler.draw(&engine->window);

	engine->window.draw(rect);

	objectMap.drawForeground(&engine->window);

	if (drawDebug) {
		
		for (pit = platformMap.map.begin(); pit != platformMap.map.end(); pit++)
			engine->window.draw(*(pit->second));
	
		/* HitboxTest */
		std::string texID;
		std::vector<sf::RectangleShape> hitboxes;
		sf::RectangleShape box;
		
		#define ANIMATION_MASK (INPUT | SPRITE | SCRIPT)
		for (int entityID = 0; entityID < MAX_ENTITIES; entityID++) {
			if ((world.mask[entityID] & ANIMATION_MASK) == ANIMATION_MASK) {
				texID = world.sprite[entityID].animationManager.getCurrentTextureID();

				if (world.input[entityID].lastDirection == LEFT)
					hitboxes = hitboxMap.getFlippedHitboxes(texID, HITBOXTYPE_ALL);
				else
					hitboxes = hitboxMap.getHitboxes(texID, HITBOXTYPE_ALL);

				for (size_t i = 0; i < hitboxes.size(); i++) {
					box = hitboxes[i];
					box.move(world.position[entityID].x, world.position[entityID].y);
					engine->window.draw(box);
				}
			}
		}
	}

	//for (eventMap.eit = eventMap.events.begin(); eventMap.eit != eventMap.events.end(); )
	//{
		//if (eventMap.eit->second->eventArea->getGlobalBounds().contains(world.position[0].x, world.position[0].y)) {
			//if (eventMap.eit->second->eventArea == NULL)
				//printf("NULL");
			//else
				//engine->window.draw(*(eventMap.eit->second->eventArea));
		//}
		//eventMap.eit++;
//	}

	engine->window.setView(guiView);

	healthBar->draw(&engine->window);

	engine->window.setView(view);

}