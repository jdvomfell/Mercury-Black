#include "PauseMenu.h"
#include <iostream>

PauseMenu PauseMenu::pauseMenu;

void PauseMenu::init() {

	title = sf::Text("Paused", engine->textureManager.font, PAUSE_TITLE_SIZE);
	title.setFillColor(sf::Color::Black);
	title.setOutlineThickness(5);
	title.setOutlineColor(sf::Color(100, 100, 100, 255));
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

	resumeButton = TextButton("Resume", 0, 0, PAUSE_FONT_SIZE, &engine->textureManager.font, &popState);
	optionsButton = TextButton("Options", 0, 0, PAUSE_FONT_SIZE, &engine->textureManager.font, &doNothing);
	mainMenuButton = TextButton("Main Menu", 0, 0, PAUSE_FONT_SIZE, &engine->textureManager.font, &changeToMainMenu);
	quitButton = TextButton("Quit", 0, 0, PAUSE_FONT_SIZE, &engine->textureManager.font, &quitGame);

	guiHandler.buttons.resize(4);
	guiHandler.buttons = { &resumeButton, &optionsButton, &mainMenuButton, &quitButton };

	view = engine->window.getDefaultView();
	engine->window.setView(view);

	title.setPosition(view.getCenter().x, view.getCenter().y - (view.getSize().y / 3));

	resumeButton.text.setPosition(view.getCenter().x, title.getPosition().y + (view.getSize().y / 6));
	optionsButton.text.setPosition(view.getCenter().x, title.getPosition().y + 2*(view.getSize().y / 6));
	mainMenuButton.text.setPosition(view.getCenter().x, title.getPosition().y + 3*(view.getSize().y / 6));
	quitButton.text.setPosition(view.getCenter().x, title.getPosition().y + 4*(view.getSize().y / 6));

	guiHandler.isSelected(sf::Vector2f(0, 0));

}

void PauseMenu::clean() {

}

void PauseMenu::handleEvent() {

	sf::Event event;

	if (engine->window.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				engine->popState();
			break;

		case sf::Event::MouseMoved:

			guiHandler.isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));

			break;

		case sf::Event::MouseButtonPressed:

			if (event.mouseButton.button == sf::Mouse::Left)

				guiHandler.interact(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)), engine);

			break;

		case sf::Event::Closed:
			engine->quit();
			break;

		}

	}

}

void PauseMenu::update(const float dt) {



}

void PauseMenu::render(const float dt) {

	engine->window.clear(sf::Color(248, 240, 225));
	guiHandler.draw(&engine->window);

	engine->window.draw(title);

}