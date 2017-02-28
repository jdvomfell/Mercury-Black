#include "PauseMenu.h"
#include <iostream>

PauseMenu PauseMenu::pauseMenu;

void PauseMenu::init() {

	hText = sf::Color::Black;
	uText = sf::Color(100, 100, 100, 255);

	title = sf::Text("Paused", engine->textureManager.font, PAUSE_TITLE_SIZE);
	title.setFillColor(sf::Color::Black);
	title.setOutlineThickness(5);
	title.setOutlineColor(uText);
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

	resumeButton = Button("Resume", 0, 0, uText, PAUSE_FONT_SIZE, &engine->textureManager.font, &popState);
	optionsButton = Button("Options", 0, 0, uText, PAUSE_FONT_SIZE, &engine->textureManager.font, &doNothing);
	mainMenuButton = Button("Main Menu", 0, 0, uText, PAUSE_FONT_SIZE, &engine->textureManager.font, &changeToMainMenu);
	quitButton = Button("Quit", 0, 0, uText, PAUSE_FONT_SIZE, &engine->textureManager.font, &quitGame);

	buttons.resize(4);
	buttons = { &resumeButton, &optionsButton, &mainMenuButton, &quitButton };

	view = engine->window.getDefaultView();
	engine->window.setView(view);

	title.setPosition(view.getCenter().x, view.getCenter().y - (view.getSize().y / 3));

	resumeButton.text.setPosition(view.getCenter().x, title.getPosition().y + (view.getSize().y / 6));
	optionsButton.text.setPosition(view.getCenter().x, title.getPosition().y + 2*(view.getSize().y / 6));
	mainMenuButton.text.setPosition(view.getCenter().x, title.getPosition().y + 3*(view.getSize().y / 6));
	quitButton.text.setPosition(view.getCenter().x, title.getPosition().y + 4*(view.getSize().y / 6));

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

			for (size_t i = 0; i < buttons.size(); i++) {

				if (buttons[i]->isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y))))
					buttons[i]->text.setFillColor(hText);
				else
					buttons[i]->text.setFillColor(uText);

			}
			break;

		case sf::Event::MouseButtonPressed:

			if (event.mouseButton.button == sf::Mouse::Left) {

				for (size_t i = 0; i < buttons.size(); i++) {

					if (buttons[i]->isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
						buttons[i]->interact(engine);
					}

				}

			}
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
	for (size_t i = 0; i < buttons.size(); i++)
		engine->window.draw(buttons[i]->text);
	engine->window.draw(title);

}