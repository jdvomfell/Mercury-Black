#include "Game.h"

#include "System.h"
#include "MainMenu.h"
#include "Editor.h"

Game Game::game;

void Game::init() {

	world.textureManager = &engine->textureManager;

	//int test = createTest(&world, sf::Vector2f(1000, 0));
	createPlayer(&world, 900, 0);

	//world.sprite[test].sprite.setTexture(*engine->textureManager.getTexture("player_run_1"));
	//world.sprite[test].sprite.setOrigin(world.sprite[test].sprite.getLocalBounds().width / 2, world.sprite[test].sprite.getLocalBounds().height);

	//createCeilingPlant(&world, 100, 1000);

	objectMap = ObjectMap(&engine->textureManager);
	objectMap.load();
	collisionMap.load();

	platformMap.add(sf::Vector2f(200, 1300), 3);

	slide1.setFont(engine->textureManager.slideFont);
	slide1.setStyle(sf::Text::Bold);
	slide1.setCharacterSize(150);
	slide1.setFillColor(sf::Color::Black);
	slide1.setPosition(0, 0);
	slide1.setString("DiaLog Studio\n");

	slide2 = sf::Text(slide1);
	slide2.setCharacterSize(100);
	slide2.setString("\n\n - Jesse Vomfell\n - Alex Bahna\n - Adriano Santos\n - Todd Selwitz\n");

	slide3 = sf::Text(slide1);
	slide3.setString("The Project\n");
	slide3.setPosition(4000, 0);
	
	slide4 = sf::Text(slide2);
	slide4.setString("\n\n - 2D Action Adventure Platformer\n - SFML Libraries\n - Hand Drawn Animations\n - An Orginal Soundtrack\n - A World of Ink Art\n - Inspiration...");
	slide4.setPosition(4000, 0);

	slide5 = sf::Text(slide1);
	slide5.setString("Approaching The Project...\n");
	slide5.setPosition(8000, -300);

	slide6 = sf::Text(slide2);
	slide6.setString("\n\n - Level Editor\n - Entity Component System\n - Convex Collision System\n - Animators / Composer\n");
	slide6.setPosition(8000, -300);
	platformMap.add(sf::Vector2f(9600, 200), 3);

	slide7 = sf::Text(slide1);
	slide7.setString("Jesse Vomfell - Lead Developer\n");
	slide7.setPosition(10800, -900);

	slide8 = sf::Text(slide2);
	slide8.setString("\n\n -SFML\n - C/C++/JAVA\n - Game Development\n");
	slide8.setPosition(10800, -900);

	slide9 = sf::Text(slide1);
	slide9.setString("Adriano Santos\n");
	slide9.setPosition(14800, 0);

	slide10 = sf::Text(slide2);
	slide10.setString("\n\n - C/C++\n - AI Development\n - Level Editor Development\n");
	slide10.setPosition(14800, 0);
	createCeilingPlant(&world, 13300, 500);

	slide11 = sf::Text(slide1);
	slide11.setString("Todd Selwitz ;D\n");
	slide11.setPosition(18800, 0);
	int test = createTest(&world, sf::Vector2f(19000, 0));
	
	slide12 = sf::Text(slide2);
	slide12.setString("\n\n - C/C++\n - Physics & Collision Development\n - AI Development\n");
	slide12.setPosition(18800, 0);

	slide13 = sf::Text(slide1);
	slide13.setString("Alex Bahna\n");
	slide13.setPosition(22800, 0);

	slide14 = sf::Text(slide2);
	slide14.setString("\n\n - C/C++\n - Sound Design\n - Collision & Physics Development\n - Level Design\n");
	slide14.setPosition(22800, 0);

	slide19 = sf::Text(slide1);
	slide19.setString("Iterations\n");
	slide19.setPosition(26800, -300);

	slide20 = sf::Text(slide2);
	slide20.setString("\n\n - Iteration 1 - Animations, Simple AI, Collisiion\n - Iteration 2 - Convex Collision, AI States\n   (Attack, Defend, Etc.)\n - Iteration 3 - Several Entities Working,\n   Interactable Objects, Hit Box Editor\n - Iteration 4 - Event Editor, Better Saves And Loads\n - Iteration 5 - \"Building The Game\"\n");
	slide20.setPosition(26800, -300);

	slide15 = sf::Text(slide1);
	slide15.setString("Market Value\n");
	slide15.setPosition(30800, -700);
	
	slide16 = sf::Text(slide2);
	slide16.setString("\n\n - Market for 2D Games\n - Developed for PC\n - Unique Animations and Music\n");
	slide16.setPosition(30800, -700);

	slide17 = sf::Text(slide1);
	slide17.setString("Stretch Goals\n");
	slide17.setPosition(34800, -700);

	slide18 = sf::Text(slide2);
	slide18.setString("\n\n - Story Line\n - Polished Editor\n - Postprocessing Effects\n   - Sunrays\n   - Metaballs (INK)\n   - Canvas Texture\n - Steam Greenlight\n");
	slide18.setPosition(34800, -700);

	music.openFromFile("Music/drank.ogg");
	music.setVolume(20);
	music.setPosition(22800, 0, 0);
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
	shapeCollSystem(&world, &platformMap);
	//animationSystem(&world, dt, PLAYER);
	movementSystem(&world);

	//listener.setPosition(world.position[0].x, world.position[0].y, 0);
	sf::Listener::setPosition(world.position[0].x, 0, world.position[0].y);

	view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 2.5, engine->window.getDefaultView().getSize().y * 2.5));
	view.setCenter(sf::Vector2f(world.position[PLAYER].x, world.position[PLAYER].y - view.getSize().y / 4));
	engine->window.setView(view);

}

void Game::render(const float dt) {

	std::map<float, Object *>::iterator it;
	for (it = objectMap.map.begin(); it != objectMap.map.end(); it++)
		engine->window.draw(it->second->sprite);

	engine->window.draw(collisionMap.lines);

	engine->window.draw(slide1);
	engine->window.draw(slide2);
	engine->window.draw(slide3);
	engine->window.draw(slide4);
	engine->window.draw(slide5);
	engine->window.draw(slide6);
	engine->window.draw(slide7);
	engine->window.draw(slide8);
	engine->window.draw(slide9);
	engine->window.draw(slide10);
	engine->window.draw(slide11);
	engine->window.draw(slide12);
	engine->window.draw(slide13);
	engine->window.draw(slide14);
	engine->window.draw(slide15);
	engine->window.draw(slide16);
	engine->window.draw(slide17);
	engine->window.draw(slide18);
	engine->window.draw(slide19);
	engine->window.draw(slide20);

	renderSystem(&world, &engine->window);

	for (platformMap.pit = platformMap.platformMap.begin(); platformMap.pit != platformMap.platformMap.end(); platformMap.pit++)
		engine->window.draw(*(platformMap.pit->second->shape));
}