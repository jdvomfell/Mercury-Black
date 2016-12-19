#include "MainMenu.h"
#include <iostream>

MainMenu MainMenu::mainMenu;

void MainMenu::init() {

	menuFont.loadFromFile("ZenzaiItachi.ttf");

	hText = sf::Color::Black;
	uText = sf::Color(100, 100, 100, 255);

	newButton = GUI_NewGame(0, 0, uText, MENU_FONT_SIZE, &menuFont);
	loadButton = GUI_LoadGame(0, 0, uText, MENU_FONT_SIZE, &menuFont);
	editorButton = GUI_Editor(0, 0, uText, MENU_FONT_SIZE, &menuFont);
	optionsButton = GUI_Options(0, 0, uText, MENU_FONT_SIZE, &menuFont);
	quitButton = GUI_Quit(0, 0, uText, MENU_FONT_SIZE, &menuFont);

	buttons.resize(5);
	buttons = { &newButton, &loadButton, &editorButton, &optionsButton, &quitButton };

	title = sf::Text("Ink", menuFont, MENU_TITLE_SIZE);

	title.setFillColor(sf::Color::Black);

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

		case sf::Event::MouseMoved:
			for (size_t i = 0; i < buttons.size(); i++) {
				
				if (buttons[i]->isSelected(event.mouseMove.x, event.mouseMove.y))
					buttons[i]->text.setFillColor(hText);
				else
					buttons[i]->text.setFillColor(uText);

			}
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) {

				if (buttons[buttons.size() - 1]->isSelected(event.mouseButton.x, event.mouseButton.y))
					engine->quit();

				for (size_t i = 0; i < buttons.size() - 1; i++) {

					if (buttons[i]->isSelected(event.mouseButton.x, event.mouseButton.y))
						buttons[i]->interact();

				}

			}
			break;

		case sf::Event::Closed:
			engine->quit();
			break;
		
		}
	
	}

}

void MainMenu::update(GameEngine * engine) {

	title.setPosition(engine->window.getSize().x / 2 - title.getLocalBounds().width / 2, engine->window.getSize().y / 4 - title.getLocalBounds().height / 2);

	newButton.text.setPosition(100.0f + engine->window.getSize().x / 5 * 0, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	loadButton.text.setPosition(100.0f + engine->window.getSize().x / 5 * 1, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	editorButton.text.setPosition(100.0f + engine->window.getSize().x / 5 * 2, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	optionsButton.text.setPosition(100.0f + engine->window.getSize().x / 5 * 3, 150.0f + title.getPosition().y + title.getLocalBounds().height);
	quitButton.text.setPosition(100.0f + engine->window.getSize().x / 5 * 4, 150.0f + title.getPosition().y + title.getLocalBounds().height);

}

void MainMenu::render(GameEngine * engine) {

	engine->window.draw(newButton.text);
	engine->window.draw(loadButton.text);
	engine->window.draw(editorButton.text);
	engine->window.draw(optionsButton.text);
	engine->window.draw(quitButton.text);
	engine->window.draw(title);

}