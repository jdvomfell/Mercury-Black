#include "MainMenu.h"
#include <iostream>

MainMenu MainMenu::mainMenu;

void MainMenu::init() {

	menuFont.loadFromFile("ZenzaiItachi.ttf");

	newGame = sf::Text("New", menuFont, MENU_FONT_SIZE);
	loadGame = sf::Text("Load", menuFont, MENU_FONT_SIZE);
	worldEditor = sf::Text("Editor", menuFont, MENU_FONT_SIZE);
	options = sf::Text("Options", menuFont, MENU_FONT_SIZE);
	quit = sf::Text("Quit", menuFont, MENU_FONT_SIZE);

	title = sf::Text("Ink", menuFont, MENU_TITLE_SIZE);

	hText = sf::Color::Black;
	uText = sf::Color(100, 100, 100, 255);

	title.setFillColor(sf::Color::Black);

	newGame.setFillColor(uText);
	loadGame.setFillColor(uText);
	worldEditor.setFillColor(uText);
	options.setFillColor(uText);
	quit.setFillColor(uText);

	selector = 1;

}

void MainMenu::clean() {

}

void MainMenu::pause() {

}

void MainMenu::resume() {

}

void MainMenu::handleEvent(GameEngine * engine) {

	sf::Event event;

	if (engine->window.pollEvent(event)) {
		
		switch (event.type) {

		case sf::Event::Closed:
			engine->window.close();
			exit(0);
			break;

		case sf::Event::Resized:
			resized(event.size.width, event.size.height);
			break;

		case sf::Event::KeyPressed:
			keyPressed(&event, engine);
			break;

		default:
			break;
		
		}
	
	}

}

void MainMenu::update(GameEngine * engine) {
	
	title.setPosition(engine->window.getSize().x / 2 - title.getLocalBounds().width / 2, engine->window.getSize().y / 4 - title.getLocalBounds().height / 2);

	newGame.setPosition(100.0f + engine->window.getSize().x / 5 * 0, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	loadGame.setPosition(100.0f + engine->window.getSize().x / 5 * 1, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	worldEditor.setPosition(100.0f + engine->window.getSize().x / 5 * 2, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	options.setPosition(100.0f + engine->window.getSize().x / 5 * 3, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	quit.setPosition(100.0f + engine->window.getSize().x / 5 * 4, 150.0f + title.getPosition().y + title.getLocalBounds().height);

	switch (selector) {

	case NEW_GAME:
		newGame.setFillColor(sf::Color::Black);
		break;
	case LOAD_GAME:
		loadGame.setFillColor(sf::Color::Black);
		break;
	case EDITOR:
		worldEditor.setFillColor(sf::Color::Black);
		break;
	case OPTIONS:
		options.setFillColor(sf::Color::Black);
		break;
	case QUIT:
		quit.setFillColor(sf::Color::Black);
		break;

	}

}

void MainMenu::render(GameEngine * engine) {

	engine->window.draw(newGame);
	engine->window.draw(loadGame);
	engine->window.draw(worldEditor);
	engine->window.draw(options);
	engine->window.draw(quit);
	engine->window.draw(title);

}

void MainMenu::resized(int width, int height) {

	title.setPosition(width / 2 - title.getLocalBounds().width / 2, height / 4 - title.getLocalBounds().height / 2);

	newGame.setPosition(100.0f + width / 5 * 0, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	loadGame.setPosition(100.0f + width / 5 * 1, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	worldEditor.setPosition(100.0f + width / 5 * 2, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	options.setPosition(100.0f + width / 5 * 3, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	quit.setPosition(100.0f + width / 5 * 4, 150.0f + title.getPosition().y + title.getLocalBounds().height);

}

void MainMenu::keyPressed(sf::Event* event, GameEngine* engine) {
	switch (event->key.code) {
	case sf::Keyboard::Return:
		switch (selector) {
		case NEW_GAME:
			//changeState(engine, Game::instance());
			break;
		case LOAD_GAME:

			break;
		case EDITOR:
			//changeState(engine, Editor::instance());
			break;
		case OPTIONS:

			break;
		case QUIT:
			engine->window.close();
			exit(1);
			break;
		default:
			std::cout << "Menu Selector Out Of Bounds, Position: " << selector << std::endl;
			break;
		}
		break;
	case sf::Keyboard::D:
		if (selector < 5)
			selector++;
		else
			selector = 1;

		newGame.setFillColor(uText);
		loadGame.setFillColor(uText);
		worldEditor.setFillColor(uText);
		options.setFillColor(uText);
		quit.setFillColor(uText);
		break;
	case sf::Keyboard::A:
		if (selector > 1)
			selector--;
		else
			selector = 5;

		newGame.setFillColor(uText);
		loadGame.setFillColor(uText);
		worldEditor.setFillColor(uText);
		options.setFillColor(uText);
		quit.setFillColor(uText);
		break;
	}

}